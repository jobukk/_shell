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
    void *new_ptr;
    if (!ptr) {
        return malloc(new_size);
    }

    if (new_size == 0) {
        free(ptr);
        return NULL;
    }

    if (new_size == old_size) {
        return ptr;
    }

    new_ptr = malloc(new_size);
    if (!new_ptr) {
        return NULL;  
    }

    memcpy(new_ptr, ptr, (old_size < new_size) ? old_size : new_size);

    free(ptr);

    return new_ptr;
}
