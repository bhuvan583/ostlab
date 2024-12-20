#include <stdio.h>
#include <limits.h>

struct Process {
    int pid;
    int burstTime;
    int remainingTime;
    int waitingTime;
    int turnAroundTime;
    int completionTime;
};

void findAvgTime(struct Process processes[], int n) {
    int completed = 0, currentTime = 0, minRemainingTime;
    int totalWaitingTime = 0, totalTurnAroundTime = 0;
    int shortest = 0, finishTime;
    int isComplete = 0;


    for (int i = 0; i < n; i++) {
        processes[i].remainingTime = processes[i].burstTime;
    }

    printf("\nGantt Chart:\n");
    printf("0");

    while (completed != n) {
        minRemainingTime = INT_MAX;
        isComplete = 0;


        for (int i = 0; i < n; i++) {
            if (processes[i].remainingTime > 0 &&
                processes[i].remainingTime < minRemainingTime) {

                minRemainingTime = processes[i].remainingTime;
                shortest = i;
                isComplete = 1;
            }
        }

        if (isComplete == 0) {
            currentTime++;
            continue;
        }

        processes[shortest].remainingTime--;
        currentTime++;

        if (processes[shortest].remainingTime == 0) {
            completed++;
            finishTime = currentTime;
            processes[shortest].completionTime = finishTime;
            processes[shortest].turnAroundTime = finishTime;
            processes[shortest].waitingTime = processes[shortest].turnAroundTime - processes[shortest].burstTime;
            totalWaitingTime += processes[shortest].waitingTime;
            totalTurnAroundTime += processes[shortest].turnAroundTime;

            printf(" -- P%d -- %d", processes[shortest].pid, currentTime);
        }
    }
    printf("\n");

    printf("\nProcesses  Burst Time  Waiting Time  Turn Around Time  Completion Time\n");
    for (int i = 0; i < n; i++) {
        printf("  %d\t\t%d\t\t%d\t\t%d\t\t%d\n",
            processes[i].pid,
            processes[i].burstTime,
            processes[i].waitingTime,
            processes[i].turnAroundTime,
            processes[i].completionTime);
    }

    printf("\nAverage Waiting Time = %.2f", (float)totalWaitingTime / n);
    printf("\nAverage Turn Around Time = %.2f", (float)totalTurnAroundTime / n);
}

int main() {
    int n;

    printf("Enter the number of processes: ");
    scanf("%d", &n);

    struct Process processes[n];

    for (int i = 0; i < n; i++) {
        processes[i].pid = i + 1;
        printf("Enter burst time for process %d: ", i + 1);
        scanf("%d", &processes[i].burstTime);
    }

    findAvgTime(processes, n);
    return 0;
}
