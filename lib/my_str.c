
// #include <stdio.h>
#include <stdlib.h>
// #include <errno.h>

#include "my_str.h"

/* ---------------------------------------------------------------------------------------------------- */

int my_strtol(const char *nptr, long *nval)
{
	int ret = -1;
	char *endptr;
	long val;

	// errno = 0;

	if (nptr == NULL || nval == NULL)
	{
		goto end;
	}

	val = strtol(nptr, &endptr, 10);

#if 0
	if (errno == ERANGE)
	{
		goto end;
	}
#endif

	if (endptr == nptr || *endptr != '\0')
	{
		goto end;
	}

	*nval = val;

	ret = 0;

end:
	return ret;
}
