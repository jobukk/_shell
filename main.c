#include "shell.h"

int main(void) {
    while (1) {
        char *command = get_command();

        if (command == NULL) {
            printf("Exiting the shell\n");
            break;
        }

        if (strlen(command) > 0) {
            int result = execute_command(command);

            if (result == -1) {
                printf("Command execution failed\n");
            }
        }

        free(command);
    }

    return 0;
}
