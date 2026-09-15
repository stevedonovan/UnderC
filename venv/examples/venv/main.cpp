// venv - optional per-user helper source
// ----------------------------------------------
// Every *.c / *.cpp file in the per-user venv directory is auto-loaded into the
// interpreter before your .cvc configuration runs:
//   Windows : %APPDATA%\venv\
//   Linux   : $XDG_CONFIG_HOME/venv/   (or $HOME/.config/venv/)
//
// Put shared helper functions here so your .cvc files stay short. This file is
// C++ run by the embedded UnderC engine, started WITH its STL prelude, so
// <string>, <vector>, <map> and friends are available. Do NOT define main()
// here - that belongs in the .cvc file.
//
// The venv* API is provided natively by venv; you do not need to
// declare it:
//   void        venvRootDir(const char* path);
//   void        venvSetEnv(const char* name, const char* value);
//   void        venvSetEnv(const char* name, const char* value, bool inShell);
//   void        venvPreEnv(const char* name, const char* fragment);
//   void        venvPreEnv(const char* name, const char* fragment, bool inShell);
//   void        venvAppEnv(const char* name, const char* fragment);
//   void        venvAppEnv(const char* name, const char* fragment, bool inShell);
//   const char* venvEnvGet(const char* name);
//   void        venvSnapShotEnv();
//   void        venvCompareSnapshotEnv();
//   void        venvExeCommand(const char* cmd);
//   void        venvExeCommand(const char* cmd, bool inShell);
//   const char* venvExeCommandString(const char* cmd);
//   void        venvStartShell(const char* shell);
//   void        venvStopShell();
//   void        venvExecAppCommands();
//   int         venvAppCommandCount();
//   const char* venvAppCommandAt(int index);
//   int         venvLastExitCode();
//   void        venvPrint(const char* text);

// An auto-loaded file is parsed in its own module scope, so pull in std here.
using namespace std;

// Prepend one directory (plus its separator) to the front of PATH.
void venvAddToPathWin(const char* dir) {
    string s = dir;
    s += ";";
    venvPreEnv("PATH", s.c_str());
}
void venvAddToPathPosix(const char* dir) {
    string s = dir;
    s += ":";
    venvPreEnv("PATH", s.c_str());
}

// venvExeCommandString() runs `cmd` through the host command interpreter
// (cmd.exe on Windows, /bin/sh on Linux) in the environment built so far and
// returns everything it wrote to stdout, so a config can read a value back out
// of the environment instead of only acting on it:
//
//     string version = venvExeCommandString("cl 2>&1");
//     string vars    = venvExeCommandString("SET");
//
// The command's stderr is not captured; it still reaches the terminal.
//
// The environment-diff helpers below turn that output into data.
//
//     string before = venvExeCommandString("SET");
//     string after  = venvExeCommandString("call vcvars64.bat & SET");
//     map<string,vector<string> > a = parseEnvironment(before);
//     map<string,vector<string> > b = parseEnvironment(after);
//     map<string,vector<string> > added = findAddedEntriesEnvironment(a, b);
//     venvPreEnv(added);
//
// so a toolchain script can be run once, in a throw-away shell, and only what
// it added is carried into the environment venv hands to every later
// venvExeCommand() - no shell has to be kept open.

// The separator that joins list-valued variables on this host. There is no
// _WIN32 in the interpreter, so the host is recognised by two variables that
// only cmd.exe-based systems set.
char venvPathSep() {
    string comspec = venvEnvGet("COMSPEC");
    if (!comspec.empty()) return ';';
    string windir = venvEnvGet("WINDIR");
    if (!windir.empty()) return ';';
    return ':';
}

// Split a variable's value on `sep`, dropping empty fragments (a trailing
// separator is normal in PATH). A value that holds no separator comes back as
// a single-element vector, so scalars and lists are handled uniformly.
vector<string> venvSplitEnvValue(const string& value, char sep) {
    vector<string> parts;
    int n     = value.size();
    int start = 0;
    for (int i = 0; i <= n; i++) {
        if (i == n || value[i] == sep) {
            if (i > start) parts.push_back(value.substr(start, i - start));
            start = i + 1;
        }
    }
    return parts;
}

