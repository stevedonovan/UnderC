// ENGINE.H
#ifndef __ENGINE_H
#define __ENGINE_H

#include "class.h"
#include "vm_types.h"

struct FBlock;

struct ArgBlock {
    char *OPtr;
    int  no;
    VMWord values[256];
    VMWord ret1;
    double ret2;
	long ret_addr;
	long esi_ptr;
    long edi_ptr;
	int flags;
};

namespace Engine { 
    bool paused();
    bool running();
    void kill(int retcode = 0);
    void  object_ptr(void *);
    void *object_ptr();
    char **object_ptr_addr();
    int __STDCALL execute(FBlock *fb,int flags = 0, ArgBlock *xargs = NULL);
    int __STDCALL stub_execute(FBlock* _fb, int flags, ArgBlock *xargs);
    void set_data_seg(void *ptr);
    void global_unwind();
    void set_frame(int i,bool verbose);  
    void attach_main_context(char *fct); 
    int  retval();
    bool set_single_stepping(bool yesno);
	void reset_single_stepping();
    enum {RESUME=1,ARGS_PASSED=2,METHOD_CALL=4,RETURN_32=8,RETURN_64=16,FROM_OUTSIDE=32};

};

const int TMP_BUFF_SIZE = 24;

typedef unsigned int uint;

// Instruction operands follow the configured VM word size.
struct Instruction {
  uint opcode;
  uint rmode;
  VMWord data;
};
typedef Instruction *PInstruction;

// these functions define the Virtual Method Table structure of UC

class Class;
typedef Class **PPClass; 

inline PPClass *VMT(void *p)
{
  // The hidden table pointer sits in the VM word immediately before the
  // object; add_variable() and the allocators reserve exactly that much.
  return (PPClass *)( (char *)p - sizeof(VMWord) );
}


///// interface used by the parser to drive the code generation
const int CODE_BUFFSIZE = 1000;
class CodeGenerator {
  Instruction _code_buff_[CODE_BUFFSIZE];
  Instruction *pcode;
  int NC, mTotal;

public:

  CodeGenerator() : NC(0), mTotal(0), pcode(_code_buff_) { }
    
  void begin_code();
  Instruction *current_pi();
  Instruction *last_pi();
  int total_instructions();
  int ip_offset();
  void backspace();
  void emitc(int opc, RMode rm=NONE, VMWord data=0);
  void out(Instruction *is);
  Instruction *end_code();
  static Instruction *instruction_with_pointer(int opcode, void *ptr);
  // *add 1.2.3a Returns non-NULL ptr to instruction if this function
// has exactly one instruction
  static Instruction* has_one_instruction(Function* pf);
};

// Optimize a complete code buffer in place. Instruction positions are retained
// so branch, switch, breakpoint, and source-location offsets stay valid.
void optimize_bytecode(Instruction *code, int count, int level);

struct CatchBlock {
  Type type;
  int  ip_offset;   
};

typedef std::list<CatchBlock *> CatchBlockList;
class Label;

class CatchHandler {
private:
  CatchBlockList m_catch_blocks;
  FBlock *m_fb;
  Label *m_end_label;
  void *m_thrown_object;
  Type m_thrown_type;
public:
  CatchHandler(FBlock *fb);
  void add_catch_block(Type t, int ip_offs);
  int match_thrown_object(Type t, void *obj);

  Label *label()      { return m_end_label; }
  FBlock *fun_block() { return m_fb; }
  void *thrown_object() { return m_thrown_object; }
  Type  thrown_type()   { return m_thrown_type; }

};



#endif
