#include <stdio.h>
#include <limits.h>

struct Process {
    int pid;
    int burstTime;
    int waitingTime;
    int turnAroundTime;
    int completionTime;
    int isCompleted;
};

void calculateWaitingAndTurnaroundTimes(struct Process processes[], int n) {
    int completedProcesses = 0;
    int currentTime = 0;

    printf("\nGantt Chart:\n");
    printf("0");

    while (completedProcesses < n) {
        int index = -1;
        int minBurst = INT_MAX;


        for (int i = 0; i < n; i++) {
            if (processes[i].isCompleted == 0) {
                if (processes[i].burstTime < minBurst) {
                    minBurst = processes[i].burstTime;
                    index = i;
                }
            }
        }

        if (index != -1) {
            currentTime += processes[index].burstTime;
            processes[index].completionTime = currentTime;
            processes[index].turnAroundTime = processes[index].completionTime;
            processes[index].waitingTime = processes[index].turnAroundTime - processes[index].burstTime;
            processes[index].isCompleted = 1;
            completedProcesses++;
            printf(" -- P%d -- %d", processes[index].pid, currentTime);
            currentTime++;
        }
    }
    printf("\n");
}

void findAvgTime(struct Process processes[], int n) {
    int totalWaitingTime = 0, totalTurnAroundTime = 0;

    calculateWaitingAndTurnaroundTimes(processes, n);

    printf("\nProcesses  Burst Time  Waiting Time  Turn Around Time  Completion Time\n");

    for (int i = 0; i < n; i++) {
        totalWaitingTime += processes[i].waitingTime;
        totalTurnAroundTime += processes[i].turnAroundTime;

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
        processes[i].isCompleted = 0;
    }

    findAvgTime(processes, n);
    return 0;
}
