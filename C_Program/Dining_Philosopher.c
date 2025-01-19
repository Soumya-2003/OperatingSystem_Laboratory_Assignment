//Solve the classical dining philosophers(5 philosophers) problem.
#include <stdio.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>

#define NUM_PHILOSOPHERS 5

sem_t forks[NUM_PHILOSOPHERS];
pthread_mutex_t mutex;

void think(int philosopher) {
    printf("Philosopher %d is thinking...\n", philosopher);
    sleep(1);
}

void eat(int philosopher) {
    printf("Philosopher %d is eating...\n", philosopher);
    sleep(2);
}

void* philosopher(void* num){
	int philosopher = *(int*)num;
	while(1) {
		think(philosopher);
		
		// Avoid deadlock: Pick right fork first for even philosophers
        if (philosopher % 2 == 0) {
            sem_wait(&forks[(philosopher + 1) % NUM_PHILOSOPHERS]);
            sem_wait(&forks[philosopher]);
        } else {
            sem_wait(&forks[philosopher]);
            sem_wait(&forks[(philosopher + 1) % NUM_PHILOSOPHERS]);
        }

        eat(philosopher);
        
        sem_post(&forks[philosopher]);
        sem_post(&forks[(philosopher + 1) % NUM_PHILOSOPHERS]);
	}
	return NULL;
}

int main(){
	pthread_t philosophers[NUM_PHILOSOPHERS];
    int philosopher_ids[NUM_PHILOSOPHERS];
    
    for (int i = 0; i < NUM_PHILOSOPHERS; i++) {
        sem_init(&forks[i], 0, 1);
    }
    
    for (int i = 0; i < NUM_PHILOSOPHERS; i++) {
        philosopher_ids[i] = i;
        pthread_create(&philosophers[i], NULL, philosopher, &philosopher_ids[i]);
    }
    
    for (int i = 0; i < NUM_PHILOSOPHERS; i++) {
        pthread_join(philosophers[i], NULL);
    }
    
    for (int i = 0; i < NUM_PHILOSOPHERS; i++) {
        sem_destroy(&forks[i]);
    }
    
    return 0;
}
