#include "shell.h"

/**

 * input_buf - chained command

 * @info: param struct

 * @buf: buffer

 * @len: len var

 * Return: bytes read

 */

ssize_t input_buf(info_t *info, char **buf, size_t *len)
{
    ssize_t bytesRead = 0;

    if (*len == 0) {
        free(*buf);
        *buf = NULL;
        signal(SIGINT, sigintHandler);

#if USE_GETLINE
        bytesRead = getline(buf, len, stdin);
#else
        bytesRead = _getline(info, buf, len);
#endif

        if (bytesRead > 0) {
            if ((*buf)[bytesRead - 1] == '\n') {
                (*buf)[bytesRead - 1] = '\0';
                bytesRead--;
            }

            info->linecount_flag = 1;
            remove_comments(*buf);
            build_history_list(info, *buf, info->histcount++);
            *len = bytesRead;
            info->cmd_buf = buf;
        }
    }

    return bytesRead;
}




/**

 * get_input - get a line
 * @info: param struct
 * Return: byte read

 */

ssize_t get_input(info_t *info)
{
    static char *buf = NULL;
    static size_t i = 0, len = 0;
    ssize_t bytesRead = 0;
    char **buf_p = &(info->arg);

    _putchar(BUF_FLUSH);

    bytesRead = input_buf(info, &buf, &len);

    if (bytesRead == -1) {
        return -1;  
    }

    if (len > 0) {
        size_t j = i;
        char *p = buf + i;

        check_chain(info, buf, &j, i, len);

        while (j < len && !is_chain(info, buf, &j)) {
            j++;
        }

        i = (j < len) ? j + 1 : (i = len = 0, info->cmd_buf_type = CMD_NORM);

        *buf_p = p;

        return _strlen(p);
    }

    *buf_p = buf;

    return bytesRead;
}




/**

 * read_buf - read a buffer

 * @info: param struct

 * @buf: buffer

 * @i: size

 *

 * Return: r

 */

#include <unistd.h>

ssize_t read_buf(info_t *info, char *buf, size_t *i)
{
    ssize_t bytesRead;
    if (*i > 0) {
        return 0;  
    }

    bytesRead = read(info->readfd, buf, READ_BUF_SIZE);

    if (bytesRead >= 0) {
        *i = bytesRead;  
    }

    return bytesRead;
}





/**

 * _getline - next line

 * @info: param struct

 * @ptr: pointer 

 * @length: preallocated ptr size

 *

 * Return: s

 */

#include <stddef.h>

int _getline(info_t *info, char **ptr, size_t *length)
{
    static char buf[READ_BUF_SIZE];
    static size_t i = 0, len = 0;
    size_t k;
    ssize_t bytesRead;
    char *p = *ptr, *new_p = NULL, *c;

    if (p && length)
        k = *length;
    else
        k = 0;

    if (i == len)
        i = len = 0;

    bytesRead = read_buf(info, buf, &len);

    if (bytesRead == -1 || (bytesRead == 0 && len == 0))
        return -1;

    c = _strchr(buf + i, '\n');
    k = c ? 1 + (size_t)(c - buf) : len;

    new_p = _realloc(p, k, k + 1);

    if (!new_p)
        return p ? (free(p), -1) : -1;

    if (k)
        _strncat(new_p, buf + i, k);

    i = k;
    p = new_p;

    if (length)
        *length = k;

    *ptr = p;
    return k;
}





/**

 * sigintHandler - ctrl-C

 * @sig_num:  number

 *

 * Return: void

 */

void sigintHandler(__attribute__((unused)) int sig_num)

{

	_puts("\n");

	_puts("$ ");

	_putchar(BUF_FLUSH);

}