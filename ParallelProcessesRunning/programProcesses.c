#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <stdbool.h>
#include <string.h>
#include <time.h>


bool is_integer(const char* str) {
    for (int i = 0; str[i] != '\0'; i++) {
        if (str[i] < '0' || str[i] > '9') {
            return false;
        }
    }
    return true;
}

void usleep_milliseconds(int milliseconds) {
    usleep(milliseconds * 1000);
}

int main(int argc, char *argv[]) {
    if (argc < 3) {
        printf("Usage: ./programProcesses <number of processes> <strings of processes>\n");
        return 1;
    }

    if (!is_integer(argv[1])) {
        printf("The number of processes must be a valid integer.\n");
        return 1;
    }

    int num_processes = atoi(argv[1]);
    int expected_args = 2 + 4 * num_processes;

    if (argc != expected_args) {
        printf("Incorrect number of arguments provided.\n");
        printf("Expected format: ./program <number of processes> <text> <color_foreground> <background> <time for wait before end>\n");
        return 1;
    }

    for (int i = 0; i < num_processes; i++) {
        pid_t pid = fork();

        if (pid < 0) {
            perror("Error while forking");
            return 1;
        }

        if (pid == 0) {
            int arg_idx = 2 + 4 * i;

            char *text = argv[arg_idx];
            int color_foreground = atoi(argv[arg_idx + 1]);
            int color_background = atoi(argv[arg_idx + 2]);
            int wait_time = atoi(argv[arg_idx + 3]);

            printf("\033[%dm\033[%dmI am %s and have identification %d\033[0m\n", color_foreground, color_background, text, getpid());
            usleep_milliseconds(wait_time);
            return 0;
        }
    }

    for (int i = 0; i < num_processes; i++) {
        wait(NULL);
    }

    return 0;
}
