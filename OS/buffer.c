#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <semaphore.h>
#include <pthread.h>
#include <fcntl.h>  // For O_CREAT flag
#include <sys/mman.h>  // For memory mapping (shared memory)

#define BUFFER_SIZE 100

// Shared buffer and related synchronization
int buffer[BUFFER_SIZE];
int in = 0, out = 0;

// Semaphores
sem_t *empty;  // Count of empty slots in the buffer
sem_t *full;   // Count of filled slots in the buffer
sem_t *mutex;  // Mutex to protect buffer access

// Function for the producer
void *producer(void *param) {
    for (int i = 0; i < 1000; i++) {
        sem_wait(empty);   // Wait for an empty slot
        sem_wait(mutex);   // Lock the buffer

        buffer[in] = i;  // Produce an item
        printf("Produced: %d\n", i);

        in = (in + 1) % BUFFER_SIZE;  // Update buffer index

        sem_post(mutex);   // Unlock the buffer
        sem_post(full);    // Signal that an item is produced
        usleep(rand() % 1000);  // Simulate production delay
    }

    return NULL;
}

// Function for the consumer
void *consumer(void *param) {
    for (int i = 0; i < 1000; i++) {
        sem_wait(full);    // Wait for a filled slot
        sem_wait(mutex);   // Lock the buffer

        int item = buffer[out];  // Consume an item
        printf("Consumed: %d\n", item);

        out = (out + 1) % BUFFER_SIZE;  // Update buffer index

        sem_post(mutex);   // Unlock the buffer
        sem_post(empty);   // Signal that an empty slot is available
        usleep(rand() % 1000);  // Simulate consumption delay
    }

    return NULL;
}

int main() {
    // Initialize semaphores
    empty = sem_open("/empty", O_CREAT, 0644, BUFFER_SIZE);  // Semaphore for empty slots
    full = sem_open("/full", O_CREAT, 0644, 0);              // Semaphore for full slots
    mutex = sem_open("/mutex", O_CREAT, 0644, 1);             // Mutex for mutual exclusion

    // Check if semaphores were created successfully
    if (empty == SEM_FAILED || full == SEM_FAILED || mutex == SEM_FAILED) {
        perror("Semaphore initialization failed");
        return 1;
    }

    // Create producer and consumer threads
    pthread_t producer_thread, consumer_thread;

    if (pthread_create(&producer_thread, NULL, producer, NULL) != 0) {
        perror("Failed to create producer thread");
        return 1;
    }

    if (pthread_create(&consumer_thread, NULL, consumer, NULL) != 0) {
        perror("Failed to create consumer thread");
        return 1;
    }

    // Wait for the threads to finish
    pthread_join(producer_thread, NULL);
    pthread_join(consumer_thread, NULL);

    // Close and unlink semaphores
    sem_close(empty);
    sem_close(full);
    sem_close(mutex);

    sem_unlink("/empty");
    sem_unlink("/full");
    sem_unlink("/mutex");

    return 0;
}
