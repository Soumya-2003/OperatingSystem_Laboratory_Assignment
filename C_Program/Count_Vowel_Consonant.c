/*Write a C program to create a child process. Parent process send a string to child
process using PIPE then child process will calculate how many vowel and consonant are there?*/
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <ctype.h>
#include <string.h>

#define MAX_LEN 20
void count_vowel_consonant(char str[]) {
    int vowel_count = 0;
    int consonant_count = 0;

    for (int i = 0; str[i] != '\0'; i++) {
        char ch = tolower(str[i]);
        if ((ch >= 'a' && ch <= 'z')) {  // Check if it's an alphabet
            if (ch == 'a' || ch == 'e' || ch == 'i' || ch == 'o' || ch == 'u') {
                vowel_count++;
            } else {
                consonant_count++;
            }
        }
    }
    printf("Vowels: %d\n", vowel_count);
    printf("Consonants: %d\n", consonant_count);
}

int main(){
	int pipefd[2];  // Pipe file descriptors
    pid_t pid;
    char input_str[MAX_LEN];
    
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
        close(pipefd[0]);  // Close unused read end

        printf("Parent Process (PID: %d): Enter a string: ", getpid());
        printf("Input String: ");
        scanf("%99[^\n]",input_str);
        write(pipefd[1], input_str, strlen(input_str) + 1);  // Send string through pipe
        close(pipefd[1]);
    }
    else {
    	// Child Process
        close(pipefd[1]);  // Close unused write end
        //char received_str[MAX_LEN];
        read(pipefd[0], input_str, MAX_LEN);  // Read string from pipe
        close(pipefd[0]);
        
        printf("\nChild Process (PID: %d, Parent PID: %d):\n", getpid(), getppid());
        count_vowel_consonant(input_str);
    }
    
    return 0;
}
