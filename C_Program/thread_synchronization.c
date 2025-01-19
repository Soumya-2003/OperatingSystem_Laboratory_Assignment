//Consider 3 threads running simultaneously. First thread1 read a number a. After that thread2 reads a number b then thread3 will do addition of a and b. Synchronize it using semaphore.
#include <stdio.h>
#include <pthread.h>
#include <semaphore.h>

int a, b, sum;
sem_t sem1, sem2;

void* read_a(void* arg){
	printf("Thread 1: Enter value of a: ");
    scanf("%d", &a);
    sem_post(&sem1); // Signal that 'a' is read
    return NULL;
}

void* read_b(void* arg) {
    printf("Thread 2: Enter value of b: ");
    scanf("%d", &b);
    sem_post(&sem2); // Signal that 'b' is read
    return NULL;
}

void* compute_sum(void* arg) {
    sem_wait(&sem1); // Wait until 'a' is read
    sem_wait(&sem2); // Wait until 'b' is read
    sum = a + b;
    printf("Thread 3: Sum = %d\n", sum);
    return NULL;
}

int main() {
	pthread_t t1, t2, t3;
	
	// Initialize semaphores
    sem_init(&sem1, 0, 0);
    sem_init(&sem2, 0, 0);
    
    // Create threads
    pthread_create(&t1, NULL, read_a, NULL);
    pthread_create(&t2, NULL, read_b, NULL);
    pthread_create(&t3, NULL, compute_sum, NULL);
    
    // Join threads
    pthread_join(t1, NULL);
    pthread_join(t2, NULL);
    pthread_join(t3, NULL);
    
    // Destroy semaphores
    sem_destroy(&sem1);
    sem_destroy(&sem2);

    return 0;
}
