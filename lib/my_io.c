
#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <fcntl.h>

#include "my_io.h"

/* ---------------------------------------------------------------------------------------------------- */

static void _add_eol(FILE *stream);

/* ---------------------------------------------------------------------------------------------------- */

int read_stream(FILE *in_stream, FILE *out_stream)
{
	int ret = -1;
	int chr;

	if (in_stream == NULL || out_stream == NULL)
	{
		goto end;
	}

	while ((chr = fgetc(in_stream)) != EOF)
	{
		fputc(chr, out_stream);
	}

#if 0
	if (!feof(in_stream))
	{
		// EOF not reached
		goto end;
	}
#endif

	ret = 0;

end:
	return ret;
}

int read_stdin(FILE *out_stream)
{
	int ret;

	ret = read_stream(stdin, out_stream);

	return ret;
}

int my_fsize(FILE *stream)
{
	int ret = -1;
	int cur;
	int size;

	if (stream == NULL)
	{
		goto end;
	}

	cur = ftell(stream);

	fseek(stream, 0, SEEK_END);
	size = ftell(stream);

	fseek(stream, cur, SEEK_SET);

	ret = size;

end:
	return ret;
}

char *read_file(FILE *stream) // use my_fsize() ?!
{
	char *code = NULL;

	{
		struct stat st;

		fstat(fileno(stream), &st); // fileno() returns the file descriptor number // gets status information about the file specified by the open file descriptor and stores it

		if (st.st_size) // malloc(0) // if (st.st_size == 0) return NULL
		{
			code = malloc(st.st_size); // allocate space for the array
			fread(code, sizeof(*code), st.st_size, stream); // reads data from the stream into the array pointed to, by pointer
		}
	}

	return code;
}

static void _add_eol(FILE *stream)
{
	int chr;

	chr = fgetc(stream);

	if (chr != '\n')
	{
		fputc('\n', stream);
	}
}

int add_eol(FILE *stream)
{
	int ret = -1;
	int cur;

	if (stream == NULL)
	{
		goto end;
	}

#if 0
	if (fcntl_accmode(stream) != O_RDWR)
	{
		goto end;
	}
#endif

	cur = ftell(stream);

	fseek(stream, -1, SEEK_END);

	_add_eol(stream);

	fseek(stream, cur, SEEK_SET);

	ret = 0;

end:
	return ret;
}

int fcntl_accmode(FILE *stream)
{
	int ret = -1;
	int fd;
	int flags;
	int accmode;

	if (stream == NULL)
	{
		goto end;
	}

	fd = fileno(stream);

	flags = fcntl(fd, F_GETFL);
	accmode = flags & O_ACCMODE;

	ret = accmode;

end:
	return ret;
}
