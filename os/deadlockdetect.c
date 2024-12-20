#include <stdio.h>
#include <stdbool.h>

#define MAX_PROCESSES 10
#define MAX_RESOURCES 10

int main() {
    int allocation[MAX_PROCESSES][MAX_RESOURCES], max[MAX_PROCESSES][MAX_RESOURCES], request[MAX_PROCESSES][MAX_RESOURCES];
    int available[MAX_RESOURCES], work[MAX_RESOURCES], finish[MAX_PROCESSES];
    int n, m; // n = number of processes, m = number of resources

    // Input: Number of processes and resources
    printf("Enter number of processes: ");
    scanf("%d", &n);

    printf("Enter number of resource types: ");
    scanf("%d", &m);

    // Input: Allocation matrix
    printf("Enter the Allocation matrix:\n");
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            scanf("%d", &allocation[i][j]);
        }
    }

    // Input: Max matrix (maximum resources required)
    printf("Enter the Max matrix:\n");
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            scanf("%d", &max[i][j]);
        }
    }

    // Input: Available resources
    printf("Enter the Available resources:\n");
    for (int i = 0; i < m; i++) {
        scanf("%d", &available[i]);
    }

    // Step 1: Calculate the Request matrix = Max - Allocation
    printf("\nRequest Matrix (Max - Allocation):\n");
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            request[i][j] = max[i][j] - allocation[i][j];
            printf("%d ", request[i][j]);
        }
        printf("\n");
    }

    // Step 2: Initialize Work = Available and Finish array
    for (int i = 0; i < m; i++) {
        work[i] = available[i];
    }

    for (int i = 0; i < n; i++) {
        bool allocationIsZero = true;
        for (int j = 0; j < m; j++) {
            if (allocation[i][j] != 0) {
                allocationIsZero = false;
                break;
            }
        }
        finish[i] = allocationIsZero ? true : false;
    }

    // Step 3: Find a process i such that Finish[i] == false and Request[i] <= Work
    bool deadlockDetected = false;
    while (true) {
        bool foundProcess = false;

        for (int i = 0; i < n; i++) {
            if (!finish[i]) {
                bool canProceed = true;

                for (int j = 0; j < m; j++) {
                    if (request[i][j] > work[j]) {
                        canProceed = false;
                        break;
                    }
                }

                if (canProceed) {
                    // Work = Work + Allocation[i], Finish[i] = true
                    for (int j = 0; j < m; j++) {
                        work[j] += allocation[i][j];
                    }
                    finish[i] = true;
                    foundProcess = true;
                }
            }
        }

        // If no process was found in this pass, exit the loop
        if (!foundProcess) {
            break;
        }
    }

    // Step 4: Check if any process is still unfinished
    printf("\nDeadlock Detection:\n");
    for (int i = 0; i < n; i++) {
        if (!finish[i]) {
            printf("System is in deadlock state.\n");
            printf("Processes in deadlock: ");
            for (int j = 0; j < n; j++) {
                if (!finish[j]) {
                    printf("P%d ", j);
                }
            }
            printf("\n");
            deadlockDetected = true;
            break;
        }
    }

    if (!deadlockDetected) {
        printf("No deadlock detected.\n");
    }

    return 0;
}
