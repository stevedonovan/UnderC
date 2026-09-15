#include <stdio.h>

int main()
{
    FILE *process;
    char line[256];

    process = popen("ls", "r");
    if (process == 0) return 1;
    while (fgets(line, sizeof(line), process) != 0)
        printf("%s", line);
    return pclose(process);
}
