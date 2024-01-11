#include "shell.h"

/**
 * add_node - adds a node to start
 * @head: address 
 * @str: field of node
 * @num: node index 
 *
 * Return: size 
 */
list_t *add_node(list_t **head, const char *str, int num) 
{
    list_t *new_head;
    if (!head)
        return NULL;

    new_head = malloc(sizeof(list_t));
    if (!new_head)
        return (NULL);

    new_head->num = num;

    new_head->str = str ? strdup(str) : NULL;
    if (!new_head->str) {
        free(new_head);
        return NULL;
    }

    new_head->next = *head;
    *head = new_head;

    return (new_head);
}


/**
 * add_node_end - node to end
 * @head: ptr
 * @str: field of node
 * @num: node index 
 *
 * Return: size
 */
list_t *add_node_end(list_t **head, const char *str, int num)
{
    list_t *new_node;
    list_t *node;
    if (!head)
        return NULL;

    new_node = malloc(sizeof(list_t));
    if (!new_node)
        return NULL;

    new_node->num = num;

    new_node->str = str ? strdup(str) : NULL;
    if (!new_node->str) {
        free(new_node);
        return NULL;
    }

    new_node->next = NULL;

    if (!*head) {
        *head = new_node;
        return new_node;
    }

    node = *head;
    while (node->next)
        node = node->next;

    node->next = new_node;
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

            if (node->str)
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
void free_list(list_t **head_ptr) 
{
    list_t *node;
    list_t *next_node;
    if (!head_ptr || !*head_ptr)
        return;

    node = *head_ptr;
    
    while (node) {
        free(node->str);
        next_node = node->next;
        free(node);
        node = next_node;
    }

    *head_ptr = NULL;
}
