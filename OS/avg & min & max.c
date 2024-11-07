#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

// Function to calculate the average
double calculate_average(int *numbers, int num_count) {
    double sum = 0.0;
    for (int i = 0; i < num_count; i++) {
        sum += numbers[i];
    }
    return sum / num_count;
}

// Function to calculate the minimum value
int calculate_minimum(int *numbers, int num_count) {
    int min = INT_MAX;
    for (int i = 0; i < num_count; i++) {
        if (numbers[i] < min) {
            min = numbers[i];
        }
    }
    return min;
}

// Function to calculate the maximum value
int calculate_maximum(int *numbers, int num_count) {
    int max = INT_MIN;
    for (int i = 0; i < num_count; i++) {
        if (numbers[i] > max) {
            max = numbers[i];
        }
    }
    return max;
}

int main(int argc, char *argv[]) {
    // Check if any numbers are passed via command line arguments
    if (argc < 2) {
        printf("Usage: %s <list of numbers>\n", argv[0]);
        return 1;
    }

    // Parse command line arguments into an array of integers
    int num_count = argc - 1;
    int *numbers = (int *)malloc(num_count * sizeof(int));

    for (int i = 0; i < num_count; i++) {
        numbers[i] = atoi(argv[i + 1]);  // Convert string to integer
    }

    // Calculate average, minimum, and maximum
    double avg = calculate_average(numbers, num_count);
    int min = calculate_minimum(numbers, num_count);
    int max = calculate_maximum(numbers, num_count);

    // Output the results
    printf("Average: %.2f\n", avg);
    printf("Minimum: %d\n", min);
    printf("Maximum: %d\n", max);

    // Free dynamically allocated memory
    free(numbers);

    return 0;
}
