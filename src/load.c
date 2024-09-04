#include <stdio.h>
#include <stdlib.h>

#include "load.h"

#include "my_lib.h"

/* ---------------------------------------------------------------------------------------------------- */

static uint8_t *_load_stdin(FILE *stream);

static void error_fopen(const char *filename);

/* ---------------------------------------------------------------------------------------------------- */

uint8_t *load_code(const char *filename)
{
	uint8_t *code;

	if (filename == NULL)
	{
		code = load_stdin();
	}
	else
	{
		code = load_file(filename);
	}

	return code;
}

uint8_t *load_file(const char *filename)
{
	uint8_t *code;

	{
		FILE *f;

		f = fopen(filename, "r");

		if (!f)
		{
			error_fopen(filename);
		}

		code = read_file(f);

		fclose(f);
	}

	return code;
}

uint8_t *load_stdin(void)
{
	uint8_t *code;

	{
		FILE *f;

		f = tmpfile();

		if (!f)
		{
			error_fopen("tmp file");
		}

		code = _load_stdin(f);

		fclose(f);
	}

	return code;
}

/* ---------------------------------------------------------------------------------------------------- */

static uint8_t *_load_stdin(FILE *stream)
{
	uint8_t *code;

	read_stdin(stream);

	rewind(stream); // fseek(stream, 0, SEEK_SET)
	code = read_file(stream);

	return code;
}

/* ---------------------------------------------------------------------------------------------------- */

static void error_fopen(const char *filename)
{
	perror(filename);

	exit(1);
}
