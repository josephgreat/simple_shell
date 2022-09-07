#include "shell.h"

/**
 * handle_setenv - sets an environment var
 * @args: command entered
 * @p: shell global variable
 *
 */
void handle_setenv(char **args, shell_t *p)
{
	int i = 0;

	while (args[i])
		i++;
	if (i != 3 || !args[1] || !args[2])
	{
		p->err_status = -1;
		print_error(args, p);
		return;
	}
	i = _setenv(args[1], args[2]);
	if (i)
		_printf("setenv: invalid arguments\n", STDERR_FILENO);

	p->err_status = 0;
}

/**
 * handle_unsetenv - unsets an environment var
 * @args: command entered
 * @p: shell global variable
 *
 */
void handle_unsetenv(char **args, shell_t *p)
{
	int i = 0;

	while (args[i])
		i++;
	if (i != 2 || !args[1])
	{
		p->err_status = -1;
		print_error(args, p);
		return;
	}
	i = _unsetenv(args[1]);
	if (i)
	{
		p->err_status = -1;
		print_error(args, p);
		return;
	}

	p->err_status = 0;
}

/**
 * aliasFunc - handles aliases for commands
 * @args: command entered
 * @p: shell global variable
 *
 */
void aliasFunc(char **args, shell_t *p)
{
	int i = 0, j = 0;

	if (args[1] == NULL && p->aliases)
	{
		if (p->aliases[i] == NULL)
		{
			return;
		}
		while (p->aliases[i])
		{
			_printf(p->aliases[i++], STDOUT_FILENO);
			_printf("\n", STDOUT_FILENO);
		}
		p->err_status = 0;
		return;
	}
	for (i = 1; args[i]; i++)
	{
		if (is_delimeter(args[i], '=') == 0)
		{
			j = 0;
			while (p->aliases[j])
			{
				if (_strcmp(p->aliases[j], args[i]) == 0)
				{
					_printf(p->aliases[j], STDOUT_FILENO);
					_printf("\n", STDOUT_FILENO);
					break;
				}
				j++;
			}
			if (!p->aliases)
			{
				print_error(args, p), p->err_status = 1;
			}
		}
		else
			set_alias(args[i], p);
	}
	p->err_status = 0;
}


/**
 * set_alias - set aliases according to a key value pair
 * @key_val: key value pair to be set
 * @var: global struct shell variables
 *
 */

void set_alias(char *key_val, shell_t *var)
{
	char **tmp = tokenize(key_val, "="), **temp;
	char *key = tmp[0];
	int i = 0;

	while (var->aliases && var->aliases[i])
	{
		if (startsWith(var->aliases[i], key))
		{
			free(var->aliases[i]);
			var->aliases[i] = _strdup(key_val);
			free_tokenized(tmp);
			return;
		}
		i++;
	}
	temp = malloc((i + 2) * sizeof(char *));
	if (!temp)
		return;
	for (i = 0; var->aliases && var->aliases[i]; i++)
		temp[i] = var->aliases[i];

	temp[i++] = _strdup(key_val);
	temp[i] = NULL;
	free(var->aliases);
	var->aliases = temp;
	free_tokenized(tmp);
	var->err_status = 0;
}

/**
 * alias_error - print error message associated with alias
 * @cmd: list of arguements supplied
 * @var: global struct shell vaiables
 *
 * Return: the error message to be printed
 */

char *alias_error(char **cmd, shell_t *var __attribute__((unused)))
{
	char *res, *msg;
	int len;

	msg = " not found\n";
	len = _strlen(cmd[0]) + _strlen(msg) + _strlen(cmd[1]);

	res = malloc((len + 3) * sizeof(char));
	if (!res)
	{
		return (NULL);
	}

	_strcpy(res, cmd[0]);
	_strcat(res, ": ");
	_strcat(res, cmd[1]);
	_strcat(res, msg);

	return (res);
}
