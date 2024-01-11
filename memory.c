#include "shell.h"

/**
 * bfree - frees a ptr
 * @ptr: address
 *
 * Return: 1
 */
int bfree(void **ptr)
{
	return (ptr && *ptr) ? (free(*ptr), *ptr = NULL, 1) : 0;
}
