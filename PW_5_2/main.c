#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

void signalHandler(int signum) {
    printf("Handler %d: Process completed\n", signum);
    sleep(1);
}

int main(int argc, char *argv[]) {
    if (argc != 2) {
        printf("Usage: %s <number_of_handlers>\n", argv[0]);
        return 1;
    }

    int numHandlers = atoi(argv[1]);

    for (int i = 1; i <= numHandlers; i++) {
        if (signal(SIGCHLD, signalHandler) == SIG_ERR) {
            perror("Error registering signal handler");
            return 1;
        }
    }

    for (int i = 1; i <= numHandlers; i++) {
        pid_t child_pid = fork();
        if (child_pid == 0) {
            printf("Child %d: Process started\n", i);
            sleep(2);
            exit(0);
        } else if (child_pid < 0) {
            perror("Error forking process");
            return 1;
        }
    }

    for (int i = 1; i <= numHandlers; i++) {
        wait(NULL);
    }

    printf("All child processes completed\n");

    return 0;
}
