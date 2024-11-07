#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_PATIENTS 100
#define MAX_NAME_LEN 100

// Patient structure
typedef struct {
    int id;                  // Patient ID
    char name[MAX_NAME_LEN]; // Patient name
    int visit_count;         // Number of visits
    int priority;            // Patient priority
} Patient;

// Queues
Patient emergencyQueue[MAX_PATIENTS];
Patient normalQueue[MAX_PATIENTS];
Patient followUpQueue[MAX_PATIENTS];

// Queue pointers
int emergencyFront = 0, emergencyRear = 0;
int normalFront = 0, normalRear = 0;
int followUpFront = 0, followUpRear = 0;

// Add patient to emergency queue
void addEmergencyPatient(Patient p) {
    emergencyQueue[emergencyRear] = p;
    emergencyRear++;
}

// Add patient to normal queue
void addNormalPatient(Patient p) {
    normalQueue[normalRear] = p;
    normalRear++;
}

// Add patient to follow-up queue
void addFollowUpPatient(Patient p) {
    followUpQueue[followUpRear] = p;
    followUpRear++;
}

// Serve patient from the emergency queue
void serveEmergencyPatient() {
    if (emergencyFront < emergencyRear) {
        Patient p = emergencyQueue[emergencyFront];
        printf("Serving emergency patient: %s (ID: %d)\n", p.name, p.id);
        emergencyFront++;
    } else {
        printf("No emergency patients to serve.\n");
    }
}

// Serve patient from the normal queue
void serveNormalPatient() {
    if (normalFront < normalRear) {
        Patient p = normalQueue[normalFront];
        printf("Serving normal patient: %s (ID: %d)\n", p.name, p.id);
        normalFront++;
    } else {
        printf("No normal patients to serve.\n");
    }
}

// Serve patient from the follow-up queue
void serveFollowUpPatient() {
    if (followUpFront < followUpRear) {
        Patient p = followUpQueue[followUpFront];
        printf("Serving follow-up patient: %s (ID: %d)\n", p.name, p.id);
        followUpFront++;
    } else {
        printf("No follow-up patients to serve.\n");
    }
}

// Function to handle patient check-up
void handlePatientCheckup(Patient p) {
    if (p.priority == 1) {
        addEmergencyPatient(p);
    } else if (p.visit_count == 1) {
        addNormalPatient(p);
    } else {
        addFollowUpPatient(p);
    }
}

// Display the status of the queues
void displayQueues() {
    printf("\nCurrent Queue Status:\n");
    
    printf("\nEmergency Queue:\n");
    for (int i = emergencyFront; i < emergencyRear; i++) {
        printf("Patient ID: %d, Name: %s\n", emergencyQueue[i].id, emergencyQueue[i].name);
    }
    
    printf("\nNormal Queue:\n");
    for (int i = normalFront; i < normalRear; i++) {
        printf("Patient ID: %d, Name: %s\n", normalQueue[i].id, normalQueue[i].name);
    }
    
    printf("\nFollow-up Queue:\n");
    for (int i = followUpFront; i < followUpRear; i++) {
        printf("Patient ID: %d, Name: %s\n", followUpQueue[i].id, followUpQueue[i].name);
    }
}

// Main function to simulate the system
int main() {
    int choice;
    Patient p;

    while (1) {
        printf("\nPatient Management System\n");
        printf("1. Add Emergency Patient\n");
        printf("2. Add Normal Patient\n");
        printf("3. Add Follow-up Patient\n");
        printf("4. Serve Emergency Patient\n");
        printf("5. Serve Normal Patient\n");
        printf("6. Serve Follow-up Patient\n");
        printf("7. Display Queue Status\n");
        printf("8. Exit\n");

        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1: // Add emergency patient
                printf("Enter Patient ID: ");
                scanf("%d", &p.id);
                printf("Enter Patient Name: ");
                getchar(); // To consume the newline character left by scanf
                fgets(p.name, MAX_NAME_LEN, stdin);
                p.name[strcspn(p.name, "\n")] = 0;  // Remove newline character from name
                p.visit_count = 1;  // Emergency case always counts as first visit
                p.priority = 1;  // Highest priority for emergency
                handlePatientCheckup(p);
                break;
                
            case 2: // Add normal patient
                printf("Enter Patient ID: ");
                scanf("%d", &p.id);
                printf("Enter Patient Name: ");
                getchar(); // To consume the newline character left by scanf
                fgets(p.name, MAX_NAME_LEN, stdin);
                p.name[strcspn(p.name, "\n")] = 0;  // Remove newline character from name
                p.visit_count = 1;  // First visit
                p.priority = 2;  // Normal priority for regular patients
                handlePatientCheckup(p);
                break;
                
            case 3: // Add follow-up patient
                printf("Enter Patient ID: ");
                scanf("%d", &p.id);
                printf("Enter Patient Name: ");
                getchar(); // To consume the newline character left by scanf
                fgets(p.name, MAX_NAME_LEN, stdin);
                p.name[strcspn(p.name, "\n")] = 0;  // Remove newline character from name
                printf("Enter the number of visits: ");
                scanf("%d", &p.visit_count);
                p.priority = 3;  // Lower priority for follow-up patients
                handlePatientCheckup(p);
                break;
                
            case 4: // Serve emergency patient
                serveEmergencyPatient();
                break;
                
            case 5: // Serve normal patient
                serveNormalPatient();
                break;
                
            case 6: // Serve follow-up patient
                serveFollowUpPatient();
                break;
                
            case 7: // Display queue status
                displayQueues();
                break;
                
            case 8: // Exit
                printf("Exiting program.\n");
                return 0;
                
            default:
                printf("Invalid choice! Please try again.\n");
        }
    }

    return 0;
}
