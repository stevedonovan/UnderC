#include <stdio.h>
#include <ucri.h>

int main()
{
    uc_ucri_init();
    XNTable *global = uc_global();
    if (global == NULL) return 1;
    printf("self-import: %s\n", global->name());
    return 0;
}
