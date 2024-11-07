#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>
#include <limits.h>

// Global variables to store the results
double average = 0.0;
int min_value = INT_MAX;
int max_value = INT_MIN;

// Global variables for input data
int *numbers;
int num_count;

// Mutex to protect shared global variables (not strictly necessary in this case, but good practice)
pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;

// Thread function to calculate the average
void* calculate_average(void* arg) {
    double sum = 0.0;
    
    for (int i = 0; i < num_count; ++i) {
        sum += numbers[i];
    }

    pthread_mutex_lock(&mutex);
    average = sum / num_count;
    pthread_mutex_unlock(&mutex);

    return NULL;
}

// Thread function to calculate the minimum value
void* calculate_minimum(void* arg) {
    int min = INT_MAX;
    
    for (int i = 0; i < num_count; ++i) {
        if (numbers[i] < min) {
            min = numbers[i];
        }
    }

    pthread_mutex_lock(&mutex);
    min_value = min;
    pthread_mutex_unlock(&mutex);

    return NULL;
}

// Thread function to calculate the maximum value
void* calculate_maximum(void* arg) {
    int max = INT_MIN;
    
    for (int i = 0; i < num_count; ++i) {
        if (numbers[i] > max) {
            max = numbers[i];
        }
    }

    pthread_mutex_lock(&mutex);
    max_value = max;
    pthread_mutex_unlock(&mutex);

    return NULL;
}

int main(int argc, char* argv[]) {
    // Check for correct usage
    if (argc < 2) {
        printf("Usage: %s <list of numbers>\n", argv[0]);
        return 1;
    }

    // Parse input numbers from command line arguments
    num_count = argc - 1;
    numbers = (int*)malloc(num_count * sizeof(int));

    for (int i = 0; i < num_count; ++i) {
        numbers[i] = atoi(argv[i + 1]);  // Convert argument to integer
    }

    // Create threads
    pthread_t avg_thread, min_thread, max_thread;
    
    if (pthread_create(&avg_thread, NULL, calculate_average, NULL) != 0) {
        perror("Error creating average thread");
        return 1;
    }
    if (pthread_create(&min_thread, NULL, calculate_minimum, NULL) != 0) {
        perror("Error creating minimum thread");
        return 1;
    }
    if (pthread_create(&max_thread, NULL, calculate_maximum, NULL) != 0) {
        perror("Error creating maximum thread");
        return 1;
    }

    // Wait for threads to finish
    if (pthread_join(avg_thread, NULL) != 0) {
        perror("Error joining average thread");
        return 1;
    }
    if (pthread_join(min_thread, NULL) != 0) {
        perror("Error joining minimum thread");
        return 1;
    }
    if (pthread_join(max_thread, NULL) != 0) {
        perror("Error joining maximum thread");
        return 1;
    }

    // Output the results
    printf("Average: %.2f\n", average);
    printf("Minimum: %d\n", min_value);
    printf("Maximum: %d\n", max_value);

    // Free dynamically allocated memory
    free(numbers);

    return 0;
}
