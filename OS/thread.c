#include <stdio.h>
#include <pthread.h>
#include <unistd.h>  // For sleep function

// Define the thread runner function
void* thread_runner(void* arg) {
    printf("Thread started.\n");
    sleep(2);  // Simulate some work with sleep
    printf("Thread finished.\n");
    return NULL;
}

int main() {
    pthread_t thread;  // Thread identifier

    // Create the thread
    if (pthread_create(&thread, NULL, thread_runner, NULL) != 0) {
        perror("Failed to create thread");
        return 1;
    }

    // Wait for the thread to finish (join)
    printf("Main program waiting for the thread to finish...\n");
    if (pthread_join(thread, NULL) != 0) {
        perror("Failed to join thread");
        return 1;
    }

    printf("Main program has completed waiting.\n");
    
    return 0;
}
