

#include "shell.h"

/**
* _strlen - check length of a string
* @s: the string
*
* Return: length of string as an interger
*/

int _strlen(char *s)
{
char *ptr = s;

if (!s)
return (0);

for (; *ptr; ptr++)
;

return (ptr - s);
}


/**
* _strcmp -  lexicogarphic comparison of two strings.
* @s1: first string
* @s2:  second string
*
* Return: negative if s1 < s2, positive if s1 > s2, zero if s1 == s2
*/

int _strcmp(char *s1, char *s2)
{
for (; *s1 && *s2 && *s1 == *s2; s1++, s2++)
;

return ((*s1 == *s2) ? 0 : (*s1 < *s2 ? -1 : 1));
}

/**
* starts_with - checks if needle starts with haystack
* @haystack: string to search
* @needle:  substring to find
*
* Return: address of next char or NULL
*/

char *starts_with(const char *haystack, const char *needle)
{
for (; *needle; needle++, haystack++)
if (*needle != *haystack)
{
return (NULL);
}


return ((char *)haystack);
}


/**
* _strcat - concat two strings
* @dest:  dest buffer
* @src:  src buffer
*
* Return: pointer to dest buffer
*/

char *_strcat(char *dest, char *src)
{
char *ret = dest;

for (; *dest; dest++)
;

for (; *src; dest++, src++)
*dest = *src;

*dest = *src;

return (ret);
}
