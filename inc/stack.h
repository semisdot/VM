// #ifndef
// #define

/* ---------------------------------------------------------------------------------------------------- */

#include "stack.struct.h"

/* ---------------------------------------------------------------------------------------------------- */

size_t stack_push(struct stack *s, struct object o);
size_t stack_pop(struct stack *s, struct object *o);
size_t stack_peek(struct stack *s, struct object *o);

/* ---------------------------------------------------------------------------------------------------- */

// #endif //
