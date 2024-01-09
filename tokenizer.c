#include "shell.h"

/**
* **strtow - split a string into words.
* @str: input str
* @d:  delimeter str
* Return: a ptr to an array of str, else NULL
*/
char **strtow(char *str, char *d)
{
int i = 0, j = 0, k, numwords = 0;
char **s;

if (!str || str[0] == '\0')
return (NULL);

d = (d == NULL) ? " " : d;

numwords = countWords(str, d);
if (numwords == 0)
return (NULL);

s = malloc((1 + numwords) *sizeof(char *));
if (!s)
return (NULL);

i = 0;
j = 0;
while (j < numwords)
{
i = skipDelimiters(str, d, i);

k = getWordLength(str, d, i);

s[j] = extractWord(str, i, k);
if (!s[j])
{
freeMemory(s, j);
return (NULL);
}

j++;
}

s[j] = NULL;
return (s);
}


