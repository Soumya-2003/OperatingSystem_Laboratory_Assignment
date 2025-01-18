// Solve the classical reader writer problem. Create 5 readers and 2 writers then synchronize it.
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>

sem_t wrt; // Semaphore for writer synchronization
pthread_mutex_t mutex; 
int read_count = 0;   
int data = 0;

void *reader(void *arg) {
	int reader_id = *((int *)arg);
	while(1){
		pthread_mutex_lock(&mutex);
		read_count++;
		if (read_count == 1) {
            sem_wait(&wrt); // First reader locks writers
        }
        pthread_mutex_unlock(&mutex);
        printf("Reader %d is reading data: %d\n", reader_id, data);
        sleep(1);
        
        pthread_mutex_lock(&mutex);
        read_count--;
        if (read_count == 0) {
            sem_post(&wrt); // Last reader unlocks writers
        }
        pthread_mutex_unlock(&mutex);
        sleep(1);
	}
}

void *writer(void *arg){
	int writer_id = *((int *)arg);
	while(1) {
		sem_wait(&wrt);
		data += 1;
		printf("Writer %d is writing data: %d\n", writer_id, data);
		sleep(1);
		sem_post(&wrt);
		sleep(1);
	}
}

int main() {
	pthread_t readers[5], writers[2];
	int reader_ids[5], writer_ids[2];
	
	sem_init(&wrt, 0, 1);
    pthread_mutex_init(&mutex, NULL);
    
    // Create 5 reader threads
    for (int i = 0; i < 5; i++) {
        reader_ids[i] = i + 1;
        pthread_create(&readers[i], NULL, reader, &reader_ids[i]);
    }
    
    // Create 2 writer threads
    for (int i = 0; i < 2; i++) {
        writer_ids[i] = i + 1;
        pthread_create(&writers[i], NULL, writer, &writer_ids[i]);
    }
    
    for (int i = 0; i < 5; i++) {
        pthread_join(readers[i], NULL);
    }
    for (int i = 0; i < 2; i++) {
        pthread_join(writers[i], NULL);
    }
    
    sem_destroy(&wrt);
    pthread_mutex_destroy(&mutex);

    return 0;
}
