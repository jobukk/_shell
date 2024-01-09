#include "shell.h"


/**
* list_len - check length of linked list
* @h: ptr of first node
*
* Return: size of list
*/

size_t list_len(const list_t *h)
{
size_t i;

for (i = 0; h; h = h->next, i++)
;


return (i);
}


/**
* list_to_strings - returns an array of strs
* @head: ptr to first node
*
* Return: array of strs
*/

char **list_to_strings(list_t *head)
{
list_t *node = head;
size_t i = list_len(head), j;
char **strs;
char *str;

if (!head)
return (NULL);


strs = malloc(sizeof(char *) * (i + 1));
if (!strs || !i)
{
free(strs);
return (NULL);
}


i = 0;
while (node)
{
str = malloc(_strlen(node->str) + 1);
if (!str)
{
for (j = 0; j < i; j++)
free(strs[j]);
free(strs);
return (NULL);
}

str = _strcpy(str, node->str);
strs[i] = str;
i++;
node = node->next;
}

strs[i] = NULL;
return (strs);
}


/**
* print_list - print all elements linked list
* @h: ptr to first node
*
* Return: size of list
*/

size_t print_list(const list_t *h)
{
size_t i;

for (i = 0; h; h = h->next, i++)
{
_puts(convert_number(h->num, 10, 0));
_putchar(':');
_putchar(' ');
_puts(h->str ? h->str : "(nil)");
_puts("\n");
}

return (i);
}

/**
* node_starts_with - returns node with str that start with prefix
* @node: ptr to list head
* @prefix: str to match
* @c: the next char after prefix to match
*
* Return: match node or null
*/

list_t *node_starts_with(list_t *node, char *prefix, char c)
{
for (; node; node = node->next)
{
char *p = starts_with(node->str, prefix);
if (p && ((c == -1) || (*p == c)))
return (node);
}

return (NULL);
}

/**
* get_node_index - takes the index of a node
* @head: ptr to list head
* @node: ptr to the node
*
* Return: node  index or -1
*/
ssize_t get_node_index(list_t *head, list_t *node)
{
size_t i = 0;
for (i = 0; head; head = head->next, i++)
{
if (head == node)
return (i);
}

return (-1);
}
