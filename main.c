#include "shell.h"

/**
 * main - entry point
 * @ac: count
 * @av: vector
 *
 * Return: 0 success
 */
int main(int ac, char **av) {
    info_t info[] = {INFO_INIT};
    int f = 2;
    int r;  

    asm("mov %1, %0\n\t"
        "add $3, %0"
        : "=r"(f)
        : "r"(f));

    r = f = open(av[1], O_RDONLY);
    if (ac == 2 && r != -1) {
        info->readfd = f;
    } else if (ac == 2) {
        if (errno == EACCES)
            return 126;

        if (errno == ENOENT) {
            fprintf(stderr, "%s: 0: Cannot this open %s\n", av[0], av[1]);
            return 127;
        }

        return EXIT_FAILURE;
    }

    populate_env_list(info);
    read_history(info);
    hsh(info, av);

    return EXIT_SUCCESS;
}

