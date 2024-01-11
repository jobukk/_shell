#include "shell.h"

/**
 **_memset - fills memory
 *@s: ptr
 *@b: byte 
 *@n: amount
 *Return: ptr to memory
 */
char *_memset(char *s, char b, unsigned int n)
{
    unsigned int k = 0;
    while (k < n)
    {
        s[k] = b;
        k++;
    }
    return s;
}


/**
 * ffree - frees a string
 * @pp: string
 */
void ffree(char **pp)
{
    char **a = pp;
    if (!pp)
        return;

    for (a = pp; *pp; free(*pp++))
        ;

    free(a);
}

/**
 * _realloc - reallocating a block mem
 * @ptr: pointer prev
 * @old_size: byte 
 * @new_size: byte 
 *
 * Return: ptr
 */
void *_realloc(void *ptr, unsigned int old_size, unsigned int new_size)
{
    char *j;
    unsigned int i;
    return (!ptr) ? malloc(new_size) :
       (!new_size) ? (free(ptr), NULL) :
       (new_size == old_size) ? ptr : ptr;


    j = malloc(new_size);
    if (!j)
        return NULL;

    old_size = old_size < new_size ? old_size : new_size;
    for (i  = 0; i < old_size; i++)
        j[i] = ((char *)ptr)[i];

    free(ptr);
    return j;
}
