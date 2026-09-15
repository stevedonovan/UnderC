/* The venv_spawner shell-environment scenario from underc_fix.txt.
 *
 * Overloaded natives with a two- and a three-argument form are imported by
 * name, a loaded script calls them with the language literal `true` in the
 * trailing position, and the natives allocate and free between calls.  The
 * interpreter is then shut down and the host keeps allocating, so any small
 * out-of-bounds write during the calls shows up before the test returns.
 */
#include <underc/ucdl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <map>
#include <string>
#include <vector>

static int failures;
static int shell_open;
static std::map<std::string,std::string> environment;
static std::vector<std::string> commands;

static void expect(bool condition)
{
    if (!condition) ++failures;
}

// Each native churns the host heap the way the real implementation does, so a
// corrupted allocator is detected close to the call that damaged it.
static void churn()
{
    std::vector<std::string> traffic(8,std::string(80,'x'));
    if (traffic.back().size() != 80) ++failures;
}

static void env_start_shell(const char *shell)
{
    expect(shell != 0 && strcmp(shell,"cmd.exe") == 0);
    shell_open = 1;
    churn();
}

static void env_stop_shell()
{
    expect(shell_open == 1);
    shell_open = 0;
    churn();
}

static void env_set(const char *name, const char *value)
{
    environment[name] = value;
    churn();
}

static void env_set_shell(const char *name, const char *value, int in_shell)
{
    expect(in_shell == 1);
    expect(shell_open == 1);
    environment[name] = value;
    churn();
}

static void env_prepend(const char *name, const char *value)
{
    environment[name] = std::string(value) + environment[name];
    churn();
}

static void env_prepend_shell(const char *name, const char *value, int in_shell)
{
    expect(in_shell == 1);
    environment[name] = std::string(value) + environment[name];
    churn();
}

static void env_append(const char *name, const char *value)
{
    environment[name] += value;
    churn();
}

static void env_append_shell(const char *name, const char *value, int in_shell)
{
    expect(in_shell == 1);
    environment[name] += value;
    churn();
}

static void env_command(const char *command)
{
    commands.push_back(command);
    churn();
}

static void env_command_shell(const char *command, int in_shell)
{
    expect(in_shell == 1);
    commands.push_back(command);
    churn();
}

static int import_function(const char *declaration, void *function)
{
    char buffer[256];
    if (strlen(declaration) >= sizeof(buffer)) return 0;
    strcpy(buffer,declaration);
    if (uc_import(buffer,function)) return 1;
    char error[512] = {0};
    uc_error(error,sizeof(error));
    fprintf(stderr,"import failed for %s: %s\n",declaration,error);
    return 0;
}

int main()
{
    // The embedding that reported the corruption starts with the standard
    // prelude and runs a loaded program, so reproduce both.
    if (!uc_init(NULL,1)) return 1;

    if (!import_function("void envStartShell(const char*)",
                         reinterpret_cast<void *>(&env_start_shell)) ||
        !import_function("void envStopShell()",
                         reinterpret_cast<void *>(&env_stop_shell)) ||
        !import_function("void envSet(const char*,const char*)",
                         reinterpret_cast<void *>(&env_set)) ||
        !import_function("void envSet(const char*,const char*,int)",
                         reinterpret_cast<void *>(&env_set_shell)) ||
        !import_function("void envPrepend(const char*,const char*)",
                         reinterpret_cast<void *>(&env_prepend)) ||
        !import_function("void envPrepend(const char*,const char*,int)",
                         reinterpret_cast<void *>(&env_prepend_shell)) ||
        !import_function("void envAppend(const char*,const char*)",
                         reinterpret_cast<void *>(&env_append)) ||
        !import_function("void envAppend(const char*,const char*,int)",
                         reinterpret_cast<void *>(&env_append_shell)) ||
        !import_function("void envCommand(const char*)",
                         reinterpret_cast<void *>(&env_command)) ||
        !import_function("void envCommand(const char*,int)",
                         reinterpret_cast<void *>(&env_command_shell))) return 2;

    const char *home = getenv("UC_HOME");
    if (home == 0) { fprintf(stderr,"UC_HOME is not set\n"); return 3; }
    std::string script = std::string(home) + "/regressiontests/native-shell-env.cvc";
    std::vector<char> path(script.begin(),script.end());
    path.push_back('\0');
    if (!uc_load(&path[0])) {
        char error[512] = {0};
        uc_error(error,sizeof(error));
        fprintf(stderr,"load failed: %s\n",error);
        return 4;
    }
    uc_run();

    expect(environment["VENV_ONE"] == "pre-alpha-post");
    expect(environment["VENV_TWO"] == "pre-beta-post");
    expect(commands.size() == 2);
    expect(shell_open == 0);

    uc_finis();

    // Interpreter teardown is where a poisoned allocator used to fault, so
    // keep allocating afterwards to give any damage a chance to surface.
    std::vector<std::string> traffic(64,std::string(96,'y'));
    traffic.assign(32,std::string(112,'z'));

    if (failures != 0) {
        fprintf(stderr,"native shell env: %d failures\n",failures);
        return 5;
    }
    puts("native-shell-env-ok");
    return 0;
}
