#include "shell.h"

/**
 * _strlen - length of a string
 * @s: length to check
 *
 * Return: integer length
 */
int _strlen(char *s)
{
    int k = 0;

    if (!s)
        return 0;

    for (; *s; s++)
        k++;

    return k;
}

/**
 * _strcmp - lexicographic
 * @s1: string
 * @s2: string
 *
 * Return: s1 < s2
 */
int _strcmp(char *s1, char *s2)
{
    for (; *s1 && *s2; s1++, s2++)
    {
        if (*s1 != *s2)
            return (*s1 - *s2);
    }

    return (*s1 == *s2 ? 0 : (*s1 < *s2 ? -1 : 1));
}

/**
 * starts_with -  haystack
 * @haystack: search
 * @needle: substring to find
 *
 * Return: address
 */
char *starts_with(const char *haystack, const char *needle)
{
    for (; *needle; needle++, haystack++)
    {
        if (*needle != *haystack)
            return NULL;
    }

    return (char *)haystack;
}

/**
 * _strcat - concatenates
 * @dest: destination
 * @src: source
 *
 * Return: ptr to destination
 */
char *_strcat(char *dest, char *src)
{
    char *ret = dest;

    for (; *dest; dest++)
        ;

    for (; *src; *dest++ = *src++)
        ;

    *dest = *src;

    return ret;
}
