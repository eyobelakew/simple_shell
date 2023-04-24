#include "shell.h"

/**
 * my_unsetenv - unsetenv library replica.
 * @name: variable name
 *
 * Return: 0 (Success)
 *         -1 (Failure)
 */
int my_unsetenv(const char *name)
{	/* Check if the variable exists */
	char *existing_value = getenv(name);
	char **new_environ = (char **)malloc((envc + 1) * sizeof(char *));
	int envc = 0;

	if (existing_value == NULL)
		return (0);

	/* Allocate memory for a new environment array without the variable */
	while (environ[envc])
	{
		envc++;
	}
	if (new_environ == NULL)
	{
		return (-1);
	} /* Return failure if malloc fails */

	/* Copy the environment variables into the new array */
	int i = 0;

	while (environ[i])
	{
		if (strncmp(environ[i], name, strlen(name)) != 0 ||
		    environ[i][strlen(name)] != '=')
		{
			new_environ[i] = environ[i];
		}
		else /* Skip the variable to be unset */
		{
			i++;
			continue;
		}
		i++;
	}
	new_environ[i] = NULL; /* Null terminate the array */

	environ = new_environ; /* Replace environ with the modified one */

	return (0);
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
