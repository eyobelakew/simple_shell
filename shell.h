#ifndef SHELL_H
#define SHELL_H
/********************************************** SYSTEM LIBRARIES *****************************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <errno.h>
#include <stddef.h>
#include <sys/stat.h>
#include <signal.h>


/****************************************************** STRUCTURES ****************************************************************/

/**
 * struct list_path - Linked list containing PATH directories
 * @dir: directory in path
 * @p: pointer to next node
 */
typedef struct list_path
{
	char *dir;
	struct list_path *p;
} list_path;


/**
 * struct mybuild - pointer to function with corresponding buildin command
 * @name: buildin command
 * @func: execute the buildin command
 */
typedef struct mybuild
{
	char *name;
	void (*func)(char **);
} mybuild;

/************************************************* I/O AND UTIL FUNCTIONS*********************************************************/
int _putchar(char c);

char **splitstring(char *str, const char *delim);
void freearv(char **arv);
void free_list(list_path *head);
/************************************************** MAIN FUNCTIONS ****************************************************************/
extern char **environ;

void execute(char **argv);
char *_getenv(const char *name);
list_path *linkpath(char *path);
char *_which(char *filename, list_path *head);

void(*checkbuild(char **arv))(char **arv);
int _atoi(char *s);
void __exit(char **arv);
void env(char **arv);
void _setenv(char **arv);
void _unsetenv(char **arv);
int my_unsetenv(const char *name);
void cd(char **arv);
int my_setenv(const char *name, const char *value, int overwrite);
/************************************************************END *********************************************************************/
#endif
