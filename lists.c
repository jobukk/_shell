#include "shell.h"

/**
 * add_node - adds a node to start
 * @head: address 
 * @str: field of node
 * @num: node index 
 *
 * Return: size 
 */
list_t *add_node(list_t **head, const char *str)
{
    list_t *new_node;
    if (!head || !str)
        return NULL;

    new_node = malloc(sizeof(list_t));
    return (!new_node ? NULL : (new_node->str = strdup(str)) ? (new_node->next = *head, *head = new_node, new_node) : (free(new_node), NULL));
}


/**
 * add_node_end - node to end
 * @head: ptr
 * @str: field of node
 * @num: node index 
 *
 * Return: size
 */
list_t *add_node_end(list_t **head, const char *str)
{
    list_t *new_node;
    if (!head || !str)
        return NULL;

    new_node = malloc(sizeof(list_t));
    if (!new_node)
        return NULL;

    new_node->str = strdup(str);
    if (!new_node->str)
    {
        free(new_node);
        return NULL;
    }

    new_node->next = NULL;

    if (*head == NULL)
    {
        *head = new_node;
    }
    else
    {
        list_t *temp = *head;
        for (; temp->next; temp = temp->next)
        {
            
        }
        temp->next = new_node;
    }

    return new_node;
}


/**
 * print_list_str - str element of a list_t
 * @h: first node
 *
 * Return: size of list
 */
size_t print_list_str(const list_t *h)
{
    size_t i = 0;

    for (; h; h = h->next)
    {
        _puts(h->str ? h->str : "(nil)");
        _puts("\n");
        i++;
    }

    return i;
}

/**
 * delete_node_at_index - deletes node
 * @head: address of ptr
 * @index: index of node
 *
 * Return: 1 else 0
 */
int delete_node_at_index(list_t **head, unsigned int index)
{
    list_t *node;
    list_t *prev_node;
    unsigned int i;
    if (!head || !*head)
        return 0;

    if (!index)
    {
        node = *head;
        *head = (*head)->next;
        free(node->str);
        free(node);
        return 1;
    }

    node = *head;
    prev_node = NULL;
    

    for (i = 0; node; i++)
    {
        if (i == index)
        {
            if (prev_node)
                prev_node->next = node->next;
            free(node->str);
            free(node);
            return 1;
        }

        prev_node = node;
        node = node->next;
    }

    return 0;
}

/**
 * free_list - frees 
 * @head: list_t 
 */
void free_list(list_t *head)
{
	list_t *temp;

	while (head)
	{
		temp = head->next;
		free(head->str);
		free(head);
		head = temp;
	}
}
