//Write a C program to create a child process. Parent process send a string to child process using PIPE then child process will check the string is palindrome or not.
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>

#define MAX_LEN 15

int is_palindrome(char str[]){
	int len = strlen(str);
	for (int i = 0; i < len / 2; i++) {
		if (str[i] != str[len - i - 1]) {
            return 0;
        }
	}
	return 1;
}

int main(){
	int pipefd[2];
	pid_t pid;
	char input_str[MAX_LEN], buffer[MAX_LEN];
	
	// Create pipe
    if (pipe(pipefd) == -1) {
        perror("Pipe failed");
        return 1;
    }
    
    pid = fork();
    
    if (pid < 0) {
        perror("Fork failed");
        return 1;
    }
    
    if (pid > 0) {  // Parent Process
    	close(pipefd[0]); // Close unused read end
    	printf("Parent: Enter a string: ");
    	scanf("%99[^\n]", input_str);
    	write(pipefd[1], input_str, strlen(input_str) + 1);
    	close(pipefd[1]); // Close write end
    }
    else {   // Child Process
    	close(pipefd[1]); // Close unused write end
    	read(pipefd[0], buffer, MAX_LEN);
    	close(pipefd[0]); // Close read end
    	
    	if (is_palindrome(buffer)) {
            printf("Child: The string \"%s\" is a Palindrome.\n", buffer);
        } else {
            printf("Child: The string \"%s\" is NOT a Palindrome.\n", buffer);
        }
    }
    return 0;
}
