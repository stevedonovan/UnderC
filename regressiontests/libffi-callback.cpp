#include <underc/ucdl.h>
#include <underc/ucri.h>
#include <stdio.h>
#include <stdlib.h>
#include <string>

typedef int (*IntCallback)(int, int, int, int, int, int, int, int);
typedef double (*DoubleCallback)(double, float, int);
typedef int (*ZeroCallback)();
typedef int (*PointerCallback)(int *);
typedef int (*MethodCallback)(void *, int);
typedef int (*RecursiveCallback)(int);

static int host_recurse(RecursiveCallback callback, int value)
{
    return callback(value);
}

int main()
{
    if (!uc_init(NULL,0)) return 1;
    char int_args[] = "int a,int b,int c,int d,int e,int f,int g,int h";
    char int_expr[] = "a+b+c+d+e+f+g+h";
    IntCallback sum = (IntCallback)uc_compile_fn(int_args,int_expr);
    char double_args[] = "double a,float b,int c";
    char double_expr[] = "a+b+c";
    DoubleCallback mixed = (DoubleCallback)uc_compile_fn(double_args,double_expr);
    char no_args[] = "";
    char answer[] = "42";
    ZeroCallback zero = (ZeroCallback)uc_compile_fn(no_args,answer);
    char pointer_args[] = "int *p";
    char pointer_expr[] = "p[0]+0";
    PointerCallback pointer = (PointerCallback)uc_compile_fn(pointer_args,pointer_expr);
    int value = 9;
    int int_result = sum ? sum(1,2,3,4,5,6,7,8) : -1;
    double double_result = mixed ? mixed(1.25,2.5f,3) : -1.0;
    int zero_result = zero ? zero() : -1;
    int pointer_result = pointer ? pointer(&value) : -1;
    char recurse_declaration[] = "int host_recurse(int (*callback)(int),int value);";
    if (!uc_import(recurse_declaration,reinterpret_cast<void *>(&host_recurse))) return 3;
    if (!uc_exec("int bounce(int n){if(n==0)return 0;return host_recurse(bounce,n-1)+1;}")) {
        char callback_error[256] = {0}; uc_error(callback_error,sizeof(callback_error));
        fprintf(stderr,"recursive callback source: %s\n",callback_error);
        return 4;
    }
    std::string method_source = std::string(getenv("UC_HOME")) +
                                "/regressiontests/callback-method-source.cpp";
    if (!uc_load(method_source.c_str())) {
        char callback_error[256] = {0}; uc_error(callback_error,sizeof(callback_error));
        fprintf(stderr,"method callback source: %s\n",callback_error);
        return 5;
    }
    uc_ucri_init();
    XFunction *bounce_function = uc_global()->lookup("bounce")->function();
    XClass *callback_class = uc_global()->lookup_class("CallbackObject");
    XFunction *method_function = callback_class->lookup("add")->function();
    RecursiveCallback bounce = reinterpret_cast<RecursiveCallback>(bounce_function->fun());
    MethodCallback method = reinterpret_cast<MethodCallback>(method_function->fun());
    struct CallbackObjectStorage { int base; } object = {37};
    int recursive_result = bounce ? bounce(9) : -1;
    int method_result = method ? method(&object,5) : -1;
    int ok = int_result == 36 && double_result == 6.75 && zero_result == 42 &&
             pointer_result == value && recursive_result == 9 && method_result == 42;
    uc_finis();
    if (!ok) {
        fprintf(stderr,"callback results: int=%d double=%.2f zero=%d pointer=%d recursive=%d method=%d\n",
                int_result,double_result,zero_result,pointer_result,recursive_result,method_result);
        return 2;
    }
    printf("libffi callbacks passed\n");
    return 0;
}
