// #ifndef
// #define

/* ---------------------------------------------------------------------------------------------------- */

#include "stack.struct.h"

/* ---------------------------------------------------------------------------------------------------- */

// #define MAX_OPS (UCHAR_MAX + 1) // 256

/* ---------------------------------------------------------------------------------------------------- */

uint8_t *op_nop(uint8_t *ip, struct stack *s);
uint8_t *op_push_char(uint8_t *ip, struct stack *s);
uint8_t *op_emit(uint8_t *ip, struct stack *s);
uint8_t *op_halt(uint8_t *ip, struct stack *s);
uint8_t *op_emit_ASCII_code(uint8_t *ip, struct stack *s);
uint8_t *op_sum_top(uint8_t *ip, struct stack *s);
uint8_t *op_switch_top(uint8_t *ip, struct stack *s);

/* ---------------------------------------------------------------------------------------------------- */

// #endif //
