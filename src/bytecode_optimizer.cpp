/* V8-inspired staged bytecode peephole optimizer.
 *
 * V8's interpreter optimizer combines local bytecode reductions, constant
 * folding, and control-flow simplification. UnderC is stack based, so the
 * same strategy is expressed as three increasingly aggressive passes.
 * Replaced instructions become NOP rather than being removed: UnderC stores
 * instruction indices in labels, switch tables, breakpoints, and line maps.
 */
#include "common.h"
#include "engine.h"
#include "opcodes.h"

static void make_nop(Instruction& instruction)
{
  instruction.opcode = NOP;
  instruction.rmode = NONE;
  instruction.data = 0;
}

static bool integer_constant(const Instruction& instruction, VMWord& value)
{
  if (instruction.opcode != PUSHI || instruction.rmode != DIRECT) return false;
  value = *(VMWord *)Parser::global().addr(instruction.data);
  return true;
}

static void replace_constant(Instruction& instruction, VMWord value)
{
  instruction.opcode = PUSHI;
  instruction.rmode = DIRECT;
  instruction.data = Parser::global().alloc(sizeof(VMWord),&value);
}

static bool fold_binary(int opcode, VMWord left, VMWord right, VMWord& result)
{
  switch (opcode) {
  case ADD: result = left + right; return true;
  case SUB: result = left - right; return true;
  case MUL: result = left * right; return true;
  case DIV: if (!right) return false; result = left / right; return true;
  case IDIV: if (!right) return false; result = (VMUWord)left / (VMUWord)right; return true;
  case MOD: if (!right) return false; result = left % right; return true;
  case AND: result = left & right; return true;
  case OR: result = left | right; return true;
  case XOR: result = left ^ right; return true;
  case EQ: result = left == right; return true;
  case NEQ: result = left != right; return true;
  case LESS: result = left < right; return true;
  case GREAT: result = left > right; return true;
  case LE: result = left <= right; return true;
  case GE: result = left >= right; return true;
  default: return false;
  }
}

static bool is_conditional_jump(int opcode)
{
  return opcode == JZ || opcode == JNZ || opcode == JZND || opcode == JNZND;
}

void optimize_bytecode(Instruction *code, int count, int level)
{
  int i;
  if (!code || count <= 0 || level <= 0) return;

  // Level 1: local stack-bytecode reductions.
  for (i = 0; i + 1 < count; ++i) {
    int first = code[i].opcode;
    if ((first == PUSHI || first == PUSHC || first == PUSHW || first == PUSHP ||
         first == PEA || first == PERA) && code[i + 1].opcode == DROP) {
      make_nop(code[i]);
      make_nop(code[i + 1]);
    } else if (first == DUP && code[i + 1].opcode == DROP) {
      make_nop(code[i]);
      make_nop(code[i + 1]);
    }
  }
  if (level < 2) return;

  // Level 2: constant folding and unary simplification.
  for (i = 0; i + 2 < count; ++i) {
    VMWord left, right, result;
    if (integer_constant(code[i],left) && integer_constant(code[i + 1],right) &&
        fold_binary(code[i + 2].opcode,left,right,result)) {
      replace_constant(code[i],result);
      make_nop(code[i + 1]);
      make_nop(code[i + 2]);
    }
  }
  for (i = 0; i + 1 < count; ++i) {
    VMWord value;
    if (!integer_constant(code[i],value)) continue;
    int opcode = code[i + 1].opcode;
    if (opcode == NEG) value = -value;
    else if (opcode == NOT) value = !value;
    else if (opcode == BNOT) value = ~value;
    else if (opcode == I2B) value = !!value;
    else continue;
    replace_constant(code[i],value);
    make_nop(code[i + 1]);
  }
  if (level < 3) return;

  // Level 3: strength reduction and jump threading.
  for (i = 0; i + 1 < count; ++i) {
    VMWord value;
    if (!integer_constant(code[i],value)) continue;
    int opcode = code[i + 1].opcode;
    if ((value == 0 && (opcode == ADD || opcode == SUB || opcode == OR ||
                        opcode == XOR || opcode == SHL || opcode == SHR)) ||
        (value == 1 && opcode == MUL)) {
      make_nop(code[i]);
      make_nop(code[i + 1]);
    }
  }
  for (i = 0; i < count; ++i) {
    int opcode = code[i].opcode;
    if (opcode != JMP && !is_conditional_jump(opcode)) continue;
    VMWord target = code[i].data;
    int guard = count;
    while (target >= 0 && target < count && code[target].opcode == JMP && guard-- > 0) {
      VMWord next = code[target].data;
      if (next == target) break;
      target = next;
    }
    code[i].data = target;
    if (opcode == JMP && target == i + 1) make_nop(code[i]);
  }
}
