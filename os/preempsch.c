#include <stdio.h>
#include <limits.h>

struct Process {
    int pid;
    int burstTime;
    int arrivalTime;
    int waitingTime;
    int turnAroundTime;
    int completionTime;
    int remainingTime;
    int priority;
};


void findWaitingTimeAndTurnaroundTime(struct Process processes[], int n, int priorityType) {
    int completed = 0, currentTime = 0, selected = -1, priorityCompare = (priorityType == 1) ? INT_MAX : INT_MIN;
    int finished[n];

    for (int i = 0; i < n; i++) {
        finished[i] = 0;
        processes[i].remainingTime = processes[i].burstTime;
    }

    printf("\nGantt Chart:\n");
    printf("0");

    while (completed != n) {
        selected = -1;
        priorityCompare = (priorityType == 1) ? INT_MAX : INT_MIN;

        for (int i = 0; i < n; i++) {
            if (processes[i].arrivalTime <= currentTime && !finished[i]) {
                if ((priorityType == 1 && processes[i].priority < priorityCompare) ||
                    (priorityType == 2 && processes[i].priority > priorityCompare)) {
                    priorityCompare = processes[i].priority;
                    selected = i;
                }
            }
        }

        if (selected == -1) {
            currentTime++;
            continue;
        }

        currentTime++;
        processes[selected].remainingTime--;

        if (processes[selected].remainingTime == 0) {
            processes[selected].completionTime = currentTime;
            processes[selected].turnAroundTime = processes[selected].completionTime - processes[selected].arrivalTime;
            processes[selected].waitingTime = processes[selected].turnAroundTime - processes[selected].burstTime;
            finished[selected] = 1;
            completed++;

            printf(" -- P%d -- %d", processes[selected].pid, currentTime);
        }
    }
    printf("\n");
}


void findAvgTime(struct Process processes[], int n, int priorityType) {
    int totalWaitingTime = 0, totalTurnAroundTime = 0;

    findWaitingTimeAndTurnaroundTime(processes, n, priorityType);

    printf("\nProcesses  Arrival Time  Burst Time  Priority  Waiting Time  Turn Around Time  Completion Time\n");

    for (int i = 0; i < n; i++) {
        totalWaitingTime += processes[i].waitingTime;
        totalTurnAroundTime += processes[i].turnAroundTime;

        printf("  %d\t\t%d\t\t%d\t\t%d\t\t%d\t\t%d\t\t%d\n",
            processes[i].pid,
            processes[i].arrivalTime,
            processes[i].burstTime,
            processes[i].priority,
            processes[i].waitingTime,
            processes[i].turnAroundTime,
            processes[i].completionTime);
    }

    printf("\nAverage Waiting Time = %.2f", (float)totalWaitingTime / n);
    printf("\nAverage Turn Around Time = %.2f", (float)totalTurnAroundTime / n);
}

int main() {
    int n, priorityType;

    printf("Enter the number of processes: ");
    scanf("%d", &n);

    struct Process processes[n];

    for (int i = 0; i < n; i++) {
        processes[i].pid = i + 1;
        printf("Enter arrival time for process %d: ", i + 1);
        scanf("%d", &processes[i].arrivalTime);
        printf("Enter burst time for process %d: ", i + 1);
        scanf("%d", &processes[i].burstTime);
        printf("Enter priority for process %d: ", i + 1);
        scanf("%d", &processes[i].priority);
    }

    printf("Enter 1 if lower number is higher priority, or 2 if higher number is higher priority: ");
    scanf("%d", &priorityType);

    findAvgTime(processes, n, priorityType);
    return 0;
}
