// A consumer of the installed headers never sees the interpreter's own
// compile definitions, so underc/vm_types.h has to reach the host ABI on its
// own: a 32-bit host must get a 32-bit VM word and a 64-bit host a 64-bit one.
// This translation unit is deliberately compiled without UNDERC_VM_BITS and
// without linking the library, so it fails if that derivation is ever lost.
#ifdef UNDERC_VM_BITS
# error "this regression must compile without a build-system-supplied UNDERC_VM_BITS"
#endif

#include <underc/vm_types.h>
#include <underc/ucdl.h>
#include <underc/ucembed.h>
#include <underc/ucri.h>
#include <underc/version.h>

#include <stddef.h>
#include <stdio.h>

struct AggregateProbe { char lead; double member; void *tail; };

int main()
{
    const int host_bits = (int)sizeof(void *) * 8;
    if (UNDERC_VM_BITS != host_bits) {
        printf("vm word is %d bits on a %d-bit host\n",(int)UNDERC_VM_BITS,host_bits);
        return 1;
    }
    if (sizeof(VMWord) != sizeof(void *)) return 2;
    if (!vm_can_transport_host_pointers()) return 3;
    // The interpreter lays out aggregates with this alignment, so it has to
    // agree with what the host compiler does to the same members: on 32-bit
    // MSVC a double is 8-aligned even though a pointer is only 4-aligned.
    if (vm_host_aggregate_double_alignment() != (int)offsetof(AggregateProbe,member)) {
        printf("double aligns to %d in an aggregate, interpreter assumes %d\n",
               (int)offsetof(AggregateProbe,member),vm_host_aggregate_double_alignment());
        return 4;
    }
    if (vm_default_object_alignment() < (int)sizeof(void *)) return 5;
    if (vm_default_object_alignment() < vm_host_aggregate_double_alignment()) return 6;
    printf("host-abi-width=%d\n",(int)UNDERC_VM_BITS);
    return 0;
}
