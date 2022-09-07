#include "shell.h"

/**
 * shell_loop - read a line(user input)
 *			check if the shell should be ran interactively or not
 *			remove comments from line if any
 *			parse or tokenize the read line
 *			execute the parsed command
 *			runs infinitely unless user types exit or CTRL-D
 * @var: shell global variable
 */

void shell_loop(shell_t *var)
{
	char *line;

	/* handle program interruption if CTRL-C is pressed */
	signal(SIGINT, ctrl_C_func);
	while (1)
	{
		non_interractive(var);
		_printf(" ($) ", STDOUT_FILENO);
		line = shell_readline();
		if (!_strlen(line))
		{
			free(line);
			if (isatty(STDIN_FILENO))
				continue;
		}
		if (!line)
		{
			if (isatty(STDIN_FILENO))
				break;
		}

		logic_token_help(line, var);
		free(line);
	}
}


/**
 * non_interractive - runs the shell in non interactive mode
 * @p: shell Global variable
 */

void non_interractive(shell_t *p)
{
	char **args, **logic_cmd;
	char *line, *op;
	int i = 0;

	if (isatty(STDIN_FILENO) == 0)
	{
		line = shell_readline();
		remove_comment(line);
		args = tokenize(line, ";");
		while (args[i])
		{
			logic_cmd = logic_token(args[i++]);
			op = logic_cmd[1];
			while (logic_cmd[0])
			{
				execute_logic(logic_cmd[0], p);
				p->cmd_counter += 1;
				if (!logic_cmd[2])
					break;
				if (_strcmp(op, AND_DELIM) == 0)
				{
					if (p->err_status == 0)
						logic_cmd = logic_token(logic_cmd[2]);
					else
						break;
				}
				else if (_strcmp(op, OR_DELIM) == 0)
				{
					if (p->err_status != 0)
						logic_cmd = logic_token(logic_cmd[2]);
					else
						break;
				}
			}
		}
		free_tokenized(args);
		free_tokenized(environ);
		free(line);
	}
}


/**
 * check_cmd_type - determines the type of the command
 * @command: command to be checked
 *
 * Return: constant variable representing the type of command
 */

int check_cmd_type(char *command)
{
	static char *internal_cmd[] = {
		"exit", "cd", "help", "env", "setenv",
		"unsetenv", "alias", NULL
	};
	char *path = NULL;
	int i = 0;

	while (command[i])
	{
		if (command[i++] == '/')
			return (TERM_CMD);
	}
	for (i = 0; internal_cmd[i]; i++)
	{
		if (_strcmp(command, internal_cmd[i]) == 0)
			return (INTERNAL_CMD);
	}
	path = check_path(command);
	if (path)
	{
		free(path);
		return (PATH_CMD);
	}
	return (INVALID_CMD);
}

/**
 * shell_execute - launches the command to be executed
 * @command: command to be launched
 * @cmd_type: type of the command to be executed
 * @var: struct for shell name and old path
 * Return: 1 always
 */
void shell_execute(char **command, int cmd_type, shell_t *var)
{
	pid_t PID, W_PID __attribute__((unused));
	int state;

	if (cmd_type == PATH_CMD || cmd_type == TERM_CMD)
	{
		PID = fork();
		if (PID == 0)
		{
			shell_launch(command, cmd_type, var);
		}
		else if (PID < 0)
		{
			perror("Error Creating fork");
			return;
		}
		else
		{
			do {
				W_PID = waitpid(PID, &state, WUNTRACED);
			} while (!WIFEXITED(state) && !WIFSIGNALED(state));
		}
	}
	else
		shell_launch(command, cmd_type, var);
	var->err_status = state / 256;
}

/**
 * _strcpy - copy a string from src to dest
 * @dest: destination
 * @src: source
 *
 * Return: copied string
 */

char *_strcpy(char *dest, char *src)
{
	int i;

	for (i = 0; src[i]; i++)
		dest[i] = src[i];
	dest[i] = '\0';

	return (dest);
}
