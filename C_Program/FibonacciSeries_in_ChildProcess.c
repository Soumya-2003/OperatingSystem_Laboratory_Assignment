/*Write a C program that will create a child process. The parent process will announce that
it is the parent process and taking a input from user it will send it to the child process. The
child will announce that it is the child process and will display the Fibonacci series of the
number (Up to the range).*/
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <string.h>

#define MAX_LEN 10   // Maximum length of input number

void fibonacci(int n){
	int a = 0, b = 1, next;
	printf("Fibonacci Series up to %d terms:\n", n);
	for (int i = 0; i < n; i++){
		printf("%d ", a);
		next = a + b;
		a = b;
        b = next;
	}
	printf("\n");
}

int main(){
	int pipefd[2];  // Pipe file descriptors
    pid_t pid;
    int num;
    
    if (pipe(pipefd) == -1) {
        perror("Pipe failed");
        return 1;
    }

    pid = fork();  // Create a child process

    if (pid < 0) {
        perror("Fork failed");
        return 1;
    }
    
    if (pid > 0) {  // Parent process
    	close(pipefd[0]);  // Close unused read end
        printf("Parent Process (PID: %d):\n", getpid());
        printf("Enter a number for Fibonacci series: ");
        scanf("%d", &num);  // Read integer input
        write(pipefd[1], &num, sizeof(int));  // Send integer directly
        close(pipefd[1]);  // Close write end
        wait(NULL);  // Wait for child process to complete
    }
    else {
    	close(pipefd[1]);  // Close unused write end
        read(pipefd[0], &num, sizeof(int));  // Read integer from pipe
        close(pipefd[0]);  // Close read end
        printf("\nChild Process (PID: %d, Parent PID: %d):\n", getpid(), getppid());
        fibonacci(num); 
    }
    
    return 0;
}
