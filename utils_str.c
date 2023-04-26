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
 * _itoa - convert a intiger to string
 * @num: input number
 *
 * Return: converted string
 */

char *_itoa(int num)
{
	int temp = num, digits = 0;
	char *str;

	while (temp != 0)
	{
		digits++;
		temp /= 10;
	}

	str = malloc(sizeof(char) * (digits + 1));
	str[digits] = '\0';

	while (digits > 0)
	{
		str[--digits] = (num % 10) + '0';
		num /= 10;
	}

	return (str);
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
	char **words = NULL, **old_words = NULL;
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
		old_words = words;
		/* resize the words array */
		words = realloc(words, (i + 2) * sizeof(char *));
		if (words == NULL)
		{
			return (NULL);
		}

		/* allocate memory for the current word and copy it */
		words[i] = malloc(strlen(token) + 1);
		if (words[i] == NULL)
		{
			freearv(words);
			return (NULL);
		}
		_strcpy(words[i], token);

		/* move to the next token */
		token = strtok(NULL, delim);
		i++;
	}

	/* add a NULL terminator to the end of the words array */
	words[i] = NULL;
	token = NULL;

	return (words);
}

/**
 * _strcpy - copy a string to a buffer
 * @src: source string
 * @dest: destination buffer
 *
 * Return: dest
 */

char *_strcpy(char *dest, const char *src)
{
	char *c_dest = dest;

	while (*src)
	{
		*c_dest++ = *src++;
	}

	c_dest = '\0';

	return (dest);
}
