#include <underc/ucdl.h>
#include <stdio.h>

static int fail(int code)
{
    char error[512] = { 0 };
    uc_error(error,sizeof(error));
    fprintf(stderr,"embed binding failure %d: %s\n",code,error);
    return code;
}

int main()
{
    int count = 7;
    double scale = 2.5;

    if (uc_bind_variable("early",UC_TYPE_INT,&count) != UC_STATUS_NOT_INITIALIZED) return fail(1);
    uc_init(NULL,0);
    if (uc_bind_variable("count",UC_TYPE_INT,&count) != UC_STATUS_OK) return fail(2);
    if (uc_bind_variable("scale",UC_TYPE_DOUBLE,&scale) != UC_STATUS_OK) return fail(3);
    if (uc_bind_variable("count",UC_TYPE_INT,&count) != UC_STATUS_ALREADY_EXISTS) return fail(4);
    if (uc_bind_variable("not valid",UC_TYPE_INT,&count) != UC_STATUS_INVALID_ARGUMENT) return fail(5);
    if (uc_bind_variable("while",UC_TYPE_INT,&count) != UC_STATUS_INVALID_ARGUMENT) return fail(8);
    if (uc_bind_variable("missing",UC_TYPE_INT,NULL) != UC_STATUS_INVALID_ARGUMENT) return fail(9);
    if (uc_bind_variable("unknown",(uc_variable_type)999,&count) != UC_STATUS_UNSUPPORTED_TYPE) return fail(10);
    if (!uc_exec("count += 5; scale *= 2;")) return fail(6);
    uc_finis();

    if (count != 12 || scale != 5.0) return fail(7);
    printf("bound count=%d scale=%.1f\n",count,scale);
    return 0;
}
