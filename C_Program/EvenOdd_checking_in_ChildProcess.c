/*Write a C program where the parent process sends a number to child process using PIPE
and child process computes whether that number is an odd or even number.*/
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>

int main(){
	int pipefd[2];
	pid_t pid;
    int num;
    
    // Create the pipe
    if (pipe(pipefd) == -1) {
        perror("Pipe failed");
        exit(1);
    }
    // Fork to create a child process
    pid = fork();
    if (pid < 0) {
        perror("Fork failed");
        exit(1);
    }
    
    if (pid > 0){
    	// Parent Process
    	close(pipefd[0]); //close reading end
    	printf("Parent: Enter a number: ");
        scanf("%d", &num);
        
        write(pipefd[1], &num, sizeof(num));
        close(pipefd[1]); //close writing end
        wait(NULL);
    }
    else{
    	// Child process
    	close(pipefd[1]);  // Close writing end
    	
        read(pipefd[0], &num, sizeof(num)); // Read the number from the pipe
        close(pipefd[0]);  // Close reading end
        
        if (num % 2 == 0)
            printf("Child: The number %d is EVEN.\n", num);
        else
            printf("Child: The number %d is ODD.\n", num);
    }
    return 0;
}
