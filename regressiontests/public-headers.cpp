#include <underc/ucdl.h>
#include <underc/ucri.h>
#include <underc/version.h>

#include <stdio.h>

int main()
{
    XInstructionInfo instruction;
    instruction.structure_size = sizeof(instruction);
    instruction.version = XINSTRUCTION_INFO_VERSION;
    printf("public-header-layout=%s\n", UNDERC_VERSION);
    return instruction.version == 1 ? 0 : 1;
}
