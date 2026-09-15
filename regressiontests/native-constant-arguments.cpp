#include <underc/ucdl.h>
#include <stdio.h>
#include <string.h>
#include <string>
#include <vector>

static int failures;
static int calls;
static int native3_calls;

static void expect_string(const char *actual, const char *expected)
{
    if (!actual || strcmp(actual,expected) != 0) ++failures;
}

static void native2(const char *a, int value)
{
    expect_string(a,"a");
    if (value != 1) ++failures;
    ++calls;
}

static void native3(const char *a, const char *b, int value)
{
    static const int expected_prefix[] = {1,0,1,2};
    expect_string(a,"a");
    expect_string(b,"b");
    const int expected = native3_calls < 4 ? expected_prefix[native3_calls] : 1;
    if (value != expected) ++failures;
    ++native3_calls;

    // Match the real-world trigger: the imported native allocates and frees
    // strings between calls, making damage visible before interpreter cleanup.
    if (native3_calls <= 4) {
        std::vector<std::string> heap_traffic(8,std::string(80,'x'));
        if (heap_traffic.back().size() != 80) ++failures;
    }
    ++calls;
}

static void native4(const char *a, const char *b, const char *c, int value)
{
    expect_string(a,"a");
    expect_string(b,"b");
    expect_string(c,"c");
    if (value != 1) ++failures;
    ++calls;
}

static void native_first(int value, const char *a, const char *b)
{
    if (value != 1) ++failures;
    expect_string(a,"a");
    expect_string(b,"b");
    ++calls;
}

static void native_middle(const char *a, int value, const char *b)
{
    expect_string(a,"a");
    if (value != 1) ++failures;
    expect_string(b,"b");
    ++calls;
}

static int import_function(char *declaration, void *function)
{
    if (uc_import(declaration,function)) return 1;
    char error[512] = {0};
    uc_error(error,sizeof(error));
    fprintf(stderr,"import failed for %s: %s\n",declaration,error);
    return 0;
}

static int execute(const char *source)
{
    if (uc_exec(source)) return 1;
    char error[512] = {0};
    uc_error(error,sizeof(error));
    fprintf(stderr,"source failed: %s\n",error);
    return 0;
}

int main()
{
    // The embedding path that exposed the corruption loads the standard
    // prelude. Keep the regression on that exact initialization mode.
    if (!uc_init(NULL,1)) return 1;
    char declaration2[] = "void native2(const char*,int);";
    char declaration3[] = "void native3(const char*,const char*,int);";
    char declaration4[] = "void native4(const char*,const char*,const char*,int);";
    char declaration_first[] = "void native_first(int,const char*,const char*);";
    char declaration_middle[] = "void native_middle(const char*,int,const char*);";
    if (!import_function(declaration2,reinterpret_cast<void *>(&native2)) ||
        !import_function(declaration3,reinterpret_cast<void *>(&native3)) ||
        !import_function(declaration4,reinterpret_cast<void *>(&native4)) ||
        !import_function(declaration_first,reinterpret_cast<void *>(&native_first)) ||
        !import_function(declaration_middle,reinterpret_cast<void *>(&native_middle))) return 2;

    if (!execute("enum Switch { SWITCH_OFF=0, SWITCH_ON=1, SWITCH_OTHER=2 };")) return 3;
    if (!execute("void exercise_constants(){int i; native2(\"a\",true); native3(\"a\",\"b\",true); native3(\"a\",\"b\",false); native3(\"a\",\"b\",SWITCH_ON); native3(\"a\",\"b\",SWITCH_OTHER); native4(\"a\",\"b\",\"c\",true); native_first(true,\"a\",\"b\"); native_middle(\"a\",true,\"b\"); for(i=0;i<32;++i) native3(\"a\",\"b\",true);}")) return 4;
    if (!execute("exercise_constants();")) return 5;
    std::vector<std::string> heap_traffic(32,std::string(80,'x'));

    const int expected_calls = 8 + 32;
    int ok = failures == 0 && calls == expected_calls && native3_calls == 4 + 32;
    uc_finis();
    heap_traffic.assign(8,std::string(96,'y'));
    if (!ok) {
        fprintf(stderr,"native constants: calls=%d expected=%d native3=%d failures=%d\n",
                calls,expected_calls,native3_calls,failures);
        return 6;
    }
    puts("native-constant-arguments-ok");
    return 0;
}
