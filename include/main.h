/* main.h
 * Main Program, initialization, and # command implementation
 * UnderC C++ interpreter
 * Steve Donovan, 2001
 * This is GPL'd software, and the usual disclaimers apply.
 * See LICENCE
 */

namespace Main {
 void initialize();
 bool process_command_line(int& argc, char**& argv);
 void banner();
 void finalize();
 int interactive_loop();
 char *uc_exec_name();
 string uc_lib_dir();
 // *add 1.5.3 host-configured runtime prefix ($PREFIX with bin/ include/ lib/)
 void set_home_dir(const string& path);
 const string& configured_home_dir();
};

