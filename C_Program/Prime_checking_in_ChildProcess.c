/*Write a C program where parent process send a number to child process using PIPE and child process compute whether that number is a prime number or not.*/
#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<sys/types.h>
#include<stdbool.h>

int isPrime(int);

int main(){
	int pipefd[2];
	pid_t pid;
	int num;
	
	// Create the pipe
	if(pipe(pipefd) == -1){
		perror("Pipe Failed");
		return 1;
	}
	pid = fork();
	if(pid < 0) {
		perror("Fork Failed");
		return 1;
	}
	if(pid > 0){ // Parent process
		close(pipefd[0]);  // close unused read end
		
		printf("Parent: Enter a number: ");
        scanf("%d", &num);
        
		write(pipefd[1], &num, sizeof(num));  // Send number to child
		close(pipefd[1]); // Close write end
		
		wait(NULL);
	}
	else {
		close(pipefd[1]); // Close unused write end
		read(pipefd[0], &num, sizeof(num)); // Read number from parent
        close(pipefd[0]); // Close read end
        
        if (isPrime(num) == 1)
            printf("Child: %d is a PRIME number.\n", num);
        else
            printf("Child: %d is NOT a prime number.\n", num);

        exit(0);
	}
	return 0;
}

int isPrime(int num) {
    if (num < 2) return 0;
    for (int i = 2; i * i <= num; i++) {
        if (num % i == 0)
            return 0;
    }
    return 1;
}
