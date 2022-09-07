#include "shell.h"


/**
 * execute_logic - Handles execution without logical && or ||
 * @args: command arguement to be executed
 * @var: global shell variable
 *
 * Return;
 */

void execute_logic(char *args, shell_t *var)
{
	char **command;
	int command_type;

	command = tokenize(args, DELIM);
	if (!(command[0]))
	{
		free(command);
		return;
	}
	command_type = check_cmd_type(command[0]);
	replace_vars(command, var);
	shell_execute(command, command_type, var);
	free_tokenized(command);
	free(args);
}


/**
 * logic_token - split a string base on a string
 * @str: string to split
 * Return: pointer to new or NULL
 */
char **logic_token(char *str)
{
	int j = 0, i = 0;
	char **res;

	if (!str)
		return (0);
	res = malloc(3 * sizeof(char *));
	for (; str[i]; i++)
	{
		j = startsWith(str + i, "&&");
		if (j)
		{
			res[0] = _strndup(str, i);
			res[1] = _strdup("&&");
			res[2] = str + i + j;
			return (res);
		}
		j = startsWith(str + i, "||");
		if (j)
		{
			res[0] = _strndup(str, i);
			res[1] = _strdup("||");
			res[2] = str + i + j;
			return (res);
		}
	}
	res[0] = _strdup(str);
	res[1] = 0;
	res[2] = 0;
	return (res);
}


/**
 * logic_token_help - helper function to handle logic token
 * @line: line entered by the user
 * @var: global shell variable
 *
 */

void logic_token_help(char *line, shell_t *var)
{
	int i = 0;
	char **args, **logic_cmd, *op;

	remove_comment(line);
	args = tokenize(line, ";");

	while (args[i])
	{
		logic_cmd = logic_token(args[i++]);
		op = logic_cmd[1];
		while (logic_cmd[0])
		{
			execute_logic(logic_cmd[0], var);
			var->cmd_counter += 1;
			if (!logic_cmd[2])
				break;
			if (_strcmp(op, AND_DELIM) == 0)
			{
				if (var->err_status == 0)
					logic_cmd = logic_token(logic_cmd[2]);
				else
				{
					free_tokenized(logic_cmd);
					break;
				}
			}
			else if (_strcmp(op, OR_DELIM) == 0)
			{
				if (var->err_status != 0)
					logic_cmd = logic_token(logic_cmd[2]);
				else
				{
					free_tokenized(logic_cmd);
					break;
				}
			}
		}
		free(logic_cmd);
	}
	free_tokenized(args);
}
