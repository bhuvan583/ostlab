#include <stdio.h>
#include <stdbool.h>

#define MAX 10
#define RESOURCES 3

int allocation[MAX][RESOURCES], max[MAX][RESOURCES], need[MAX][RESOURCES];
int available[RESOURCES], safeSequence[MAX], processCount;

bool isSafe() {
    int work[RESOURCES];
    bool finish[MAX] = {false};
    int count = 0;

    // Initialize work array
    for (int i = 0; i < RESOURCES; i++) {
        work[i] = available[i];
    }

    while (count < processCount) {
        bool found = false;
        for (int p = 0; p < processCount; p++) {
            if (!finish[p]) {
                // Check if the process can be finished
                bool canFinish = true;
                for (int j = 0; j < RESOURCES; j++) {
                    if (need[p][j] > work[j]) {
                        canFinish = false;
                        break;
                    }
                }
                // If yes, simulate the allocation
                if (canFinish) {
                    for (int j = 0; j < RESOURCES; j++) {
                        work[j] += allocation[p][j];
                    }
                    safeSequence[count++] = p;
                    finish[p] = true;
                    found = true;
                }
            }
        }
        if (!found) {
            break;
        }
    }

    // If all processes finished
    return (count == processCount);
}

void calculateNeed() {
    printf("\nNeed Matrix:\n");
    for (int i = 0; i < processCount; i++) {
        for (int j = 0; j < RESOURCES; j++) {
            need[i][j] = max[i][j] - allocation[i][j];
            printf("%d ", need[i][j]);
        }
        printf("\n");
    }
}

int main() {
    printf("Enter number of processes: ");
    scanf("%d", &processCount);

    printf("Enter the Maximum Resource Allocation Matrix:\n");
    for (int i = 0; i < processCount; i++) {
        for (int j = 0; j < RESOURCES; j++) {
            scanf("%d", &max[i][j]);
        }
    }

    printf("Enter the Allocation Matrix:\n");
    for (int i = 0; i < processCount; i++) {
        for (int j = 0; j < RESOURCES; j++) {
            scanf("%d", &allocation[i][j]);
        }
    }

    printf("Enter the Available Resources:\n");
    for (int i = 0; i < RESOURCES; i++) {
        scanf("%d", &available[i]);
    }

    // Calculate and display Need Matrix
    calculateNeed();

    if (isSafe()) {
        printf("\nSystem is in a safe state.\nSafe sequence is: ");
        for (int i = 0; i < processCount; i++) {
            printf("%d ", safeSequence[i]);
        }
        printf("\n");
    } else {
        printf("\nSystem is not in a safe state.\n");
    }

    return 0;
}
