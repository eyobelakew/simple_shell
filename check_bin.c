#include "shell.h"

void (*checkbuild(char **arv))(char **arv)
{

    static mybuild buildins[] = {
        {"env", env},
        {"exit", __exit},
        {"setenv", _setenv},
        {"unsetenv", _unsetenv},
        {"cd", cd}, /* more built-in commands here */
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

