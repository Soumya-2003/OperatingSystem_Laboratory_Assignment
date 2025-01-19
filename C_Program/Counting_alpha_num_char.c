/*Write a C program to create a child process. Parent process send a string to child process using PIPE then child process will calculate how many, alphabet, numeric and special characters #, & are there?*/
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <ctype.h>
#include <string.h>

#define MAX_LEN 20

int main(){
	int pipefd[2];
	pid_t pid;
	char input_str[MAX_LEN];
	
	// Create the pipe
    if (pipe(pipefd) == -1) {
        perror("Pipe failed");
        return 1;
    }
    
    // Fork a child process
    pid = fork();
    
    if (pid < 0) {
        perror("Fork failed");
        return 1;
    }
    
    if (pid > 0) {
    	// Parent process
    	printf("Parent: Enter a string: ");
    	scanf("%99[^\n]", input_str);
    	
    	close(pipefd[0]);  // Close unused read end
        write(pipefd[1], input_str, strlen(input_str) + 1);  // Send string to child
        close(pipefd[1]);  // Close write end
        wait(NULL);
    }
    else {
    	char received_str[MAX_LEN];
        int alphabets = 0, digits = 0, special_chars = 0;
        
        close(pipefd[1]);  // Close unused write end
        read(pipefd[0], received_str, MAX_LEN);  // Read string from parent
        close(pipefd[0]);  // Close read end
        
        for (int i = 0; received_str[i] != '\0'; i++) {
        	if (isalpha(received_str[i]))  
                alphabets++;
            else if (isdigit(received_str[i]))  
                digits++;
            else if (received_str[i] == '#' || received_str[i] == '&' || received_str[i] == '*')  
                special_chars++;
        }
        
        printf("Child: String received: \"%s\"\n", received_str);
        printf("Child: Alphabets: %d\n", alphabets);
        printf("Child: Digits: %d\n", digits);
        printf("Child: Special characters (#, &): %d\n", special_chars);

        exit(0);
    }
    return 0;
}
