#include "shell.h"

#define MAX_PATH_SIZE 1024


/**
 * Parsing, syntax analysis, or syntactic analysis is the process of analyzing a string of symbols,
 * either in natural language, computer languages or data structures
 */

/**
 * is_cmd - determines if a file is an executable command
 * @info: the info struct
 * @path: path to the file
 *
 * Return: 1 if true, 0 otherwise
 */
/**
 * New implementation of is_cmd function with different logic
 */
int is_cmd(info_t *info __attribute__((unused)), char *path)
{
    struct stat st;

    if (!path || stat(path, &st) == -1)
        return 0;

    return S_ISREG(st.st_mode) && (st.st_mode & S_IXUSR);
}



/**
 * dup_chars - duplicates characters
 * @pathstr: the PATH string
 * @start: starting index
 * @stop: stopping index
 *
 * Return: pointer to new buffer
 */
char *dup_chars(char *pathstr, int start, int stop)
{
    int i;
    int length = stop - start;
    char *buf = malloc(length + 1);  

    if (buf == NULL) {
        fprintf(stderr, "Memory allocation error\n");
        exit(EXIT_FAILURE);
    }

    i = 0;
    while (i < length) {
        buf[i] = pathstr[start + i];
        i++;
    }
    buf[length] = '\0';

    return buf;
}


/**
 * find_path - finds this cmd in the PATH string
 * @info: the info struct
 * @pathstr: the PATH string
 * @cmd: the cmd to find
 *
 * Return: full path of cmd if found or NULL
 */
char *find_path(info_t *info, char *pathstr, char *cmd)
{
    int i = 0;
    int curr_pos = 0;
    char *path;

    if (!pathstr)
        return (NULL);
    if ((_strlen(cmd) > 2) && starts_with(cmd, "./"))
    {
        if (is_cmd(info, cmd))
            return (cmd);
    }

    for (i = 0; ; i++)
    {
        if (!pathstr[i] || pathstr[i] == ':')
        {
            path = dup_chars(pathstr, curr_pos, i);
            if (!*path)
                _strcat(path, cmd);
            else
            {
                _strcat(path, "/");
                _strcat(path, cmd);
            }
            if (is_cmd(info, path))
                return (path);
            if (!pathstr[i])
                break;
            curr_pos = i;
        }
    }
    return (NULL);
}
