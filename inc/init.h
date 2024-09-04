// #ifndef
// #define

/* ---------------------------------------------------------------------------------------------------- */

#include "stack.struct.h"

/* ---------------------------------------------------------------------------------------------------- */

void init_stack(struct stack *s, long size);
void check_stack(struct stack *s);
void free_stack(struct stack *s);
void set_ops(uint8_t *(**ops)(uint8_t *, struct stack *),
			 unsigned int ops_size,
			 uint8_t *(*op)(uint8_t *, struct stack *));
void init_ops(uint8_t *(**ops)(uint8_t *, struct stack *));

/* ---------------------------------------------------------------------------------------------------- */

// #endif //
