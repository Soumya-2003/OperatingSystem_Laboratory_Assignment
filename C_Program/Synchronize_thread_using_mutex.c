/*A variable count is shared by 3 threads. Each thread will increment the variable. Write a C
program to synchronize the threads.*/
#include <stdio.h>
#include <pthread.h>

#define NUM_THREADS 3

int count = 0;
pthread_mutex_t lock;

void *increment_count(void *arg) {
	pthread_mutex_lock(&lock);  
    count++;
    printf("Thread %ld: count = %d\n", (long)arg, count);
    pthread_mutex_unlock(&lock);  // Unlock the mutex after modifying the shared variable
    return NULL;
}

int main() {
	pthread_t threads[NUM_THREADS];  // Array to hold thread IDs
    long i;
    
    // Initialize the mutex
    if (pthread_mutex_init(&lock, NULL) != 0) {
        printf("Mutex initialization failed\n");
        return 1;
    }
    
    // Create threads
    for (i = 0; i < NUM_THREADS; i++) {
        if (pthread_create(&threads[i], NULL, increment_count, (void *)i) != 0) {
            printf("Thread creation failed\n");
            return 1;
        }
    }

    // Wait for all threads to finish
    for (i = 0; i < NUM_THREADS; i++) {
        pthread_join(threads[i], NULL);
    }

    // Destroy the mutex
    pthread_mutex_destroy(&lock);
    
    printf("Final count: %d\n", count);

    return 0;
}
