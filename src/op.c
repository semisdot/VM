#include <stdio.h>

#include "op.h"

#include "h.h"
#include "stack.h"

/* ---------------------------------------------------------------------------------------------------- */

#define NEXT_INSTRUCTION_ADDRESS(ip) (ip)

/* ---------------------------------------------------------------------------------------------------- */

static void put_ASCII_code(uint8_t u8);
static uint8_t _op_sum_top(struct stack *s);

/* ---------------------------------------------------------------------------------------------------- */

uint8_t *op_nop(uint8_t *ip, struct stack *s)
{
	UNUSED_PARAMETER(s);

	return NEXT_INSTRUCTION_ADDRESS(ip + 1);
}

uint8_t *op_push_char(uint8_t *ip, struct stack *s)
{
	{
		struct object o;

		o.type = 'c';
		o.u8 = *(ip + 1);

		stack_push(s, o);
	}

	return NEXT_INSTRUCTION_ADDRESS(ip + 2);
}

uint8_t *op_emit(uint8_t *ip, struct stack *s)
{
	{
		struct object o;

		stack_pop(s, &o);

		putchar(o.u8);
	}

	return NEXT_INSTRUCTION_ADDRESS(ip + 1);
}

uint8_t *op_halt(uint8_t *ip, struct stack *s)
{
	UNUSED_PARAMETER(ip);
	UNUSED_PARAMETER(s);

	return NEXT_INSTRUCTION_ADDRESS(NULL);
}

uint8_t *op_emit_ASCII_code(uint8_t *ip, struct stack *s)
{
	{
		struct object o;

		stack_pop(s, &o);

		put_ASCII_code(o.u8);
	}

	return NEXT_INSTRUCTION_ADDRESS(ip + 1);
}

uint8_t *op_sum_top(uint8_t *ip, struct stack *s)
{
	{
		struct object o;

		o.type = 'c';
		o.u8 = _op_sum_top(s);

		stack_push(s, o);
	}

	return NEXT_INSTRUCTION_ADDRESS(ip + 1);
}

uint8_t *op_switch_top(uint8_t *ip, struct stack *s)
{
	{
		struct object o1, o2;

		stack_pop(s, &o1);
		stack_pop(s, &o2);

		stack_push(s, o1);
		stack_push(s, o2);
	}

	return NEXT_INSTRUCTION_ADDRESS(ip + 1);
}

/* ---------------------------------------------------------------------------------------------------- */

static uint8_t _op_sum_top(struct stack *s)
{
	uint8_t u8;

	{
		struct object o1, o2;

		stack_pop(s, &o1);
		stack_pop(s, &o2);

		u8 = o1.u8 + o2.u8;
	}

	return u8;
}

static void put_ASCII_code(uint8_t u8)
{
	if (u8 > 9)
	{
		put_ASCII_code(u8 / 10);

		u8 = u8 % 10; // == last digit // u8 = u8 - (u8 / 10) * 10
	}

	putchar(u8 + 48);
}
