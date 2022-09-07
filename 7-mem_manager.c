#include "shell.h"

/**
 * free_tokenized - frees an array of arrays
 *
 * @tokens: pointer to array
 */
void free_tokenized(char **tokens)
{
	int i = 0;

	if (!tokens)
		return;
	while (tokens[i])
		free(tokens[i++]);
	free(tokens);
	tokens = NULL;
}


/**
 * _realloc - reallocate memory to a buffer
 * @ptr: pointer to buffer
 * @old_size: old size of buffer
 * @new_size: new size of buffer
 * Return: pointer to the new buffer
 */
void *_realloc(void *ptr, unsigned int old_size, unsigned int new_size)
{
	unsigned int i, min;
	void *new_ptr;

	if (ptr == NULL)
		return (malloc(new_size));
	else if (!new_size)
	{
		free(ptr);
		return (NULL);
	}
	if (old_size == new_size)
		return (ptr);
	min = (old_size > new_size) ?
		new_size :
		old_size;
	new_ptr = malloc(new_size);
	if (new_ptr == NULL)
		return (NULL);
	for (i = 0; i < min; i++)
		((char *)new_ptr)[i] = ((char *)ptr)[i];
	free(ptr);
	return (new_ptr);
}

/**
 * clear_memory - frees global memories
 *
 * @var: global shell variable
 */
void clear_memory(shell_t *var)
{
	free_tokenized(environ);
	free_tokenized(var->aliases);
}
