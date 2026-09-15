#include <underc/ucdl.h>
#include <stdio.h>

int main()
{
    const char *source = "embed/ucload.cpp";

    uc_init(NULL,0);
    int ok = uc_exec("char *message = \"Started up\";")
          && uc_load(source)
          && uc_exec("change_message(); printf(\"%s\\n\",message);");
    uc_finis();
    return ok ? 0 : 1;
}
