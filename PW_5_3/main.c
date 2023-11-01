#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

#define DEFAULT_BUFFER_SIZE 127

void printPrompt(char *username) {
    printf("[%s]$", username);
}

int main(int argc, char *argv[]) {
    char username[100];
    char commandBuffer[DEFAULT_BUFFER_SIZE + 1];
    int bufferSize = DEFAULT_BUFFER_SIZE;

    for (int i = 1; i < argc; i++) {
        if (strcmp(argv[i], "-h") == 0 || strcmp(argv[i], "--help") == 0) {
            printf("Help: Your help message here.\n");
            return 0;
        } else if ((strcmp(argv[i], "-b") == 0 || strcmp(argv[i], "--buffer") == 0) && i + 1 < argc) {
            bufferSize = atoi(argv[i + 1]);
            i++;
        }
    }
    getlogin_r(username, sizeof(username));

    printf("User: %s\n", username);

    while (1) {
        printPrompt(username);

        if (fgets(commandBuffer, bufferSize, stdin) == NULL) {
            perror("Error reading command");
            return 1;
        }

        commandBuffer[strcspn(commandBuffer, "\n")] = '\0';

        if (strcmp(commandBuffer, "stop") == 0) {
            printf("Wait 3 seconds...\n");
            sleep(3);
            system("clear");
            break;
        }

        int result = system(commandBuffer);
        if (result == -1) {
            perror("Error executing command");
        }
    }

    return 0;
}
