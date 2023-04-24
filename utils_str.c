#include "shell.h"

/**
 * _atoi - converts a string to an integer
 * @s: the string to convert
 *
 * Return: the converted integer
 */
int _atoi(char *s)
{
	int res = 0, sign = 1, i = 0;

	if (s[0] == '-')
	{
		sign = -1;
		i++;
	}
	for (; s[i]; ++i)
	{
		if (s[i] >= '0' && s[i] <= '9')
		{
			res = res * 10 + s[i] - '0';
		}
		else
		{
			break;
		}
	}
	return (sign * res);
}


/**
 * splitstring - splits a string into an array of strings
 * @str: the string to split
 * @delim: the delimiter to use for splitting
 *
 * Return: a dynamically-allocated array of strings
 */
char **splitstring(char *str, const char *delim)
{
	char **words = NULL;
	char *token = NULL;
	int i = 0;

	/* allocate memory for the words array */
	words = malloc(sizeof(char *));
	if (words == NULL)
		return (NULL);

	/* split the string into words using the delimiter */
	token = strtok(str, delim);
	while (token != NULL)
	{
		/* resize the words array */
		words = realloc(words, (i + 2) * sizeof(char *));
		if (words == NULL)
			return (NULL);

		/* allocate memory for the current word and copy it */
		words[i] = malloc(strlen(token) + 1);
		if (words[i] == NULL)
			return (NULL);
		strcpy(words[i], token);

		/* move to the next token */
		token = strtok(NULL, delim);
		i++;
	}

	/* add a NULL terminator to the end of the words array */
	words[i] = NULL;

	return (words);
}
