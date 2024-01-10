#include "shell.h"

/**
 * _erratoi - converts a string to an integer
 * @s: the string to be converted
 * Return: 0 if no numbers in string, converted number otherwise
 *        -1 on error
 */
int _erratoi(char *s)
{
    int i = 0;
    unsigned long int result = 0;

    if (*s == '+')
        s++;  /* TODO: why does this make main return 255? */

    
    while (s[i] != '\0')
    {
        if (s[i] >= '0' && s[i] <= '9')
        {
            result *= 10;
            result += (s[i] - '0');
            if (result > INT_MAX)
                return -1;
        }
        else
        {
            return -1;
        }
        i++;
    }

    return result;
}

/**
 * print_error - prints an error message
 * @info: the parameter & return info struct
 * @estr: string containing specified error type
 * Return: 0 if no numbers in string, converted number otherwise
 *        -1 on error
 */
void print_error(info_t *info, char *estr)
{
    _eputs(info->fname);
    _eputs(": ");
    print_d(info->line_count, STDERR_FILENO);
    _eputs(": ");
    _eputs(info->argv[0]);
    _eputs(": ");
    _eputs(estr);
}

/**
 * print_d - function prints a decimal (integer) number (base 10)
 * @input: the input
 * @fd: the filedescriptor to write to
 *
 * Return: number of characters printed
 */
int print_d(int input, int fd)
{
    int (*__putchar)(char) = (fd == STDERR_FILENO) ? _eputchar : _putchar;
    int count = 0;
    unsigned int _abs_ = (input < 0) ? -input : input;
    unsigned int current = _abs_;

    if (input < 0)
    {
        __putchar('-');
        count++;
    }

    while (current > 1)
    {
        if (_abs_ / 1000000000)
        {
            __putchar('0' + current / 1000000000);
            count++;
        }
        current %= 1000000000;
    }

    __putchar('0' + current);
    count++;

    return count;
}

/**
 * convert_number - converter function, a clone of itoa
 * @num: number
 * @base: base
 * @flags: argument flags
 *
 * Return: string
 */
char *convert_number(long int num, int base, int flags)
{
    unsigned long n;
    char sign;
    static char buffer[50];
    char *array = (flags & CONVERT_LOWERCASE) ? "0123456789abcdef" : "0123456789ABCDEF";
    char *ptr = &buffer[49];
    *ptr = '\0';

     n = (flags & CONVERT_UNSIGNED) ? num : -num;
    sign = (num < 0 && !(flags & CONVERT_UNSIGNED)) ? '-' : 0;

    do
    {
        *--ptr = array[n % base];
        n /= base;
    } while (n != 0);

    if (sign)
        *--ptr = sign;

    return ptr;
}

/**
 * remove_comments - function replaces first instance of '#' with '\0'
 * @buf: address of the string to modify
 *
 * Return: Always 0;
 */
void remove_comments(char *buf)
{
    int i = 0;
    while (buf[i] != '\0')
    {
        if (buf[i] == '#' && (!i || buf[i - 1] == ' '))
        {
            buf[i] = '\0';
            break;
        }
        i++;
    }
}
