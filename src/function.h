/* FUNCTION.H
 */
#ifndef _FUNCTION_H
#define _FUNCTION_H
#include "table.h"
#include "imports.h"
#include "class.h"

// structure that contains info about a PROC
// (the CALL instruction is passed this)
#include "engine.h"

#define WITHIN_UC
#include "export.h"
#include "xtrace.h"

class Function;

#include "fblock.h"

struct LineInfo {
    string file;
    int line, ip_offset;
    Table *cntxt;
};

class LineNumbersB {
public:
   virtual void add(const LineInfo& li) = 0;
   virtual bool lookup_line(LineInfo& li, bool find_line=true) = 0;
   virtual int  lookup_ip(int line) = 0;
   virtual void lookup_range(int& l1, int& l2) = 0;
   virtual void module(int id) = 0;
   virtual int  module() = 0;
   virtual void dump(std::ostream& out) = 0;
};

class FunctionContext;

const int FUNCTION = 487;

class LocalContext: public Table {
protected:
  Function *m_function;
  bool m_no_auto_dtor;

public:
    LocalContext(Table *parent, Function *fun);
    int alloc(int sz, void *data);   // override Table::alloc()
    void set_parent(Table *parent);
    void finalize();
    void add_line_no(const string& file, int line); // override

	bool check_objects(bool do_clear=true);
    Function *function() { return m_function; }

    void set_no_auto_dtor(bool yesno)   { m_no_auto_dtor = yesno;  }
    bool no_auto_dtor()       { return m_no_auto_dtor;  }
};
typedef LocalContext *PLocalContext;

class FunctionContext: public LocalContext {
public:
   FunctionContext(Table *parent, Function *fun);
   virtual void initialize();
   virtual void finalize();
   FBlock *fun_block();
   bool  ip_to_line(LineInfo& li);
};

// The Function class has three purposes:
//  - manages the _function context_
//  - looks after the type of the function (its signature)
//  - keeps all necessary references to code & line numbers.
class FunctionEntry; // forward
class Expr;
typedef Expr *PExpr;
typedef std::list<PExpr> ExprList;
typedef ExprList *PExprList;

typedef std::vector<Expr *> ExprArray;
typedef ExprArray *PExprArray;

class TemplateInstance; // forward

typedef unsigned char uchar;

#undef CDECL

class Function {
protected:
  Signature *m_sig;
  FunctionContext *m_context;
  bool m_cdecl;
  int m_slot_id;
  PEntry m_ret_obj;
  FunctionEntry *m_fun_entry;
  PExprArray m_default_args;
  int m_default_index;
  bool m_stdarg;
  uchar m_builtin;
  uchar m_ftype;
  FBlock *m_fun_block;
  LineNumbersB *m_line_nos;
  TemplateInstance *m_templ_info;
  ImportScheme *m_import_scheme;
  int m_line;
  int m_mod;

public:

  enum { CDECL=2, _STDCALL=1, STDMETHOD=3, UCFN=0 };

  Function(Signature *sig, FunctionEntry *fe);
  ~Function();

  void attach_context(FunctionContext *context);
  void set_construct_destruct(int ftype, bool no_implicit_type_conversion = false);
  bool is_destructor();
  bool is_constructor();
  bool is_plain();
  bool is_method();

   // non-NULL iff this is a 'complete' function
  FunctionContext * context();
  Signature *       signature();
  Type              return_type();
  LineNumbersB *    line_nos();

  // non-NULL iff this function returns an object value
  PEntry return_object();
  void return_object(PEntry pe);

  bool stdarg();
  void stdarg(bool stdarg);
  bool builtin();
  void builtin(uchar b);
  bool is_cdecl();
  bool stdmethod();
  ImportScheme *import_scheme();
  void import_scheme(ImportScheme *is);
  void adjust_return_type(Type t);
  void fun_block(FBlock *fblk);
  FBlock *fun_block();
  FunctionEntry *fun_entry();
  bool undefined();
  void clear();
  void dump(std::ostream& os);
  string as_str();
  static Function *from_fun_block(FBlock *pfb);
  static Function *lookup(const string& nm);
  string  name();
  bool can_match(int size);
  bool has_default_args();
  void set_default_args(PExprList args);
  PExprList complete_arg_list(PExprList args);
  // non-NULL iff this is a method of a class
  Class *class_context();
  bool is_const();
  bool is_static();
  // *change 1.2.3 A flag which is true if a function is to be _exported_ as cdecl
  bool export_as_cdecl();
  void export_as_cdecl(bool yesno);
  int slot_id();
  void slot_id(int i);
  bool is_virtual();
  int  line();
  int  module();
 // (optional) template info
  bool is_template();
  TemplateInstance *get_template();
  void set_template(TemplateInstance *pti);

};

typedef std::list<Function *> FunctionList;
class TemplateEntry; // forward

// for the now, FunctionEntry is really just a list of functions!
class FunctionEntry {
protected:
  FunctionList m_functions;
  PEntry m_entry;
  TemplateEntry *m_templ;
public:
  typedef FunctionList::const_iterator iterator;

  FunctionEntry(PEntry pe)
   : m_entry(pe),m_templ(NULL) {}

  FunctionEntry(PEntry pe, const FunctionList& fl)
   : m_entry(pe)
  {
    m_functions.assign(fl.begin(),fl.end());
  }

  PEntry reference() { return m_entry; }

  void dump (std::ostream& os);
  // Finding functions within the set...
  Function *simple_match(Signature *sig);
  Function *full_match(Signature *sig);
  Function *fun_from_fblock(FBlock *pfb);
  Function *nth_fun(int idx);

  // list-like interface!
  void push_back(Function *f) { m_functions.push_back(f); }
  void push_back(Signature *s) { push_back(new Function(s,this)); }
  void pop_back() { m_functions.pop_back(); }
  Function *back() const { return m_functions.back(); }
  int size() const { return m_functions.size(); }
  iterator begin() const { return m_functions.begin(); }
  iterator end()   const { return m_functions.end(); }

  void           set_template(TemplateEntry *te)  { m_templ = te; }
  TemplateEntry *get_template() const             { return m_templ; }
};

typedef Function *PFunction;
typedef FunctionEntry *PFunctionEntry;

std::ostream& operator << (std::ostream& os, Signature& sig);

class ConstructorContext: public FunctionContext {
private:
public:
   ConstructorContext(Table *parent, Function *fun);
   void initialize();
   void finalize();
};

class DestructorContext: public FunctionContext {
private:
public:
   DestructorContext(Table *parent, Function *fun);
///   void initialize();
   void finalize();
};

#endif
