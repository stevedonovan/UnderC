#include <underc/ucdl.h>
#include <stdio.h>

int main()
{
    int count = 6;
    double multiplier = 1.5;
    const char *message = "Started up";
    char declaration[128];

    uc_init(NULL,0);
    printf("before: count=%d multiplier=%.1f\n",count,multiplier);
    int ok = uc_bind_variable("count",UC_TYPE_INT,&count) == UC_STATUS_OK
          && uc_bind_variable("multiplier",UC_TYPE_DOUBLE,&multiplier) == UC_STATUS_OK
          && uc_exec("count += 4; multiplier *= 2;");
    if (ok)
        printf("after:  count=%d multiplier=%.1f\n",count,multiplier);

    snprintf(declaration,sizeof(declaration),"char *message = \"%s\";",message);
    ok = ok
      && uc_exec(declaration)
      && uc_load("embed/ucload.cpp")
      && uc_exec("change_message(); printf(\"%s\\n\",message);");
    uc_finis();
    return ok ? 0 : 1;
}
