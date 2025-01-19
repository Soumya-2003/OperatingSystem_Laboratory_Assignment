//Create two threads one thread will take the input of a matrix and 2nd thread will check the matrix is symmetric or not.
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

#define SIZE 10

int matrix[SIZE][SIZE];
int n;
pthread_mutex_t lock;

void *input_matrix(void *arg) {
	pthread_mutex_lock(&lock);
	printf("Enter the size of the matrix (n x n): ");
    scanf("%d", &n);
    printf("Enter the matrix elements (%d x %d):\n", n, n);
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            scanf("%d", &matrix[i][j]);
        }
    }
    pthread_mutex_unlock(&lock);
    wait(NULL);
}

void *check_symmetric(void *arg) {
	pthread_mutex_lock(&lock);
    int is_symmetric = 1;
    
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            if (matrix[i][j] != matrix[j][i]) {
                is_symmetric = 0;
                break;
            }
        }
        if (!is_symmetric) break;
    }
    printf("\nThe matrix is %s\n", is_symmetric ? "Symmetric" : "Not Symmetric");
    pthread_mutex_unlock(&lock);
    wait(2);
}

int main(){
	pthread_t thread1, thread2;
	pthread_mutex_init(&lock, NULL);
	
	pthread_create(&thread1, NULL, input_matrix, NULL);
    pthread_join(thread1, NULL);
    
    pthread_create(&thread2, NULL, check_symmetric, NULL);
    pthread_join(thread2, NULL);
    
    pthread_mutex_destroy(&lock);
    return 0;
}
