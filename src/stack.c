#include <stdio.h>
#include <stdlib.h>
// #include <assert.h>

#include "stack.h"

/* ---------------------------------------------------------------------------------------------------- */

static void check_stack_overflow(size_t top, size_t size);
static void check_stack_underflow(int top);

static void error_stack(const char *err_msg);

/* ---------------------------------------------------------------------------------------------------- */

size_t stack_push(struct stack *s, struct object o)
{
	check_stack_overflow(s->top + 1, s->size);

	s->o[s->top++] = o;

	return s->top; // not used
}

size_t stack_pop(struct stack *s, struct object *o)
{
	check_stack_underflow(s->top - 1);

	*o = s->o[--s->top];

	return s->top; // not used
}

size_t stack_peek(struct stack *s, struct object *o) // not used
{
	check_stack_underflow(s->top - 1);

	*o = s->o[s->top - 1];

	return s->top;
}

/* ---------------------------------------------------------------------------------------------------- */

static void check_stack_overflow(size_t top, size_t size)
{
	if (top > size)
	{
		error_stack("stack overflow");
	}
}

static void check_stack_underflow(int top)
{
	if (top < 0)
	{
		error_stack("stack underflow");
	}
}

/* ---------------------------------------------------------------------------------------------------- */

static void error_stack(const char *err_msg)
{
	fflush(stdout);
	fprintf(stderr, "\nError: %s\n", err_msg);

	exit(1);
}
