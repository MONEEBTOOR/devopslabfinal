#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_JOBS 100
#define MAX_NAME_LEN 100

// Job structure
typedef struct {
    int job_id;             // Job ID
    char job_name[MAX_NAME_LEN]; // Job name
    int priority;           // Job priority (1: High, 2: Medium, 3: Low)
    int execution_time;     // Execution time for the job
} Job;

// Queues
Job highPriorityQueue[MAX_JOBS];
Job mediumPriorityQueue[MAX_JOBS];
Job lowPriorityQueue[MAX_JOBS];

// Queue pointers
int highFront = 0, highRear = 0;
int mediumFront = 0, mediumRear = 0;
int lowFront = 0, lowRear = 0;

// Add job to high priority queue
void addHighPriorityJob(Job j) {
    highPriorityQueue[highRear] = j;
    highRear++;
}

// Add job to medium priority queue
void addMediumPriorityJob(Job j) {
    mediumPriorityQueue[mediumRear] = j;
    mediumRear++;
}

// Add job to low priority queue
void addLowPriorityJob(Job j) {
    lowPriorityQueue[lowRear] = j;
    lowRear++;
}

// Serve job from the high priority queue
void serveHighPriorityJob() {
    if (highFront < highRear) {
        Job j = highPriorityQueue[highFront];
        printf("Serving high priority job: %s (Job ID: %d), Execution Time: %d\n", j.job_name, j.job_id, j.execution_time);
        highFront++;
    } else {
        printf("No high priority jobs to serve.\n");
    }
}

// Serve job from the medium priority queue
void serveMediumPriorityJob() {
    if (mediumFront < mediumRear) {
        Job j = mediumPriorityQueue[mediumFront];
        printf("Serving medium priority job: %s (Job ID: %d), Execution Time: %d\n", j.job_name, j.job_id, j.execution_time);
        mediumFront++;
    } else {
        printf("No medium priority jobs to serve.\n");
    }
}

// Serve job from the low priority queue
void serveLowPriorityJob() {
    if (lowFront < lowRear) {
        Job j = lowPriorityQueue[lowFront];
        printf("Serving low priority job: %s (Job ID: %d), Execution Time: %d\n", j.job_name, j.job_id, j.execution_time);
        lowFront++;
    } else {
        printf("No low priority jobs to serve.\n");
    }
}

// Function to handle job scheduling based on priority
void handleJobScheduling(Job j) {
    if (j.priority == 1) {
        addHighPriorityJob(j);
    } else if (j.priority == 2) {
        addMediumPriorityJob(j);
    } else if (j.priority == 3) {
        addLowPriorityJob(j);
    }
}

// Display the status of the queues
void displayQueues() {
    printf("\nCurrent Queue Status:\n");

    printf("\nHigh Priority Queue:\n");
    for (int i = highFront; i < highRear; i++) {
        printf("Job ID: %d, Job Name: %s, Execution Time: %d\n", highPriorityQueue[i].job_id, highPriorityQueue[i].job_name, highPriorityQueue[i].execution_time);
    }

    printf("\nMedium Priority Queue:\n");
    for (int i = mediumFront; i < mediumRear; i++) {
        printf("Job ID: %d, Job Name: %s, Execution Time: %d\n", mediumPriorityQueue[i].job_id, mediumPriorityQueue[i].job_name, mediumPriorityQueue[i].execution_time);
    }

    printf("\nLow Priority Queue:\n");
    for (int i = lowFront; i < lowRear; i++) {
        printf("Job ID: %d, Job Name: %s, Execution Time: %d\n", lowPriorityQueue[i].job_id, lowPriorityQueue[i].job_name, lowPriorityQueue[i].execution_time);
    }
}

// Main function to simulate the system
int main() {
    int totalJobs, choice;
    Job j;

    // Step 1: Get the number of jobs and their information
    printf("Enter the number of jobs: ");
    scanf("%d", &totalJobs);

    for (int i = 0; i < totalJobs; i++) {
        printf("\nEnter details for job %d\n", i + 1);
        printf("Enter Job ID: ");
        scanf("%d", &j.job_id);
        printf("Enter Job Name: ");
        getchar(); // To consume the newline character left by scanf
        fgets(j.job_name, MAX_NAME_LEN, stdin);
        j.job_name[strcspn(j.job_name, "\n")] = 0;  // Remove newline character from job name
        printf("Enter Execution Time for Job: ");
        scanf("%d", &j.execution_time);
        printf("Enter Job Priority (1: High, 2: Medium, 3: Low): ");
        scanf("%d", &j.priority);

        // Add job to the appropriate priority queue
        handleJobScheduling(j);
    }

    // Step 2: Provide an interface to serve jobs based on priority
    while (1) {
        printf("\nJob Scheduling System\n");
        printf("1. Serve High Priority Job\n");
        printf("2. Serve Medium Priority Job\n");
        printf("3. Serve Low Priority Job\n");
        printf("4. Display Queue Status\n");
        printf("5. Exit\n");

        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1: // Serve high priority job
                serveHighPriorityJob();
                break;

            case 2: // Serve medium priority job
                serveMediumPriorityJob();
                break;

            case 3: // Serve low priority job
                serveLowPriorityJob();
                break;

            case 4: // Display queue status
                displayQueues();
                break;

            case 5: // Exit
                printf("Exiting program.\n");
                return 0;

            default:
                printf("Invalid choice! Please try again.\n");
        }
    }

    return 0;
}
