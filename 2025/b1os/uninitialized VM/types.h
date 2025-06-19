#include <stdint.h>

struct VM
{
  uint8_t *_pc;
  uint8_t *stack_ptr;
  uint8_t *stack_top;
  uint8_t *regs[8];
  uint8_t *pc;
  uint16_t bytecode_len;
};

struct Mem
{
  char code[256];
  char stack[2040];
  char stack_top[8];
};

