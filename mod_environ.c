#include "shell.h"
 
/**
* my_unsetenv - unsetenv library replica.
* @name: variable name
*
* Return: 0 (Success)
*	: -1 (Failure)
*/

int my_unsetenv(const char *name) 
{
    /* Check if the variable exists */
    char *existing_value = getenv(name);
    if (existing_value == NULL)
    {
        return 0;
    }

    /* Allocate memory for a new environment array without the variable */
    int envc = 0;
    while (environ[envc])
    {
        envc++;
    }
    char **new_environ = (char **)malloc((envc + 1) * sizeof(char *));
    if (new_environ == NULL)
    {
        return -1;
    } /* Return failure if malloc fails */

    /* Copy the environment variables into the new array */
    int i = 0;
    while (environ[i])
    {
        if (strncmp(environ[i], name, strlen(name)) != 0 || environ[i][strlen(name)] != '=') 
        {
            new_environ[i] = environ[i];
        } 
        else /* Skip the variable to be unset */
        {
            i++;
        }
        i++;
    }
    new_environ[i] = NULL;  /* Null terminate the array */

    environ = new_environ; /* Replace environ with the modfied one */

    return 0;
}

int my_setenv(const char *name, const char *value, int overwrite)
{
    // Calculate the length of the new environment variable string
    size_t name_len = strlen(name);
    size_t value_len = strlen(value);
    size_t var_len = name_len + 1 + value_len + 1;

    // Allocate memory for the new environment variable string
    char *new_var = (char *)malloc(var_len);
    if (new_var == NULL)
    {
        return -1;
    }

    // Construct the new environment variable string
    strncpy(new_var, name, name_len);
    new_var[name_len] = '=';
    strncpy(new_var + name_len + 1, value, value_len);
    new_var[var_len - 1] = '\0';

    // Search for the existing variable
    char **p = environ;
    while (*p != NULL)
    {
        if (strncmp(*p, name, name_len) == 0 && (*p)[name_len] == '=')
        {
            // Variable found
            if (overwrite)
            {
                // If overwrite is set, replace the existing variable
                *p = new_var;
                return 0;
            }
            else
            {
                // If overwrite is not set, keep the existing variable
                free(new_var);
                return 0;
            }
        }
        p++;
    }

    // Variable not found, add it to the environment
    size_t env_len = p - environ;
    char **new_environ = (char **)malloc((env_len + 2) * sizeof(char *));
    if (new_environ == NULL)
    {
        free(new_var);
        return -1;
    }

    // Copy the existing environment to the new environment
    memcpy(new_environ, environ, env_len * sizeof(char *));
    new_environ[env_len] = new_var;
    new_environ[env_len + 1] = NULL;

    // Replace the old environment with the new environment
    environ = new_environ;

    return 0;
}
