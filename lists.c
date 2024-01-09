#include "shell.h"

/**
* add_node - add node to start of alist
* @head: address of ptr of head
* @str: string field of node
* @num: node index used by history
*
* Return: size of the list
*/

list_t *add_node(list_t **head, const char *str, int num)
{
list_t *new_head;
if (!head)
return (NULL);

new_head = malloc(sizeof(list_t));
if (!new_head)
return (NULL);

new_head->num = num;
new_head->str = str ? _strdup(str) : NULL;

if (!new_head->str && str)
{
free(new_head);
return (NULL);
}

new_head->next = *head;
*head = new_head;

return (new_head);
}


/**
* print_list_str - print only the string element of a list_t linked list
* @h: ptr to first node
*
* Return: size of list
*/


size_t print_list_str(const list_t *h)
{
size_t i;

for (i = 0; h; h = h->next, i++)
{
_puts(h->str ? h->str : "(nil)");
_puts("\n");
}

return (i);
}

/**
 * add_node_end - add the node end of the list
 * @head: address of ptr to head node
 * @str: str field of node
 * @num: node index used by history
 *
 * Return: size of list
 */
list_t *add_node_end(list_t **head, const char *str, int num)
{
    list_t *new_node;
    list_t *node;
	if (!head || !(*head))
		return NULL;

	new_node = malloc(sizeof(list_t));
	if (!new_node)
		return NULL;

    _memset((void *)new_node, 0, sizeof(list_t));
	new_node->num = num;

	if (str)
	{
		new_node->str = _strdup(str);
		if (!new_node->str)
		{
			free(new_node);
			return NULL;
		}
	}

	node = *head;
	while (node->next)
		node = node->next;

	node->next = new_node;
	return new_node;
}


/**
* delete_node_at_index - remove node at acertain index
* @head: address of ptr's the first node
* @index: index of node to remove
*
* Return: On success 1 ,On failure 0
*/

int delete_node_at_index(list_t **head, unsigned int index)
{
unsigned int i = 0;
list_t *node;
list_t *prev_node;
if (!head || !*head)
return (0);

node = *head;
prev_node = NULL;

if (index == 0)
{
*head = node->next;
free(node->str);
free(node);
return (1);
}

for (i = 0; node; i++, prev_node = node, node = node->next)
{
if (i == index)
{
prev_node->next = node->next;
free(node->str);
free(node);
return (1);
}
}

return (0);
}

/**
* free_list - frees all nodes in list
* @head_ptr: address of ptr to head node
*
* Return: void
*/

void free_list(list_t **head_ptr)
{
list_t *node, *next_node, *head;

if (!head_ptr || !*head_ptr)
return;

head = *head_ptr;

for (node = head, next_node = NULL; node; node = next_node)
{
next_node = node->next;
free(node->str);
free(node);
}

*head_ptr = NULL;
}

