// Write a C program to create two threads 1st thread will take input of an array and 2nd thread will perform sorting i.e after 1st threads 2nd threads start execution.
#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>

#define MAX_SIZE 100

int arr[MAX_SIZE];
int n;

pthread_mutex_t mutex;
void* input_array(void* arg) {
    pthread_mutex_lock(&mutex);  // Lock the mutex to ensure synchronization

    // Take input for the array
    printf("Enter the number of elements: ");
    scanf("%d", &n);

    if (n > MAX_SIZE) {
        printf("Array size exceeds the maximum limit of %d\n", MAX_SIZE);
        pthread_mutex_unlock(&mutex);
        pthread_exit(NULL);
    }

    printf("Enter the elements of the array:\n");
    for (int i = 0; i < n; i++) {
        scanf("%d", &arr[i]);
    }

    pthread_mutex_unlock(&mutex);  // Unlock the mutex after taking input
    pthread_exit(NULL);
}

void* sort_array(void* arg) {
    pthread_mutex_lock(&mutex);  // Lock the mutex to ensure synchronization

    // Wait until input_thread has completed the input
    printf("\nSorting the array...\n");

    // Simple Bubble Sort algorithm for demonstration
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            if (arr[j] > arr[j + 1]) {
                // Swap elements
                int temp = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = temp;
            }
        }
    }

    // Print the sorted array
    printf("Sorted Array: ");
    for (int i = 0; i < n; i++) {
        printf("%d ", arr[i]);
    }
    printf("\n");

    pthread_mutex_unlock(&mutex);  // Unlock the mutex after sorting
    pthread_exit(NULL);
}

int main() {
    pthread_t thread1, thread2;

    pthread_create(&thread1, NULL, input_array, NULL);
    pthread_join(thread1, NULL);

    pthread_create(&thread2, NULL, sort_array, NULL);
    pthread_join(thread2, NULL);

    return 0;
}

