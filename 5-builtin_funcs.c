#include "shell.h"

/**
 * env - prints the current_environnement
 * @tokenized_command: command entered
 * @p: shell global variable
 *
 */

void env(char **tokenized_command __attribute__((unused)),
		shell_t *p)
{
	int i;

	for (i = 0; environ[i]; i++)
	{
		_printf(environ[i], STDOUT_FILENO);
		_printf("\n", STDOUT_FILENO);
	}
	p->err_status = 0;
}

/**
 * quit - exits the shell
 * @tokenized_command: command entered
 * @p: shell global variable
 *
 */

void quit(char **tokenized_command, shell_t *p)
{
	int num_token = 0, arg;

	for (; tokenized_command[num_token] != NULL; num_token++)
		;
	if (num_token == 1)
	{
		/* free_tokenized(tokenized_command); */
		clear_memory(p);
		p->exit = p->err_status;
	}
	else if (num_token == 2)
	{
		arg = _atoi(tokenized_command[1]);
		if (arg < 0)
		{
			print_error(tokenized_command, p);
			p->err_status = 2;
		}
		else
		{
			/* free_tokenized(tokenized_command); */
			clear_memory(p);
			p->exit = arg;
		}
	}
	else
		_printf("$: exit doesn't take more than one argument\n", STDERR_FILENO);
}

#define SETPWD(V) (V = _strdup(_getenv("OLDPWD")))
/**
 * ch_dir - handles change directory command (cd)
 * @command: command enterd, not used
 * @var: shell global variable
 */

void ch_dir(char **command, shell_t *var)
{
	char *home;

	home = _getenv("HOME");
	if (command[1] == NULL)
	{
		SETPWD(var->old_pwd);
		if (chdir(home) < 0)
		{
			print_error(command, var);
			var->err_status = 2;
			return;
		}
	}
	else if (_strcmp(command[1],  "-") == 0)
	{
		if (var->old_pwd == NULL)
		{
			SETPWD(var->old_pwd);
			if (chdir(home) < 0)
				exit(EXIT_FAILURE);
		}
		else
		{
			SETPWD(var->old_pwd);
			if (chdir(var->old_pwd) < 0)
				exit(EXIT_FAILURE);
		}
		_printf(var->old_pwd, STDOUT_FILENO);
		_printf("\n", STDOUT_FILENO);
	}
	else
	{
		SETPWD(var->old_pwd);
		if (chdir(command[1]) < 0)
		{
			print_error(command, var), var->err_status = 2;
			return;
		}
	}
	var->err_status = 0;
}

#undef GETCWD
/**
 * display_help - display help necessary help and docs for the shell
 * @command: command passed
 * @p: shell global variable
 */

void display_help(char **command __attribute__((unused)),
		shell_t *p __attribute__((unused)))
{
	static char *texts[] = {
		"\n\t***Welcome to Our Simple Shell***\n",
		"Copyright: @Sanctus-Peter @mamt4real\n",
		"\nList of Supported Commands:\n",
		"\tcd\n",
		"\trmdir\n",
		"\tmkdir\n",
		"\tsetenv\n",
		"\tunsetenv\n",
		"\thelp\n",
		"\tclear\n",
		"\texit\n",
		"\nAll Other Shell Built in Commands are supported\n",
		"\nHave Fun!!\n",
		NULL
		};
	int i = 0;

	while (texts[i])
	{
		_printf(texts[i], STDIN_FILENO);
		i++;
	}
}
