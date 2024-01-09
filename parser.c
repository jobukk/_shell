#include "shell.h"
#include <sys/stat.h>

/**
 * is_cmd - check if file is executable command
 * @info: info struct
 * @path: path to file
 *
 * Return: 1 true else 0 
 */
int is_cmd(info_t *info, char *path)
{
    struct stat st;

    (void)info;

    if (path && !stat(path, &st) && (st.st_mode & S_IFREG))
    {
        return 1;
    }

    return 0;
}

/**
 * dup_chars - duplicates char
 * @pathstr: PATH str
 * @start: starting index
 * @stop: stopping index
 *
 * Return: ptr to new buff
 */
char *dup_chars(char *pathstr, int start, int stop)
{
    static char buf[1024];
    int i = start, k = 0;

    while (i < stop)
    {
        buf[k] = (pathstr[i] != ':') ? pathstr[i] : buf[k];
        k += (pathstr[i++] != ':');
    }

    buf[k] = '\0';
    return buf;
}


/**
 * find_path - finds this cmd in PATH str
 * @info: info struct
 * @pathstr: PATH string
 * @cmd: cmd to find
 *
 * Return: path of cmd else NULL
 */
char *find_path(info_t *info, char *pathstr, char *cmd)
{
    int curr_pos = 0;
    char *path;
    int i = 0;

    if (!pathstr || (_strlen(cmd) > 2 && starts_with(cmd, "./") && is_cmd(info, cmd)))
        return cmd;

    for (i = 0; ; i++)
    {
        if (!pathstr[i] || pathstr[i] == ':')
        {
            path = dup_chars(pathstr, curr_pos, i);
            _strcat(path, (!*path) ? cmd : _strcat(_strcat(path, "/"), cmd));

            if (is_cmd(info, path))
                return path;

            if (!pathstr[i])
                break;

            curr_pos = i;
        }
    }

    return NULL;
}

