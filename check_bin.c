#include "shell.h"

/**
 * checkbuild - searches for a built-in command
 * @arv: array of arguments passed to the shell
 * Return: function pointer to built-in command if found, NULL otherwise
 */
void (*checkbuild(char **arv))(char **arv)
{
    static mybuild buildins[] = {
        {"env", env},
        {"exit", __exit},
        {"setenv", _setenv},
        {"unsetenv", _unsetenv},
        {"cd", cd},
        {NULL, NULL}
    };
    int i;

    for (i = 0; buildins[i].name != NULL; i++)
    {
        if (strcmp(arv[0], buildins[i].name) == 0)
        {
            return buildins[i].func;
        }
    }
    return NULL;
}

