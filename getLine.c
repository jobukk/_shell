#include "shell.h"

/**
 * input_buf - buffs chain command
 * @info: param struct
 * @buf: address of buff
 * @len: address of len var
 *
 * Return: bytes read
 */
ssize_t input_buf(info_t *info, char **buf, size_t *len)
{
ssize_t r = 0;
size_t len_p = 0;
*len = 0;  

*buf = NULL;
if (*len && *buf != NULL)
{
signal(SIGINT, sigintHandler);

r = USE_GETLINE ? getline(buf, &len_p, stdin) : _getline(info, buf, &len_p);

if (r > 0)
{
if ((*buf)[r - 1] == '\n')
{
(*buf)[r - 1] = '\0';
r--;
}

info->linecount_flag = 1;
remove_comments(*buf);
build_history_list(info, *buf, info->histcount++);

*len = r;
info->cmd_buf = buf;
}
}

return (r);
}


/**
 * get_input - gets with no newline
 * @info: param struct
 *
 * Return: byte read
 */

ssize_t get_input(info_t *info)
{
static char *buf; /* the ';' command chain buffer */
static size_t i, j, len;
ssize_t r = 0;
char **buf_p = &(info->arg), *p;

_putchar(BUF_FLUSH);
r = input_buf(info, &buf, &len);

if (r == -1) /* EOF */
return (-1);

if (len) /* we have commands left in the chain buffer */
{
j = i;         /* init new iterator to current buf position */
p = buf + i;   /* get pointer for return */

check_chain(info, buf, &j, i, len);

for (; j < len && !is_chain(info, buf, &j); j++)
;

i = (i = j + 1) >= len ? (len = 0) : i;
info->cmd_buf_type = CMD_NORM;

*buf_p = p;             /* pass back pointer to current command position */
return (_strlen(p)); /* return length of current command */
}

*buf_p = buf; /* else not a chain, pass back buffer from _getline() */
return (r);     /* return length of buffer from _getline() */
}

/**
 * read_buf - read a buffer
 * @info: param struct
 * @buf: buffer
 * @i: size
 *
 * Return: r
 */

ssize_t read_buf(info_t *info, char *buf, size_t *i)
{
ssize_t r = 0;
r = read(info->readfd, buf, READ_BUF_SIZE);
*i = 0;  

if (*i && (r) >= 0)
*i = r;

return r;
}



/**
 * _getline - get next line of input from STDIN
 * @info: param struct
 * @ptr: address of ptr to buffer, preallocated or NULL
 * @length: size of preallocated ptr buffer if not NULL
 *
 * Return: s
 */
int _getline(info_t *info, char **ptr, size_t *length)
{
static char buf[READ_BUF_SIZE];
static size_t i, len;
size_t k;
ssize_t r = 0, s = 0;
char *p = *ptr;
char *new_p;
char *c;

if (p && length)
s = *length;

if (i == len)
i = len = 0;

r = read_buf(info, buf, &len);

if (r == -1 || (r == 0 && len == 0))
return (-1);

c = _strchr(buf + i, '\n');
k = c ? 1 + (size_t)(c - buf) : len;

new_p = _realloc(p, s, s + k + 1);

if (!new_p) /* MALLOC FAILURE! */
return (p ? (free(p), -1) : -1);

_strncat(new_p, buf + i, k - i + 1);

s += k - i;
i = k;
*ptr = p = new_p;

if (length)
*length = s;

return (s);
}


/**
 * sigintHandler -  ctrl-C
 * @sig_num: signal num
 *
 * Return: void
 */
void sigintHandler(__attribute__((unused)) int sig_num)
{
_puts("\n$ ");
_putchar(BUF_FLUSH);
}
