#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/wait.h>

char* FILE_NAME = "output";

int main(int argc, char *argv[]) {
    int opt;
    int numChildren = 0;
    char* fileName = NULL;

    while ((opt = getopt(argc, argv, "f:n:")) != -1) {
        switch (opt) {
            case 'f':
                FILE_NAME = optarg;
                break;
            case 'n':
                numChildren = atoi(optarg);
                break;
            default:
                fprintf(stderr, "Usage: %s [-f <file_name>] [-n <num_children>]\n", argv[0]);
                exit(EXIT_FAILURE);
        }
    }

    for (int i = 1; i <= numChildren; i++) {
        pid_t child_pid = fork();
        if (child_pid == 0) {
            char outputFileName[100];
            if (FILE_NAME != NULL) {
                sprintf(outputFileName, "%s_%d.txt", FILE_NAME, i);
            } else {
                sprintf(outputFileName, "output_%d.txt", i);
            }

            FILE* outputFile = fopen(outputFileName, "w");
            if (outputFile != NULL) {
                srand(i);
                int random_number = rand() % 2;
                fprintf(outputFile, "%d\n", random_number);
                fclose(outputFile);
                printf("Child %d: Created %s\n", i, outputFileName);
                exit(EXIT_SUCCESS);
            } else {
                perror("Error opening output file");
                exit(EXIT_FAILURE);
            }
        } else if (child_pid < 0) {
            perror("Error forking process");
            exit(EXIT_FAILURE);
        }
    }

    for (int i = 1; i <= numChildren; i++) {
        wait(NULL);
    }

    return 0;
}
