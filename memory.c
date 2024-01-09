#include "shell.h"


/**
* bfree - free ptr and NULLs the address
* @ptr: address of the ptr to free
*
* Return: 1 on success and 0 on fail.
*/
int bfree(void **ptr)
{
return ((ptr && *ptr) ? (free(*ptr), *ptr = NULL, 1) : 0);
}
