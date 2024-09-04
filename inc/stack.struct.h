#ifndef STACK_STRUCT_H
#define STACK_STRUCT_H

/* ---------------------------------------------------------------------------------------------------- */

#include <stdlib.h>
#include <stdint.h>

/* ---------------------------------------------------------------------------------------------------- */

struct object;

struct stack
{
	size_t top;
	size_t size;

	struct object *o;
};

struct object
{
	uint8_t type;

	union // not used
	{
		uint8_t		u8; // used
		int8_t		i8;
		uint32_t	u32;
		int32_t		i32;

		void *ptr;
	};
};

/* ---------------------------------------------------------------------------------------------------- */

#endif // STACK_STRUCT_H
