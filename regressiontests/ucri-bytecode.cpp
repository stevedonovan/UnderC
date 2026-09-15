#include <underc/ucdl.h>
#include <underc/ucri.h>
#include <stdio.h>

int main()
{
    if (!uc_init(NULL,0)) return 1;
    if (!uc_exec("int bytecode_probe(int value) { return value+1; }")) return 2;
    uc_ucri_init();
    XEntry *entry = uc_global()->lookup("bytecode_probe");
    XFunction *function = entry ? entry->function() : NULL;
    if (!function || function->instruction_count() == 0) return 3;
    for (size_t index = 0; index < function->instruction_count(); ++index) {
        XInstructionInfo instruction;
        instruction.structure_size = sizeof(instruction);
        if (!function->instruction_at(index,&instruction) ||
            instruction.version != XINSTRUCTION_INFO_VERSION)
            return 4;
    }
    uc_finis();
    puts("ucri bytecode snapshot passed");
    return 0;
}
