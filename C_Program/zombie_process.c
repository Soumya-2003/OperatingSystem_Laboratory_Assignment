/*Write a C program that will create a child process by using the fork() system call , then
forcefully create a zombie process and display the corresponding process id from process table.*/
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
int main() {
	pid_t pid;
	pid = fork(); // create child process
	if(pid < 0){
		perror("Fork failed");
		exit(1);
	}
	if(pid == 0){  // Child process
		printf("Child Process: PID = %d, Parent PID = %d\n", getpid(), getppid());
		printf("Child exiting...\n");
        exit(0);  // Child exits immediately (becomes zombie)
	}
	else {	// Parent process
		printf("Parent Process: PID = %d, Created Child PID = %d\n", getpid(), pid);
		printf("Parent sleeping for 10 seconds to observe zombie process...\n");
		
		sleep(10);
		
		wait(NULL);
        printf("Zombie process reaped. Parent exiting...\n");	
	}
	return 0;
}
