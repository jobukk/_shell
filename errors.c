#include "shell.h"

/**
 * _eputs -  input string
 * @str: string
 *
 * Return: None
 */
void _eputs(char *str)
{
int a = 0;
if (str)
{
for (a = 0; str[a] != '\0'; a++)
_eputchar(str[a]);
}
}

/**
 * _eputchar -character c to stderr
 * @c: char
 *
 * Return: On success 1 else -1
 */
int _eputchar(char c)
{
static int j;
static char buf[WRITE_BUF_SIZE];

if (c == BUF_FLUSH || j >= WRITE_BUF_SIZE)
{
write(2, buf, j);
j = 0;
}

if (c != BUF_FLUSH)
buf[j++] = c;

return (1);
}

/**
 * _putfd - write the character c
 * @c: char
 * @fd: file descriptor
 *
 * Return: On success 1
 */
int _putfd(char c, int fd)
{
static int k;
static char buf[WRITE_BUF_SIZE];

if (c == BUF_FLUSH || k >= WRITE_BUF_SIZE)
{
if (k > 0)
write(fd, buf, k);
k = 0;
}

if (c != BUF_FLUSH)
buf[k++] = c;

return (1);
}

/**
 * _putsfd - prints string
 * @str: string
 * @fd: file descriptor
 *
 * Return: the number of chars put
 */
int _putsfd(char *str, int fd)
{
int count = 0;

if (str)
{
for (; *str; str++)
count += _putfd(*str, fd);
}

return (count);
}
