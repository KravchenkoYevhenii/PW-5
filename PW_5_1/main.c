#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char *argv[]) {
    if (argc < 2) {
        printf("Usage: %s <commands>\n", argv[0]);
        return 1;
    }

    char commands[1000] = "";
    for (int i = 1; i < argc; i++) {
        strcat(commands, argv[i]);
        if (i < argc - 1) {
            strcat(commands, " ");
        }
    }

    int exitCode = system(commands);

    printf("Exit code: %d\n", exitCode);

    return 0;
}
