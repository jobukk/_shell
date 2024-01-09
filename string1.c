#include "shell.h"


/**
* _strcpy - copy a string
* @dest:  destination
* @src:  source
*
* Return: pointer to destination
*/

char *_strcpy(char *dest, char *src)
{
int i = 0;
if (dest == src || src == 0)
return (dest);

for (i = 0; src[i]; i++)
{
dest[i] = src[i];
}

dest[i] = '\0';

return (dest);
}

/**
* _strdup - duplicate string
* @str:  string to duplicate
*
* Return: ptr to the duplicated string
*/

char *_strdup(const char *str)
{
int length = 0;
char *ret;

if (str == NULL)
return (NULL);

while (*str != '\0')
{
length++;
str++;
}

ret = malloc(sizeof(char) * (length + 1));
if (!ret)
return (NULL);

while (length--)
{
ret[length] = *--str;
}

return (ret);
}

/**
*_puts - prints an input str
*@str: the str to be printed
*
* Return: None
*/

void _puts(char *str)
{
int i = 0;
if (!str)
return;

for (i = 0; str[i] != '\0'; i++)
{
_putchar(str[i]);
}
}





/**
* _putchar - writes the character d to stdout
* @c: The character to print
*
* Return: success 1.
* On error, -1 .
*/
int _putchar(char d)
{
static int i;
static char buf[WRITE_BUF_SIZE];

if (d != BUF_FLUSH && i < WRITE_BUF_SIZE)
buf[i++] = d;

if (d == BUF_FLUSH || i >= WRITE_BUF_SIZE)
{
write(1, buf, i);
i = 0;
}

return (1);
}


