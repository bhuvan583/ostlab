#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>

#define BUFFER_SIZE 5  // Size of the buffer
#define NUM_ITEMS 10   // Total items to produce and consume

int buffer[BUFFER_SIZE]; // Shared buffer
int in = 0;              // Index for the next produced item
int out = 0;             // Index for the next consumed item
pthread_mutex_t mutex;   // Mutex for critical section
pthread_cond_t empty;    // Condition variable for empty buffer
pthread_cond_t full;     // Condition variable for full buffer

// Function for the producer
void* producer(void* arg) {
    for (int i = 0; i < NUM_ITEMS; i++) {
        pthread_mutex_lock(&mutex); // Lock the mutex

        // Wait if the buffer is full
        while ((in + 1) % BUFFER_SIZE == out) {
            pthread_cond_wait(&full, &mutex);
        }

        // Produce an item
        buffer[in] = i;
        printf("Producer produced: %d\n", buffer[in]);
        in = (in + 1) % BUFFER_SIZE; // Move the index for the next item

        pthread_cond_signal(&empty); // Signal that there is a new item
        pthread_mutex_unlock(&mutex); // Unlock the mutex

        // Simulate production time
        usleep(rand() % 100000); // Random sleep time for demonstration
    }
    pthread_exit(NULL);
}

// Function for the consumer
void* consumer(void* arg) {
    for (int i = 0; i < NUM_ITEMS; i++) {
        pthread_mutex_lock(&mutex); // Lock the mutex

        // Wait if the buffer is empty
        while (in == out) {
            pthread_cond_wait(&empty, &mutex);
        }

        // Consume an item
        int item = buffer[out];
        printf("Consumer consumed: %d\n", item);
        out = (out + 1) % BUFFER_SIZE; // Move the index for the next item

        pthread_cond_signal(&full); // Signal that there is space in the buffer
        pthread_mutex_unlock(&mutex); // Unlock the mutex

        // Simulate consumption time
        usleep(rand() % 100000); // Random sleep time for demonstration
    }
    pthread_exit(NULL);
}

int main() {
    pthread_t producerThread, consumerThread;

    // Initialize the mutex and condition variables
    pthread_mutex_init(&mutex, NULL);
    pthread_cond_init(&empty, NULL);
    pthread_cond_init(&full, NULL);

    // Create producer and consumer threads
    pthread_create(&producerThread, NULL, producer, NULL);
    pthread_create(&consumerThread, NULL, consumer, NULL);

    // Wait for both threads to finish
    pthread_join(producerThread, NULL);
    pthread_join(consumerThread, NULL);

    // Cleanup
    pthread_mutex_destroy(&mutex);
    pthread_cond_destroy(&empty);
    pthread_cond_destroy(&full);

    printf("Producer and consumer have finished.\n");
    pthread_exit(NULL);
}
