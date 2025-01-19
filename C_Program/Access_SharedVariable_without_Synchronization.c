// a count variable is shared among two threads, each thread will increment the count. show the output if the threads are not synchronized.
#include <stdio.h>
#include <pthread.h>

#define NUM_INCREMENTS 1000000

// Shared variable
int count = 0;

void* increment_count(void* arg) {
    for (int i = 0; i < NUM_INCREMENTS; i++) {
        count++; 
    }
    pthread_exit(NULL);
}

int main() {
    pthread_t thread1, thread2;

    // Create two threads
    pthread_create(&thread1, NULL, increment_count, NULL);
    pthread_create(&thread2, NULL, increment_count, NULL);

    // Wait for both threads to complete
    pthread_join(thread1, NULL);
    pthread_join(thread2, NULL);

    // Output the final count value
    printf("Final count: %d\n", count);

    return 0;
}

