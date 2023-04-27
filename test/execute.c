#include "shell.h"

/**
 * execute - executes a command
 * @argv: array of arguments
 * @line_number: command number
 * @error_msg: shell name directed from main()
 */

void execute(char **argv, int line_number, char *error_msg)
{
	int d, status;

	if (!argv || !argv[0])
		return;

	d = fork();
	if (d == -1)
	{
		perror(_getenv("_"));
		return;
	}

	if (d == 0)
	{
		if (execve(argv[0], argv, environ) == -1)
		{
			size_t message_len = strlen(error_msg);
			char *line_string = _itoa(line_number);
			size_t line_len = strlen(line_string);

			write(STDERR_FILENO, error_msg, message_len);
			write(STDERR_FILENO, ": ", 2);
			write(STDERR_FILENO, line_string, line_len);
			write(STDERR_FILENO, ": ", 2);
			write(STDERR_FILENO, argv[0], strlen(argv[0]));
			write(STDERR_FILENO, ": not found\n", 12);

			free(line_string);
			exit(EXIT_FAILURE);
		}
	}

	wait(&status);
}

