#include "shell.h"

/**
 * _strncpy - copy a string
 * @dest: dest
 * @src:  string
 * @n: characters to be copy
 * Return: concatenated string
 */

char *_strncpy(char *dest, char *src, int n)
{
int j;
int k;
char *s = dest;

for (k = 0; (k < n - 1) && (dest[k] = src[k]) != '\0'; k++)
;

for (j = k; j < n; dest[j++] = '\0')
;

return (s);
}

/**
 * _strncat - concatenates two strings
 * @dest: the first string
 * @src: the second string
 * @n: the amount of bytes to be maximally used
 * Return: the concatenated string
 */
char *_strncat(char *dest, char *src, int n)
{
int k;
int i;
char *s = dest;

for (i = 0; dest[i] != '\0'; i++);
for (k = 0; (k < n) && (dest[i + k] = src[k]) != '\0'; k++);
dest[i + k] = '\0';
return (s);
}


/**
 * _strchr - check for a character
 * @s:  string
 * @c: character
 * Return: (s) a ptr to a memory
 */
char *_strchr(char *s, char c)
{
do {
if (*s == c)
return (s);
} while (*s++ != '\0');

return (NULL);
}
