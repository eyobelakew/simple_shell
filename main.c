#include "shell.h"

/**
* check_atty - check is it's terminal interactive mode and print prompt
*
* Return: Nothing
*/

void check_atty()
 {
 	if (isatty(STDIN_FILENO))
 	printf("cisfun$ ");
}

/**
* _EOF - handle end-of-file condition
* @len: num of characters read from the input stream
* @buff: characters read from input stream
*
* Return: (0) Success.
*/

void _EOF(int len, char *buff)
{
	(void)buff; /* avoid unused variable warning */
	if (len == -1) /*if input stream reached EOF */
	{
		if (isatty(STDIN_FILENO)) /* If input stream is terminal */
		{
			puts("\n");
			free(buff);
		}
		exit(0);
	}
}

/**
* sig_handler - handle Ctrl + C
* @sig_num - signal number recieved.
*
* Return: Nothing
*/


void sig_handler(int sig_num)
{
    if (sig_num == SIGINT) /* SIGINT -signal for intrrupt (C-c). */
    {
        printf("\n");
        printf("cisfun$ ");
        fflush(stdout);
    }
}


int main(void)
{
	ssize_t len = 0;
	char *buff = NULL, *value, *pathname, **arv;
	size_t size = 0;
	list_path *head = '\0';
	void (*f)(char **);

	signal(SIGINT, sig_handler);
	while (len != EOF)
	{
		check_atty();
		len = getline(&buff, &size, stdin);
		_EOF(len, buff);
		arv = splitstring(buff, " \n");
		if (!arv || !arv[0])
			execute(arv);
		else
		{
			value = _getenv("PATH");
			head = linkpath(value);
			pathname = _which(arv[0], head);
			f = checkbuild(arv);
			if (f)
			{
				free(buff);
				f(arv);
			}
			else if (!pathname)
				execute(arv);
			else if (pathname)
			{
				free(arv[0]);
				arv[0] = pathname;
				execute(arv);
			}
		}
	}
	free_list(head);
	freearv(arv);
	free(buff);
	return (0);
}
