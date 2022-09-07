#include "shell.h"

/**
 * print_error - prints an error
 *
 * @commands: commands array
 * @build: global shell variable
 */
void print_error(char **commands, shell_t *build)
{
	char *error;

	if (_strcmp(commands[0], "exit") == 0)
	{
		error = exit_error(commands, build);
	}
	else if (_strcmp(commands[0], "alias") == 0)
	{
		error = alias_error(commands, build);
	}
	else if (_strcmp(commands[0], "cd") == 0)
	{
		error = chdir_error(commands, build);
	}
	else if (build->err_status == -1)
	{
		error = env_error(commands, build);
	}
	else
	{
		error = invalid_cmd_error(commands, build);
	}
	_printf(error, STDERR_FILENO);
	free(error);

}

/**
 * env_error - prints an error
 *
 * @cmd: commands array
 * @build: global shell variable
 * Return: something
 */
char *env_error(char **cmd, shell_t *build)
{
	char *cmd_count = _itoa(build->cmd_counter), *msg;
	char *res;
	int len;

	msg = ": Unable to add/remove from environment\n";
	len = _strlen(cmd[0]) + _strlen(build->shell_name);
	len += _strlen(cmd_count) + _strlen(msg) + 4;
	res = malloc((len + 1) * sizeof(char));
	if (!res)
	{
		free(cmd_count);
		return (NULL);
	}
	_strcpy(res, build->shell_name);
	_strcat(res, ": ");
	_strcat(res, cmd_count);
	_strcat(res, ": ");
	_strcat(res, cmd[0]);
	_strcat(res, msg);
	_strcat(res, "\0");

	free(cmd_count);
	return (res);
}

/**
 * exit_error - prints an error
 *
 * @cmd: commands array
 * @build: global shell variable
 * Return: something
 */
char *exit_error(char **cmd, shell_t *build)
{
	char *cmd_count = _itoa(build->cmd_counter);
	char *res;
	int len;

	len = _strlen(cmd[0]) + _strlen(build->shell_name);
	len += _strlen(cmd_count) + _strlen(cmd[1]) + 23;

	res = malloc((len + 1) * sizeof(char));
	if (!res)
	{
		free(cmd_count);
		return (NULL);
	}
	_strcpy(res, build->shell_name);
	_strcat(res, ": ");
	_strcat(res, cmd_count);
	_strcat(res, ": ");
	_strcat(res, cmd[0]);
	_strcat(res, ": Illegal number: ");
	_strcat(res, cmd[1]);
	_strcat(res, "\n\0");
	free(cmd_count);

	return (res);
}

/**
 * invalid_cmd_error - prints an error
 *
 * @cmd: commands array
 * @build: global shell variable
 * Return: something
 */
char *invalid_cmd_error(char **cmd, shell_t *build)
{
	char *cmd_count = _itoa(build->cmd_counter), *msg;
	char *res;
	int len;

	msg = ": not found\n";
	len = _strlen(cmd[0]) + _strlen(build->shell_name);
	len += _strlen(cmd_count) + _strlen(msg) + 5;

	res = malloc((len + 1) * sizeof(char));
	if (!res)
	{
		free(cmd_count);
		return (NULL);
	}

	_strcpy(res, build->shell_name);
	_strcat(res, ": ");
	_strcat(res, cmd_count);
	_strcat(res, ": ");
	_strcat(res, cmd[0]);
	_strcat(res, msg);

	free(cmd_count);
	return (res);
}

/**
 * chdir_error - prints an error
 *
 * @cmd: commands array
 * @build: global shell variable
 * Return: something
 */
char *chdir_error(char **cmd, shell_t *build)
{
	char *cmd_count = _itoa(build->cmd_counter), *msg;
	char *res, illegal[3];
	int len_id, len;

	if (cmd[1][0] == '-')
		msg = ": Illegal option ", len_id = 2;
	else
		msg = ": can't cd to ", len_id = _strlen(cmd[1]);
	len = _strlen(cmd[0]) + _strlen(build->shell_name);
	len += len_id + _strlen(cmd_count) + _strlen(msg) + 5;
	res = malloc((len + 1) * sizeof(char));
	if (!res)
	{
		free(msg);
		return (NULL);
	}
	_strcpy(res, build->shell_name), _strcat(res, ": ");
	_strcat(res, cmd_count), _strcat(res, ": ");
	_strcat(res, cmd[0]), _strcat(res, msg);
	if (cmd[1][0] == '-')
	{
		illegal[0] = '-';
		illegal[1] = cmd[1][1];
		illegal[2] = '\0';
		_strcat(res, illegal);
	}
	else
	{
		_strcat(res, cmd[1]);
	}
	_strcat(res, "\n"), _strcat(res, "\0");
	free(cmd_count);
	return (res);
}
