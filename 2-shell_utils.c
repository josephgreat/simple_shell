#include "shell.h"

/**
 * ctrl_C_func - handles the signal raised by CTRL-C
 * @signum: signal number
 */
void ctrl_C_func(int signum)
{
	if (signum == SIGINT)
		_printf("\n ($) ", STDIN_FILENO);
}

/**
 * shell_readline - read line from stdin
 *
 * Return: line read
 */

char *shell_readline(void)
{
	int bufsize = RL_BUFSIZE, nRead, position = 0;
	char c,  *buffer = malloc(bufsize * sizeof(char));

	if (!buffer)
	{
		perror("Failed to allocate space in memory");
		free_tokenized(environ);
		exit(EXIT_FAILURE);
	}

	while (1)
	{
		nRead = read(STDIN_FILENO, &c, 1);
		if (c == EOF || !nRead)
		{
			if (isatty(STDIN_FILENO))
			{
				free(buffer), _printf("\n", STDIN_FILENO);
				return (NULL);
			}
		}
		else if (c == '\n' || !nRead)
		{
			buffer[position] = '\0';
			return (buffer);
		}
		else
			buffer[position] = c;
		position++;
		if (position >= bufsize)
		{
			bufsize += RL_BUFSIZE;
			buffer = _realloc(buffer, RL_BUFSIZE, bufsize);
			if (!buffer)
			{
				free_tokenized(environ);
				exit(EXIT_FAILURE);
			}
		}
	}
}

/**
 * shell_launch - executes a command based on it type
 * @proccessed_cmd: processed character array
 * @cmd_type: the type of the command
 * @p: global shell variables
 */

void shell_launch(char **proccessed_cmd, int cmd_type, shell_t *p)
{
	void (*func)(char **command, shell_t *var);

	signal(SIGINT, SIG_DFL);
	switch (cmd_type)
	{
		case TERM_CMD:
			{
				if (execve(proccessed_cmd[0], proccessed_cmd, NULL) == -1)
				{
					perror(_getenv("PWD"));
					free_tokenized(environ);
					exit(2);
				}
				break;
			}
		case PATH_CMD:
			{
				if (execve(check_path(proccessed_cmd[0]), proccessed_cmd, NULL)
						== -1)
				{
					perror(_getenv("PWD"));
					free_tokenized(environ);
					exit(2);
				}
				break;
			}
		case INTERNAL_CMD:
			{
				func = get_func(proccessed_cmd[0]);
				func(proccessed_cmd, p);
				break;
			}
		case INVALID_CMD:
			{
				print_error(proccessed_cmd, p);
				p->err_status = 2;
			}
	}
	p->err_status = 0;
}

/**
 * get_func - retrieves a function based on the command given and a mapping
 * @command: string to check against the mapping
 *
 * Return: pointer to the proper function, or null on fail
 */
void (*get_func(char *command))(char **, shell_t *)
{
	int i;
	function_map mapping[] = {
		{"env", env},
		{"exit", quit},
		{"cd", ch_dir},
		{"help", display_help},
		{"alias", aliasFunc},
		{"setenv", handle_setenv},
		{"unsetenv", handle_unsetenv}
	};

	for (i = 0; i < 7; i++)
	{
		if (_strcmp(command, mapping[i].command_name) == 0)
			return (mapping[i].func);
	}
	return (NULL);
}
