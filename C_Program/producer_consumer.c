//Solve the classical producer consumer problem. Consider the buffer is bounded. Create at least 3 producers and 3 consumers.
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>

#define BUFFER_SIZE 5  // Buffer capacity
#define NUM_PRODUCERS 3
#define NUM_CONSUMERS 3
#define ITEMS_TO_PRODUCE 10

int buffer[BUFFER_SIZE];  // Shared buffer
int in = 0, out = 0;

pthread_mutex_t mutex;    // Mutex for buffer access
sem_t empty;              // Counts empty slots
sem_t full;

void *producer(void *arg) {
	int id = *(int*)arg;
	for (int i = 0; i < ITEMS_TO_PRODUCE; i++) {
		int item = rand() % 100;  // Generate random item
		sem_wait(&empty);  // Wait if buffer is full
		pthread_mutex_lock(&mutex);
		
		buffer[in] = item; //Add item in buffer
		printf("Producer %d: Produced item %d at buffer[%d]\n", id, item, in);
		in = (in + 1) % BUFFER_SIZE;
		
		pthread_mutex_unlock(&mutex);
        sem_post(&full);  // Signal that buffer has an item
        sleep(1);
	}
}

void *consumer(void *arg){
	int id = *(int*)arg;
	for (int i = 0; i < ITEMS_TO_PRODUCE; i++){
		sem_wait(&full); // Wait if buffer is empty
		pthread_mutex_lock(&mutex);
		
		int item = buffer[out]; //Consume item from buffer
		printf("\tConsumer %d: Consumed item %d from buffer[%d]\n", id, item, out);
		out = (out + 1) % BUFFER_SIZE;
		
		pthread_mutex_unlock(&mutex);
        sem_post(&empty);  // Signal that buffer has an empty slot
        sleep(1);
	}
}

int main() {
	pthread_t producers[NUM_PRODUCERS], consumers[NUM_CONSUMERS];
	
	// Initialize mutex and semaphores
    pthread_mutex_init(&mutex, NULL);
    sem_init(&empty, 0, BUFFER_SIZE);  // Initially all slots are empty
    sem_init(&full, 0, 0);  // Initially no items are present
    
    // Create producer threads
    for (int i = 0; i < NUM_PRODUCERS; i++) {
        int* id = malloc(sizeof(int));
        *id = i + 1;
        pthread_create(&producers[i], NULL, producer, id);
    }
    
    // Create consumer threads
    for (int i = 0; i < NUM_CONSUMERS; i++) {
        int* id = malloc(sizeof(int));
        *id = i + 1;
        pthread_create(&consumers[i], NULL, consumer, id);
    }
    
    // Join all threads
    for (int i = 0; i < NUM_PRODUCERS; i++) {
        pthread_join(producers[i], NULL);
    }
    for (int i = 0; i < NUM_CONSUMERS; i++) {
        pthread_join(consumers[i], NULL);
    }
    
    // Destroy mutex and semaphores
    pthread_mutex_destroy(&mutex);
    sem_destroy(&empty);
    sem_destroy(&full);

    printf("All producers and consumers finished execution.\n");
    return 0;
}
