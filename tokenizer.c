#include "shell.h"

/**
 * **strtow - splits a string into words. Repeat delimiters are ignored
 * @str: the input string
 * @d: the delimeter string
 * Return: a pointer to an array of strings, or NULL on failure
 */
char **strtow(char *str, char *d)
{
	int i = 0, j = 0, k, m, numwords = 0;
	char **s;

	if (!str || str[0] == '\0')
		return NULL;

	if (!d)
		d = " ";

	while (str[i] != '\0')
	{
		if (!is_delim(str[i], d) && (is_delim(str[i + 1], d) || !str[i + 1]))
			numwords++;
		i++;
	}

	if (numwords == 0)
		return NULL;

	s = malloc((1 + numwords) * sizeof(char *));
	if (!s)
		return NULL;

	i = 0, j = 0;
	while (j < numwords)
	{
		while (is_delim(str[i], d))
			i++;

		k = 0;
		while (!is_delim(str[i + k], d) && str[i + k])
			k++;

		s[j] = malloc((k + 1) * sizeof(char));
		if (!s[j])
		{
			while (k-- > 0)
				free(s[k]);
			free(s);
			return NULL;
		}

		m = 0;
		while (m < k)
			s[j][m++] = str[i++];

		s[j][m] = '\0';
		j++;
	}

	s[j] = NULL;
	return s;
}

/**
 * **strtow2 - splits a string into words
 * @str: the input string
 * @d: the delimeter
 * Return: a pointer to an array of strings, or NULL on failure
 */
char **strtow2(char *str, char d)
{
	int i = 0, j = 0, k, m, numwords = 0;
	char **s;

	if (!str || str[0] == '\0')
		return NULL;

	while (str[i] != '\0')
	{
		if ((str[i] != d && str[i + 1] == d) ||
		    (str[i] != d && !str[i + 1]) || str[i + 1] == d)
			numwords++;

		i++;
	}

	if (numwords == 0)
		return NULL;

	s = malloc((1 + numwords) * sizeof(char *));
	if (!s)
		return NULL;

	i = 0, j = 0;
	while (j < numwords)
	{
		while (str[i] == d && str[i] != d)
			i++;

		k = 0;
		while (str[i + k] != d && str[i + k] && str[i + k] != d)
			k++;

		s[j] = malloc((k + 1) * sizeof(char));
		if (!s[j])
		{
			while (k-- > 0)
				free(s[k]);
			free(s);
			return NULL;
		}

		m = 0;
		while (m < k)
			s[j][m++] = str[i++];

		s[j][m] = '\0';
		j++;
	}

	s[j] = NULL;
	return s;
}
