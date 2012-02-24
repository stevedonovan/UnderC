/* errors.cpp
 * Managing output and redirection of errors and messages; supplies yyerror()
 * UnderC C++ interpreter
 * Steve Donovan, 2001
 * This is GPL'd software, and the usual disclaimers apply.
 * See LICENCE
 */

#include "classlib.h"
#include "common.h"
#include "errors.h"
#include "input.h"
#ifdef _WCON
#include "ide.h"
#endif

#include "program.h"

#include <cstring>
#include <strstream>


void next_statement();   // in uc_tokens.cpp

const int BUFFSIZE = 256, ERR_BUFF_SIZE = 256, MSG_BUFF_SIZE = 1024;

static char err_buff[ERR_BUFF_SIZE], msg_buff[MSG_BUFF_SIZE];
static string current_err;

int yyerror(const char *s)
{
// *hack 1.2.9 Interactive mode final error involving "DUD" appears harmless
 if (Input::filename() == "DUD") return 1;
 cerr << Input::filename() << ' ' << Input::lineno() << ':' << s << std::endl;
 next_statement();
 // *fix 1.2.8 Insist on only collecting errors w/in the same file
 string old_file = Parser::state.file;
 if (old_file == "" || old_file == Input::filename()) {
   if (Errors::output_is_redirected() && current_err.length() > 0) current_err += "\n";
   current_err += s;
   Parser::state.file = Input::filename();
   Parser::state.lineno = Input::lineno();
 }
 return 1;
}

char *msg_buffer() { return msg_buff; }

// Redirection mechanism. Except for the console-only build, the standard error
// and message streams can be redirected into another ostream. Of course, cmsg
// is only distinct from cout when using WCON, so redirecting cmsg in the DLL
// will also redirect standard output.  This is a good thing, although watch
// out for runnaway processes.  Currently there's no pretense at being thread-safe
// or even re-entrant.

#ifndef _WCON

std::ostrstream str_cmsg(msg_buff,MSG_BUFF_SIZE),
           str_cerr(err_buff,ERR_BUFF_SIZE);

static bool mDllOutputRedirected = false;
void reset_output();


bool cerr_is_redirected(std::ostream&)
{
	return mDllOutputRedirected;
}

#endif

char *
Errors::get_redirect_buffer(int which)
{
  if (which == 1) {
	return msg_buff;
  }	else
  if (which == 2) {
     strcpy(err_buff,current_err.c_str()); //err_buff;
     current_err = "";
     return err_buff;
  }
  else return NULL;
}

void
Errors::redirect_output(bool to_buff, bool main_console)
{
#ifdef _WCON
    if (to_buff) {
       wcon_redirect_output(cmsg,new ostrstream(msg_buff,MSG_BUFF_SIZE),main_console);
       wcon_redirect_output(cerr,new ostrstream(err_buff,ERR_BUFF_SIZE),main_console);
    } else {
       wcon_redirect_off(cmsg);
       wcon_redirect_off(cerr);
    }
#else
	if (to_buff) {
#ifdef _CONSOLE
          _cmsg_out = &str_cmsg;
          _cerr_out = &str_cerr;
#endif
	   mDllOutputRedirected = true;
	   str_cmsg.seekp(0);
	   str_cerr.seekp(0);
    } else {
#ifdef _CONSOLE
           reset_output();
#endif
	   mDllOutputRedirected = false;
           str_cmsg << std::ends;
	   str_cerr << std::ends;
    }
#endif
}

bool
Errors::output_is_redirected()
{
#ifdef _WCON
  return wcon_is_redirected(cmsg);
#else
  return cerr_is_redirected(cmsg);
#endif
}

int
Errors::get_stop_position(char *filename)
{
  strcpy(filename, Parser::state.file.c_str());
  int line =  Parser::state.lineno;
  Parser::state.lineno = 0;  // this flags whether we hit a definite error!!
  return line;
}


void
Errors::set_halt_state(string msg, string fname, string file, int lineno, bool was_error)
{
  bool was_ip = file == "";
  current_err = msg;
  if (! was_ip) {  // we shd try to at least find the file otherwise...
    Parser::state.file = file;
    Parser::state.lineno = lineno;
  }
  else Parser::state.lineno = lineno;  // *fix 1.1.1 to flag us as having crashed!

  //* if (was_error || ! output_is_redirected()) {
      // *add 1.2.8 don't bug the user if we've already complained to the debugger...
      // but preserve true error messages for the meantime.
      if (! Parser::debug.interactive_debugging || was_error) {
        if (! was_ip) cerr  << file << ' ' << lineno << ": ";
        else cerr << '(' << lineno << ") ";
        cerr << msg << std::endl;
      }
#ifdef _WCON
// *change 1.2.8 we do not bother the IDE if this event happened outside the program thread.
      if (! Program::in_main_thread()) {
       if (was_error) {
		wcon_clear(0);  // clear WCON input buffer as a precaution...
        IDE::error(); // inform the IDE....
       } else
	    IDE::breakpoint();
      }
#endif
  //* }
}

void
Errors::reset_error_state()
{
  Parser::state.lineno = 0;
  current_err = "";
}


int
Errors::check_output()
{
    if (output_is_redirected()) { redirect_output(false); return 1; }
    else return 0;
}

// *add 1.2.4 We can redirect cmsg and cerr in console mode by setting
// these pointers appropriately (cmsg is #def'd to be *_cmsg_out etc - see classlib.h)
#if defined(_CONSOLE) || defined(_USRDLL)
# ifndef _FAKE_IOSTREAM
#   undef cerr
# endif
  std::ostream* _cmsg_out = &std::cout;
  std::ostream* _cerr_out = &std::cout;

void reset_output()
{
  _cmsg_out = &std::cout;
  _cerr_out = &std::cout;
}

#endif


