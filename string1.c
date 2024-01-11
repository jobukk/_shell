#include "shell.h"

/**
 * _strcpy - copy
 * @dest:  destination
 * @src: source
 *
 * Return: destination
 */
char *_strcpy(char *dest, char *src)
{
    int j;

    if (dest == src || src == NULL)
        return dest;

    for (j = 0; src[j]; j++)
    {
        dest[j] = src[j];
    }

    dest[j] = '\0';
    return dest;
}

/**
 * _strdup - duplicate
 * @str: string duplicate
 *
 * Return: ptr to duplicate str
 */
char *_strdup(const char *str)
{
    int length = 0;
    char *ret;

    if (str == NULL)
        return NULL;

    for (length = 0; str[length] != '\0'; length++)
        ;

    ret = malloc(sizeof(char) * (length + 1));
    if (!ret)
        return NULL;

    for (length++; length--;)
        ret[length] = *--str;

    return ret;
}

/**
 * _puts -  input string
 * @str: string to be printed
 *
 * Return: None
 */
void _puts(char *str)
{
    if (!str)
        return;

    for (; *str != '\0'; str++)
        _putchar(*str);
}

/**
 * _putchar - char c stdout
 * @c: char to the print
 *
 * Return:  1.
 */
int _putchar(char c)
{
    static int i;
    static char buf[WRITE_BUF_SIZE];

    return (c == BUF_FLUSH || i >= WRITE_BUF_SIZE) ? write(1, buf, i), i = 0, 1 : (c != BUF_FLUSH) ? buf[i++] = c, 1 : 1;
}
