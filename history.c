#include "shell.h"


/**
 * get_history_file - history file
 * @info: param struct
 *
 * Return: allocated str with history file
 */
char *get_history_file(info_t *info)
{
char *buf = NULL, *dir;
dir = _getenv(info, "HOME=");
return (dir
? (char *)malloc(sizeof(char) * (_strlen(dir) + _strlen(HIST_FILE) + 2))
? (buf = malloc(sizeof(char) * (_strlen(dir) + _strlen(HIST_FILE) + 2)),
buf[0] = 0,
_strcpy(_strcat(_strcpy(buf, dir), "/"), HIST_FILE),
buf)
: NULL
: NULL);

}

int write_history(info_t *info)
{
ssize_t fd;
char *filename = get_history_file(info);
list_t *node = NULL;

if (!filename)
{
free(filename);
return (-1);
}

fd = open(filename, O_CREAT | O_TRUNC | O_RDWR, 0644);
if (fd == -1)
{
free(filename);
return (-1);
}

free(filename);

node = info->history;
while (node)
{
_putsfd(node->str, fd);
_putfd('\n', fd);
node = node->next;
}

_putfd(BUF_FLUSH, fd);
close(fd);
return (1);
}

/**
 * read_history - checks history in the file
 * @info: param struct
 *
 * Return: count when success
 */

int read_history(info_t *info)
{
int i, last = 0, linecount = 0;
ssize_t fd, rdlen, fsize = 0;
struct stat st;
char *buf, *filename;

buf = NULL;
filename = get_history_file(info);
fd = open(filename, O_RDONLY);

if (!filename || (fd) == -1)
return (0);

if (fstat(fd, &st) == -1) {
close(fd);
free(filename);
return (0);
}

fsize = st.st_size;

buf = malloc(sizeof(char) * (fsize + 1));

if (!buf) {
close(fd);
free(filename);
return (0);
}

rdlen = read(fd, buf, fsize);

close(fd);
free(filename);

if ((rdlen) <= 0)
return free(buf), 0;

buf[fsize] = 0;

i = 0;
while (i < fsize)
{
if (buf[i] == '\n')
{
buf[i] = 0;
build_history_list(info, buf + last, linecount++);
last = i + 1;
}
i++;
}

if (last != i)
build_history_list(info, buf + last, linecount++);

free(buf);
info->histcount = linecount;

while (info->histcount-- >= HIST_MAX)
delete_node_at_index(&(info->history), 0);

renumber_history(info);
return (info->histcount);
}


/**
 * build_history_list - entry to history linked list
 * @info: Struct with args
 * @buf: buff
 * @linecount: history linecount, histcount
 *
 * Return: 0
 */
int build_history_list(info_t *info, char *buf, int linecount)
{
list_t *node = info->history;

add_node_end(&node, buf, linecount);

info->history = node;

return (0);
}


/**
 * renumber_history - renumbs the hist
 * @info: Structure args
 * Return: new histcount
 */

int renumber_history(info_t *info)
{
list_t *node = info->history;
int i;

for (i = 0; node; i++, node = node->next)
{
node->num = i;
}

info->histcount = i;
return (info->histcount);
}
