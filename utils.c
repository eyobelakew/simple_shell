#include "shell.h"

/**
 * freearv - frees the array of pointers arv
 * @arv: array of pointers
 */
void freearv(char **arv)
{
	int i;

	for (i = 0; arv[i]; i++)
		free(arv[i]);

	free(arv);
}

/**
 * create_var - create a new environment variable string
 *
 * @name: name of the variable
 * @value: value of the variable
 *
 * Return: pointer to the new variable string
 */
char *create_var(const char *name, const char *value)
{
	size_t name_len = strlen(name), value_len = strlen(value);
	size_t var_len = name_len + 1 + value_len + 1;

	char *new_var = malloc(var_len);

	if (new_var == NULL)
		return (NULL);

	strncpy(new_var, name, name_len);
	new_var[name_len] = '=';
	strncpy(new_var + name_len + 1, value, value_len);
	new_var[var_len - 1] = '\0';

	return (new_var);
}

/**
 * rep_var - replace an existing environment variable
 *
 * @name: name of the variable
 * @new_var: pointer to the new variable string
 *
 * Return: 0 on success, -1 on failure
 */
int rep_var(const char *name, char *new_var)
{
	char **p = environ;

	while (*p)
	{
		size_t name_len = strlen(name);

		if (strncmp(*p, name, name_len) == 0 && (*p)[name_len] == '=')
		{
			*p = new_var;
			return (0);
		}

		p++;
	}

	return (-1);
}

/**
 * add_var - add a new environment variable
 *
 * @new_var: pointer to the new variable string
 *
 * Return: 0 on success, -1 on failure
 */
int add_var(char *new_var)
{
	size_t env_len = 0;
	char **p = environ;

	while (*p)
	{
		env_len++;
		p++;
	}

	char **new_environ = malloc((env_len + 2) * sizeof(char *));

	if (new_environ == NULL)
	{
		free(new_var);
		return (-1);
	}

	memcpy(new_environ, environ, env_len * sizeof(char *));
	new_environ[env_len] = new_var;
	new_environ[env_len + 1] = NULL;
	environ = new_environ;

	return (0);
}
