#include <stdio.h>

// Function to calculate factorial
long long calculate_factorial(int n) {
    long long fact = 1;
    for (int i = 1; i <= n; ++i) {
        fact *= i;
    }
    return fact;
}

int main() {
    int n;

    // Ask user for input
    printf("Enter a natural number: ");
    scanf("%d", &n);

    // Check for valid input
    if (n < 0) {
        printf("Factorial is not defined for negative numbers.\n");
        return 1;
    }

    // Calculate factorial
    long long result = calculate_factorial(n);

    // Output the result
    printf("Factorial of %d is %lld\n", n, result);

    return 0;
}
