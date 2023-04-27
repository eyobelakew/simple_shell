#include "shell.h"

/**
 * my_unsetenv - unsetenv library replica.
 * @name: variable name
 *
 * Return: 0 (Success)
 *         -1 (Failure)
 */
int my_unsetenv(const char *name)
{
	size_t name_len = strlen(name);
	char **p = environ, **q;

	while (*p)
	{
		if (strncmp(*p, name, name_len) == 0 && (*p)[name_len] == '=')
		{
/* Shift remaining strings down one position to overwrite the removed string */
			for (q = p; *q; ++q)
			{
				*q = *(q + 1);
			}
			return (0);
		}
		++p;
	}

	return (-1);  /* Nothing found */
}


/**
 * my_setenv - setenv library replica.
 * @name: variable name
 * @value: value to set
 * @overwrite: overwrite flag
 *
 * Return: 0 (Success)
 *         -1 (Failure)
 */

int my_setenv(const char *name, const char *value, int overwrite)
{
	char *new_var = create_var(name, value);

	if (new_var == NULL)
		return (-1);

	if (rep_var(name, new_var) == 0)
	{
		if (!overwrite)
		{
			free(new_var);
			return (0);
		}
	}
	else
	{
		if (add_var(new_var) == -1)
			return (-1);
	}

	return (0);
}
