#include "shell.h"

/**
 * _strcat - concatenates src to destination
 * @src: pointer to the source string
 * @dst: pointer to the destination string
 * Return: pointer to destination
 */

char *_strcat(char *dst, char *src)
{
	int x = 0, y = 0;

	if (!dst || !src)
		return (dst);
	/* Get the length of destination */
	while (dst[y])
		y++;
	/* concatenate */
	while (src[x])
	{
		dst[y++] = src[x];
		x++;
	}
	dst[y] = '\0';
	return (dst);
}

/**
 *_strcmp - compare two strings
 *@first: first string to be compared
 *@second: second string to be compared
 *
 * Return: difference of the two strings
 */

int _strcmp(char *first, char *second)
{
	int i = 0;

	while (first[i] != '\0')
	{
		if (first[i] != second[i])
			break;
		i++;
	}
	return (first[i] - second[i]);
}


/**
 * _strlen - gets the length of a string
 * @s: string pointer
 * Return: string length
 */
int _strlen(char *s)
{
	int i = 0;

	if (!s)
		return (-1);
	while (s[i])
		i++;
	return (i);
}


/**
 * _strdup - duplicates a string
 *
 * @s: pointer to string
 * Return: pointer to duplicate
 */
char *_strdup(char *s)
{
	int i;
	char *res;

	if (!s)
		return (0);
	res = malloc(_strlen(s) + 1);
	i = 0;
	while (s[i])
	{
		res[i] = s[i];
		i++;
	}
	res[i] = '\0';
	return (res);
}

/**
 * _strndup - duplicates a string
 *
 * @s: pointer to string
 * @n: number of characters to duplicate
 * Return: pointer to duplicate
 */
char *_strndup(char *s, int n)
{
	int i, len;
	char *res;

	if (!s || n < 0)
		return (0);
	len = _strlen(s);
	if (n > len)
		n = len;
	res = malloc(n + 1);
	i = 0;
	while (s[i] && i < n)
	{
		res[i] = s[i];
		i++;
	}
	res[i] = '\0';
	return (res);
}
