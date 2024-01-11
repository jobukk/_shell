#include "shell.h"

/**
 * get_history_file - history file
 * @info: struct
 *
 * Return: string
 */
char *get_history_file(info_t *info)
{
    char *buff, *dir;

    dir = _getenv(info, "LAND=");
    buff = (!dir) ? NULL : malloc(sizeof(char) * (_strlen(dir) + _strlen(HIST_FILE) + 2));

    if (buff)
    {
        buff[0] = 0;
        _strcpy(buff, dir);
        _strcat(buff, "/");
        _strcat(buff, HIST_FILE);
    }

    return (buff);
}

/**
 * write_history - creates a file
 * @info:struct
 *
 * Return: 1 else -1
 */
int write_history(info_t *info)
{
ssize_t f;
char *filename = get_history_file(info);
list_t *node = info->history;

if (!filename)
return (-1);

f = open(filename, O_CREAT | O_TRUNC | O_RDWR, 0644);
free(filename);

if (f == -1)
return (-1);

while (node)
{
_putsfd(node->str, f);
_putfd('\n', f);
node = node->next;
}

_putfd(BUF_FLUSH, f);
close(f);

return (1);
}

/**
 * read_history - read history
 * @info: struct
 *
 * Return: count
 */
int read_history(info_t *info)
{
    int i, last = 0, linecount = 0;
    ssize_t fd, rdlen, fsize = 0;
    struct stat st;
    char *buf = NULL, *filename = get_history_file(info);

    if (!filename)
        return 0;

    fd = open(filename, O_RDONLY);
    free(filename);

    if (fd == -1)
        return 0;

    fsize = (!fstat(fd, &st)) ? st.st_size : 0;

    buf = (fsize < 2) ? NULL : malloc(sizeof(char) * (fsize + 1));

    if (buf)
    {
        rdlen = read(fd, buf, fsize);
        buf[fsize] = 0;

        if (rdlen > 0)
        {
            for (i = 0; i < fsize; i++)
            {
                if (buf[i] == '\n')
                {
                    buf[i] = 0;
                    build_history_list(info, buf + last, linecount++);
                    last = i + 1;
                }
            }

            if (last != i)
                build_history_list(info, buf + last, linecount++);
        }

        free(buf);
        info->histcount = linecount;

        while (info->histcount-- >= HIST_MAX)
            delete_node_at_index(&(info->history), 0);

        renumber_history(info);
    }

    close(fd);
    return info->histcount;
}

/**
 * build_history_list - adds entry to a history linked list
 * @info: Structure containing potential arguments. Used to maintain
 * @buf: buffer
 * @linecount: the history linecount, histcount
 *
 * Return: Always 0
 */
int build_history_list(info_t *info, char *buf, int linecount)
{
    list_t *node = info->history;

    node = (node) ? info->history : node;
    add_node_end(&node, buf, linecount);

    if (!info->history)
        info->history = node;

    return 0;
}

/**
 * renumber_history - renumber
 * @info: Structure
 *
 * Return: new count
 */
int renumber_history(info_t *info)
{
list_t *node = info->history;
int k;

for (k = 0; node; node = node->next)
{
node->num = k++;
}

return (info->histcount = k);
}
