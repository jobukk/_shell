#include "shell.h"


/**
**_strncpy - copy string
*@dest: the destination
*@src: source of the string
*@n: amount of characters  copied
*Return:concat string
*/
char *_strncpy(char *dest, char *src, int n)
{
int i, j;
char *s = dest;

for (i = 0; src[i] != '\0' && i < n - 1; i++)
{
dest[i] = src[i];
}

for (j = (s[n - 1] == '\0') ? 0 : i; j < n; j++)
{
dest[j] = '\0';
}

return (s);
}

/**
**_strncat - concat two string into one
*@dest: first str
*@src: second str
*@n: amount of bytes to use
*Return: concat str
*/
char *_strncat(char *dest, char *src, int n)
{
char *s = dest;

int i;
int j;
i = 0;
while (dest[i] != '\0')
i++;

for (j = 0; src[j] != '\0' && j < n; i++, j++)
{
dest[i] = src[j];
}

if (j < n)
dest[i] = '\0';

return (s);
}

/**
**_strchr - locates a char in a str
*@s: str to parse
*@c: char to search for
*Return: (s) ptr to memory
*/
char *_strchr(char *s, char c)
{
for (; *s != '\0'; s++)
{
if (*s == c)
return (s);
}

return (NULL);
}
