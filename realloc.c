#include "shell.h"


/**
**_memset - add memory with a constant byte
*@s:  ptr to the memory area
*@b:  byte to add  with
*@n:  amount of bytes to be filled
*Return: (s) ptr
*/

char *_memset(char *s, char b, unsigned int n)
{
unsigned int i = 0;

while (i < n)
{
s[i] = b;
i++;
}

return (s);
}



/**
* ffree - free str of strs
* @pp: str of strs
*/

void ffree(char **pp)
{
char **a = pp;
if (pp)
{
for (a = pp; *pp; free(*pp++))
;

free(a);
}
}

/**
* _memcpy - copies bytes from one block to another.
* @dest: destination.
* @src: source.
* @n: number size.
* Return: dest
*/
void *_memcpy(void *dest, const void *src, size_t n)
{
size_t i;
char *cdest = (char *)dest;
const char *csrc = (const char *)src;

for (i = 0; i < n; i++)
{
cdest[i] = csrc[i];
}

return (dest);
}

/**
* _realloc - reallocate block of memory
* @ptr: ptr to previous allocated block
* @old_size: byte size of previous block
* @new_size: byte size of new block
*
* Return: ptr block.
*/
void *_realloc(void *ptr, unsigned int old_size, unsigned int new_size)
{
char *p;

return ((!ptr) ? malloc(new_size) :
(new_size == 0) ? (free(ptr), NULL) :
(new_size == old_size) ? ptr :
((p = malloc(new_size)) ?
((void)_memcpy(p, ptr, old_size), free(ptr), p) :
NULL));
}
