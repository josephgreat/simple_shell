#include "shell.h"

void print_arr(char **arr)
{
	int i = 0;

	while(arr[i])
		printf("%s\n", arr[i++]);

	printf("======={=======\n");
}

char **logic_token(char *str);

int main(int c, char **a)
{
	char *temp = "abc && ghi || xyz fgh";
	int i = 1;
	
	(void)c, (void)a;

	shell_t var;
	var.err_status = -1;
	printf("line: %s\n\n", temp);


	char **args = logic_token(temp);
	while (args[1])
	{
		printf("Round %d\n", i++);
		printf("args[0]: %s\n", args[0]);
		printf("args[1]: %s\n", args[1]);
		printf("args[2]: %s\n", args[2]);
		printf("======={=======\n");
		free(args[0]);
		free(args[1]);
		free(args);
		args = logic_token(args[2]);
	}
	free(args[0]);
	free(args);
	/* print_arr(environ);
	printf("set = %d\n", _setenv("Me", "Me_value"));
	print_arr(environ);
	_unsetenv("Me");
	print_arr(environ); */
	char **x = tokenize("echo $PATH $? $$", " ");
	replace_vars(x, &var);
	print_arr(x);
	free_tokenized(x);
	return (0);
}
