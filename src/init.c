#include <stdio.h>
#include <stdlib.h>

#include "init.h"

#include "op.h"
#include "op.enum.h"

/* ---------------------------------------------------------------------------------------------------- */

void init_stack(struct stack *s, long size)
{
	if (size < 0) // if (size == 0) give a warning/info message ?
	{
		fprintf(stderr, "%s: %s: %ld\n", "ERROR", "negative stack size init", size);

		exit(1);
	}

	s->top = 0;
	s->size = size;

	s->o = malloc(sizeof(*s->o) * size);

	// printf("%s: %s: %ld\n", "INFO", "stack size", s->size);
}

void check_stack(struct stack *s)
{
	if (s->top > 0)
	{
		printf("%s: %s: %zu\n", "INFO", "objects on the stack", s->top);
	}
}

void free_stack(struct stack *s)
{
	// s->size = 0;

	free(s->o);
	s->o = NULL;
}

void set_ops(uint8_t *(**ops)(uint8_t *, struct stack *),
			 unsigned int ops_size,
			 uint8_t *(*op)(uint8_t *, struct stack *))
{
	unsigned int i;

	for (i = 0; i < ops_size; ++i)
	{
		ops[i] = op;
	}
}

void init_ops(uint8_t *(**ops)(uint8_t *, struct stack *))
{
	ops[OP_PUSH_CHAR]		= op_push_char;
	ops[OP_EMIT]			= op_emit;
	ops[OP_HALT]			= op_halt;
	ops[OP_EMIT_ASCII_CODE]	= op_emit_ASCII_code;
	ops[OP_SUM_TOP]			= op_sum_top;
	ops[OP_SWITCH_TOP]		= op_switch_top;
}