// True for something that can be an environment variable name in a SET / env
// dump. This is what rejects the banner lines vcvars64.bat prints before its
// SET output: they carry no '=' at all, or no usable name in front of one.
bool venvIsEnvName(const string& name) {
    if (name.empty()) return false;
    for (int i = 0; i < name.size(); i++) {
        char c = name[i];
        if (c == ' ' || c == '\t') return false;
    }
    return true;
}

// Parse the output of `SET` (Windows) or `env` (Linux) into
//   variable name -> the value, split on the host's list separator
//
// One NAME=VALUE per line; \r\n and \n line endings are both accepted. Lines
// without a '=', and cmd.exe's `=C:=...` / `=ExitCode=...` pseudo variables
// (whose name is empty), are skipped, which is also what keeps a tool banner
// printed ahead of the dump out of the result.
map<string,vector<string> > parseEnvironment(const string& text) {
    map<string,vector<string> > out;
    char sep = venvPathSep();
    int  n   = text.size();
    int  i   = 0;
    while (i < n) {
        int stop = i;
        while (stop < n && text[stop] != '\n') stop++;
        int end = stop;
        if (end > i && text[end - 1] == '\r') end--;

        int eq = -1;
        for (int j = i; j < end; j++) {
            if (text[j] == '=') { eq = j; break; }
        }
        if (eq > i) {
            string name = text.substr(i, eq - i);
            if (venvIsEnvName(name)) {
                string value = text.substr(eq + 1, end - eq - 1);
                out[name]    = venvSplitEnvValue(value, sep);
            }
        }
        i = stop + 1;
    }
    return out;
}

// Diff two parsed environments and return only what `after` gained:
//   - a variable `before` does not have at all, with its whole value, and
//   - for a variable both have, the fragments of it that `before` lacked,
//     in the order `after` lists them.
// Variables that did not change are left out entirely, and so are ones that
// only lost fragments.
map<string,vector<string> > findAddedEntriesEnvironment(
        map<string,vector<string> >& before,
        map<string,vector<string> >& after) {
    map<string,vector<string> > added;
    map<string,vector<string> >::iterator it;
    for (it = after.begin(); it != after.end(); ++it) {
        vector<string> fresh;
        if (before.count(it->first) == 0) {
            fresh = it->second;
        } else {
            vector<string>& old = before[it->first];
            for (int i = 0; i < it->second.size(); i++) {
                bool seen = false;
                for (int j = 0; j < old.size(); j++) {
                    if (old[j] == it->second[i]) { seen = true; break; }
                }
                if (!seen) fresh.push_back(it->second[i]);
            }
        }
        if (fresh.size() > 0) added[it->first] = fresh;
    }
    return added;
}

// venvPreEnv() over a whole parsed environment: prepend every entry to the
// variable it belongs to, joined with the host's list separator.
//
// A variable that already has a value is prepended to, separator included, so
// the existing entries stay reachable behind the new ones. One that does not
// exist yet is set outright, so a freshly introduced scalar such as VSCMD_VER
// does not end up with a stray separator glued to it.
void venvPreEnv(map<string,vector<string> >& entries) {
    char sep = venvPathSep();
    map<string,vector<string> >::iterator it;
    for (it = entries.begin(); it != entries.end(); ++it) {
        if (it->second.size() == 0) continue;
        string joined;
        for (int i = 0; i < it->second.size(); i++) {
            if (i > 0) joined += sep;
            joined += it->second[i];
        }
        string current = venvEnvGet(it->first.c_str());
        if (current.empty()) {
            venvSetEnv(it->first.c_str(), joined.c_str());
        } else {
            joined += sep;
            venvPreEnv(it->first.c_str(), joined.c_str());
        }
    }
}

// Run vcvars64.bat inside the currently open shell (call venvStartShell first).
void venvMsvc2026() {
    venvExeCommand(
        "call \"C:\\Program Files\\Microsoft Visual Studio\\18\\Community"
        "\\VC\\Auxiliary\\Build\\vcvars64.bat\"", true);
}
