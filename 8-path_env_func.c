#include "shell.h"

/**
 * _getenv - gets an environment variable
 *
 * @key: key of the variable
 * Return: address of value of key if found
 * null if not found
 */
char *_getenv(char *key)
{
	char **envs;
	int i, j;

	if (!key)
		return (0);
	for (i = 0, envs = environ; envs[i]; i++)
	{
		j = startsWith(envs[i], key);
		if (j)
			return (envs[i] + 1 + j);
	}
	return (0);
}


/**
 * check_path - find the path of a cmd
 *
 * @file: the command to find its full path
 * Return: pointer to full path
 */
char *check_path(char *file)
{
	char *path, **paths, *res = NULL;
	int i = 0;

	path = _getenv("PATH");
	if (!path || !(_strlen(path)))
		return (0);
	paths = tokenize(path, ":");
	if (!paths)
		return (0);
	for (; paths[i]; i++)
	{
		res = malloc(_strlen(paths[i]) + _strlen(file) + 2);
		res[0] = '\0';
		res = _strcat(res, paths[i]);
		res = _strcat(res, "/");
		res = _strcat(res, file);
		if (access(res, F_OK) == 0)
		{
			free_tokenized(paths);
			return (res);
		}
		free(res);
		res = 0;
	}
	free_tokenized(paths);
	return (res);
}

/**
 * _setenv - sets an environment variable
 *
 * @key: key of the variable
 * @val: value of the variable
 * Return: 0 success -1 failed
 */
int _setenv(char *key, char *val)
{
	int i = 0;
	char *key_val, **temp;

	if (!key || !key[0] || is_delimeter(key, '='))
		return (-1);
	/* reserve space for env */
	key_val = malloc(_strlen(key) + _strlen(val) + 2);
	if (!key_val)
		return (-1);
	key_val[0] = '\0';
	key_val = _strcat(key_val, key);
	key_val = _strcat(key_val, "=");
	key_val = _strcat(key_val, val);
	/* check if key exist and overwrite */
	while (environ[i])
	{
		if (startsWith(environ[i], key))
		{
			free(environ[i]);
			environ[i] = key_val;
			return (0);
		}
		i++;
	}
	/* key is new add it */
	temp = malloc((i + 2) * sizeof(char *));
	if (!temp)
		return (-1);
	for (i = 0; environ[i]; i++)
		temp[i] = environ[i];
	free(environ);
	environ = temp;
	environ[i] = key_val;
	environ[i + 1] = NULL;
	return (0);
}

/**
 * _unsetenv - unsets an environment variable
 *
 * @key: key of the variable
 * Return: 0 success -1 failed
 */
int _unsetenv(char *key)
{
	int i = 0, j = 0, index = -1;
	char **temp;

	if (!key || !key[0] || is_delimeter(key, '='))
		return (-1);
	/* check if key exist and save the index */
	while (environ[i])
	{
		if (startsWith(environ[i], key))
			index = i;
		i++;
	}
	/* if key is not found */
	if (index == -1)
		return (-1);
	/* key is found remove it */
	temp = malloc(i * sizeof(char *));
	if (!temp)
		return (-1);
	for (i = 0; environ[i]; j++, i++)
	{
		if (i == index)
		{
			free(environ[i]);
			j--;
			continue;
		}
		temp[j] = environ[i];
	}
	temp[j] = NULL;
	free(environ);
	environ = temp;
	return (0);
}

/**
 * replace_vars - replace variables in args
 *
 * @args: tokenized args
 * @var: shell global info variable
 *
 */
void replace_vars(char **args, shell_t *var)
{
	int i = 0;
	char *temp;

	if (!args)
		return;
	for (; args[i]; i++)
	{
		if (args[i][0] != '$')
			continue;
		temp = _getenv(args[i] + 1);
		if (temp)
		{
			free(args[i]);
			args[i] = _strdup(temp);
			continue;
		}
		if (_strlen(args[i] + 1) == 1)
		{
			switch (args[i][1])
			{
			case '$':
				free(args[i]);
				args[i] = _itoa(getpid());
				break;
			case '?':
				free(args[i]);
				args[i] = _itoa(var->err_status);
				break;
			}
		}
	}
}
