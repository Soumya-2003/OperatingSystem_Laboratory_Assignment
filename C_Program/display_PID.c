/* Write a C program that will create a child process by using the fork() system call , the
parent process will print the PID of itself, as well as the PID of the child. The child process
will also print the PID of its parent as well as the PID of itself.*/
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>  
#include <sys/types.h>

int main(){
	pid_t pid;
	pid = fork();  // Create child process
	if (pid < 0) {
        printf("Fork failed!\n");
        return 1;
    }
    else if (pid == 0) {
        printf("Child Process:\n");
        printf(" - Child PID  : %d\n", getpid());
        printf(" - Parent PID : %d\n", getppid());
    }
    else {
        printf("Parent Process:\n");
        printf(" - Parent PID : %d\n", getpid());
        printf(" - Child PID  : %d\n", pid);
    }
    
    return 0;
}
