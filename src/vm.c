#include "vm.h"

/* ---------------------------------------------------------------------------------------------------- */

void vm_run(uint8_t *ip, // instruction pointer
			struct stack *s,
			uint8_t *(**ops)(uint8_t *, struct stack *))
{
	while (ip)
	{
		ip = ops[*ip](ip, s); // instruction
	}
}
