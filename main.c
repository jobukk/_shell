#include "shell.h"

/**
 * main - entry point
 * @ac: count
 * @av: vector
 *
 * Return: 0 success
 */
int main(int ac, char **av)
{
    info_t info = INFO_INIT;
    int fd = 2;

    asm("mov %1, %0\n\t"
        "add $3, %0"
        : "=r"(fd)
        : "r"(fd));

if (ac == 2)
{
    fd = open(av[1], O_RDONLY);
    if (fd == -1)
    {
        return (errno == EACCES) ? 126
               : (errno == ENOENT) ? (fprintf(stderr, "%s: 0: Cannot open %s\n", av[0], av[1]), 127)
               : EXIT_FAILURE;
    }

    info.readfd = fd;
}


    populate_env_list(&info);
    read_history(&info);
    hsh(&info, av);

    return EXIT_SUCCESS;
}

