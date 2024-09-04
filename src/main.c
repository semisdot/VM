#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <getopt.h>

#include "main.h"

#include "my_lib.h"

#include "vm.h"
#include "load.h"
#include "init.h"
#include "op.h"

/* ---------------------------------------------------------------------------------------------------- */

#define STACK_SIZE	1024
#define OPS_SIZE	128

/* ---------------------------------------------------------------------------------------------------- */

struct command_line_opts
{
	long stack_size;
};

struct command_line_args
{
	char *filename;
};

#if 0
struct command_line // cl
{
	struct command_line_opts;
	struct command_line_args;
};
#endif

/* ---------------------------------------------------------------------------------------------------- */

static void set_command_line_opts(struct command_line_opts *opts);
static void handle_command_line_opts(int argc, char **argv, struct command_line_opts *opts);
// static void set_command_line_args(struct command_line_args *args);
static void handle_command_line_args(int argc, char **argv, struct command_line_args *args);

static void error_usage(const char *err_msg);

/* ---------------------------------------------------------------------------------------------------- */

int main(int argc, char **argv)
{
	struct command_line_opts opts;
	struct command_line_args args;

	set_command_line_opts(&opts);
	handle_command_line_opts(argc, argv, &opts);

	argc -= optind;
	argv += optind;

	// set_command_line_args(&args);
	handle_command_line_args(argc, argv, &args);

	{
		uint8_t *code;
		struct stack s;
		uint8_t *(*ops[OPS_SIZE])(uint8_t *, struct stack *); // array of function pointers, DON'T PANIC!

		code = load_code(args.filename);

		init_stack(&s, opts.stack_size);

		set_ops(ops, OPS_SIZE, op_nop);
		init_ops(ops);

		vm_run(code, &s, ops);

		check_stack(&s);

#if 0
		free_stack(&s);

		free(code);
		code = NULL;
#endif
	}

	return 0;
}

/* ---------------------------------------------------------------------------------------------------- */

static void set_command_line_opts(struct command_line_opts *opts)
{
	opts->stack_size = STACK_SIZE;
}

static void handle_command_line_opts(int argc, char **argv, struct command_line_opts *opts)
{
	struct option long_options[] =
	{
		{STACK_SIZE_OPT, required_argument, 0, 's'},
		{0, 0, 0, 0}
	};

	int opt;

	while ((opt = getopt_long(argc, argv, "", long_options, 0)) != -1)
	{
		switch (opt)
		{
			case 's':
			{
				my_strtol(optarg, &opts->stack_size);

				break;
			}

			default: // case '?'
			{
				exit(1);

				// break;
			}
		}
	}
}

static void handle_command_line_args(int argc, char **argv, struct command_line_args *args)
{
	if (argc == 0)
	{
		args->filename = NULL;
	}
	else if (argc == 1)
	{
		args->filename = argv[argc - 1];
	}
	else
	{
		error_usage("vm usage");
	}
}

static void error_usage(const char *err_msg)
{
	fprintf(stderr, "Error: %s\n", err_msg);

	exit(1);
}
