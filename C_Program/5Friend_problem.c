// A book is shared among 5 friends.each friend will read the book but at a time the book can not be read by any two persons. Show how the book is read by the friends.
#include <stdio.h>
#include <pthread.h>
#include <unistd.h>

pthread_mutex_t mutex;

void* read_book(void* friend_id) {
    int id = *(int*) friend_id;
    
    pthread_mutex_lock(&mutex);

    printf("Friend %d is reading the book...\n", id);
    sleep(2);  // Simulating the time taken to read the book
    printf("Friend %d has finished reading the book.\n", id);

    // Unlock the mutex to allow the next friend to read
    pthread_mutex_unlock(&mutex);

    pthread_exit(NULL);
}

int main() {
    pthread_t threads[5];
    int friend_ids[5] = {1, 2, 3, 4, 5};

    for (int i = 0; i < 5; i++) {
        if (pthread_create(&threads[i], NULL, read_book, &friend_ids[i]) != 0) {
            perror("Failed to create thread");
            return 1;
        }
    }

    // Wait for all threads to complete
    for (int i = 0; i < 5; i++) {
        pthread_join(threads[i], NULL);
    }

    return 0;
}

