#include "shell.h"


/**
 * _printf - prints a string
 *
 * @str: pointer to string
 * @fd: file descriptor to print to
 * Return: number of chars printed
 */
int _printf(char *str, int fd)
{
	if (!str)
		return (-1);
	return (write(fd, str, _strlen(str)));
}


/**
 * remove_comment - removes/ignores everything after a '#' char
 * @input: input to be used
 *
 * Return: void
 */
void remove_comment(char *input)
{
	int i = 0;

	if (input[i] == '#')
		input[i] = '\0';
	while (input[i] != '\0')
	{
		if (input[i] == '#' && input[i - 1] == ' ')
			break;
		i++;
	}
	input[i] = '\0';
}


/**
 * _putchar - print a character
 * @c: character to print
 * Return: 0
 */
int _putchar(char c)
{
	return (write(1, &c, 1));
}



/**
 * _atoi - changes a string to an integer
 * @s: the string to be changed
 *
 * Return: the converted int
 */
int _atoi(char *s)
{
	unsigned int n = 0;

	do {
		if (*s == '-')
			return (-1);
		else if ((*s < '0' || *s > '9') && *s != '\0')
			return (-1);
		else if (*s >= '0'  && *s <= '9')
			n = (n * 10) + (*s - '0');
		else if (n > 0)
			break;
	} while (*s++);
	return (n);
}

/**
 * _itoa - convert an integer to a string
 * @num: num to be converted
 *
 * Return: converted string
 */
char *_itoa(int num)
{
	char *res;
	int tmp = num, len = 0;

	if (tmp < 0)
	{
		len++;
		tmp *= -1;
	}

	do {
		tmp /= 10;
		len++;
	} while (tmp);
	res = malloc((len + 1) * sizeof(char));
	if (!res)
		return (NULL);
	*(res + len) = '\0';

	if (num < 0)
	{
		res[0] = '-';
		num *= -1;
	}
	len--;
	do {
		*(res + len) = (num % 10) + '0';
		num /= 10;
		len--;
	} while (num);

	return (res);
}
