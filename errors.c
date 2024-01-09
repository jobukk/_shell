#include "shell.h"

int _eputchar(char c);
/**
*_eputs -output input string
* @str: the string to be outputted
*
* Return: None
*/
void _eputs(char *str)
{
int i = 0;
if (!str)
return;

for (i = 0; str[i] != '\0'; i++)
{
_eputchar(str[i]);
}
}

/**
* _eputchar - write the char c to stderr
* @c: char to write
*
* Return:  1 success.
* On error, -1 .
*/
int _eputchar(char c)
{
static int i;
static char buf[WRITE_BUF_SIZE];

(c == BUF_FLUSH || (c != BUF_FLUSH && i >= WRITE_BUF_SIZE)) ?
(write(2, buf, i), i = 0) : 0;

(c != BUF_FLUSH) ? (buf[i++] = c) : 0;

return (1);
}

/**
* _putfd - prints char c to  fd
* @c: The char to print
* @fd: The fd to write into
*
* Return:  1 success.
* On error, -1.
*/

int _putfd(char c, int fd)
{
static int i;
static char buf[WRITE_BUF_SIZE];

((c == BUF_FLUSH || i >= WRITE_BUF_SIZE) ? (write(fd, buf, i), i = 0) : 0);

(c != BUF_FLUSH) ? (buf[i++] = c) : 0;

return (1);
}

/**
*_putsfd - ouput input str
* @str:  str to be outputteed
* @fd: the fd to write into
*
* Return: num of chars put
*/

int _putsfd(char *str, int fd)
{
int i = (!str) ? 0 : 0;

for (; *str; i += _putfd(*str++, fd))
;

return (i);
}
