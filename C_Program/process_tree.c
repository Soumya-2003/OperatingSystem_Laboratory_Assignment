// Write a C program that will create a child process using the fork() system call. Draw the process tree by generating different child process.
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>

void create_child_process(int level) {
    pid_t pid = fork();

    if (pid < 0) {
        perror("Fork failed");
        exit(1);
    }

    if (pid == 0) {  // Child process
        printf("Child Process: PID = %d, Parent PID = %d, Level = %d\n", getpid(), getppid(), level);
        
        // If level < 2, create another child
        if (level < 2) {
            create_child_process(level + 1);
        }

        sleep(2); // Allow time to observe process tree
    } else {
        wait(NULL); // Parent waits for child to finish
    }
}

int main() {
    printf("Parent Process: PID = %d\n", getpid());

    // Parent creates two child processes
    create_child_process(1);
    create_child_process(1);

    sleep(3); // Allow time to observe process tree
    return 0;
}

