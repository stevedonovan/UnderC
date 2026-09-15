// Fblock.h

#ifndef __FBLOCK_H
#define __FBLOCK_H
#include "export.h"
#ifndef __UNDERC__
# include "vm_types.h"
#else
typedef int VMFrameSlots;
#endif

// FBlock contains all that the runtime system needs to know about a function
struct EXPORT FBlock {
    PInstruction pstart;     // actual pcode
    VMFrameSlots nlocal;
    VMFrameSlots nargs;
    VMFrameSlots ntotal;
    Table*    context;       // symbol table context
    Class*    class_ptr;     // class pointer - NULL if not method
    Entry*    entry;         // specific entry in table
    Function* function;      // actual corresponding function object
    void*     data;          // extra data (will be addr of wrapped native code)
    XTrace*   trace;         // optional trace object

    // more to follow....
    FBlock (PInstruction pc=NULL, VMFrameSlots na=0)
    { pstart = pc;  nargs = na; nlocal = 0; context = NULL; data = NULL; }

    void *native_addr()   { return data; }

    static FBlock *create(Entry *pe, Class *pc);
    void finalize(int sz);
};

typedef FBlock *PFBlock;
typedef FBlock **PPFBlock;

#endif




