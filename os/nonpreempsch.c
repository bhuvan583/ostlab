#include <stdio.h>

struct Process {
    int pid;
    int burstTime;
    int arrivalTime;
    int priority;
    int waitingTime;
    int turnAroundTime;
    int completionTime;
};


void sortRemainingByPriority(struct Process processes[], int start, int n, int priorityType) {
    struct Process temp;
    for (int i = start; i < n - 1; i++) {
        for (int j = i + 1; j < n; j++) {

            if ((priorityType == 1 && processes[j].priority < processes[i].priority) ||

                (priorityType == 2 && processes[j].priority > processes[i].priority)) {
                temp = processes[i];
                processes[i] = processes[j];
                processes[j] = temp;
            }
        }
    }
}

void findWaitingAndTurnAroundTimes(struct Process processes[], int n, int priorityType) {
    int currentTime = 0, leastArrivalIndex = 0;
    int ganttChart[100], ganttIndex = 0;

    for (int i = 1; i < n; i++) {
        if (processes[i].arrivalTime < processes[leastArrivalIndex].arrivalTime) {
            leastArrivalIndex = i;
        }
    }

    struct Process firstProcess = processes[leastArrivalIndex];
    if (currentTime < firstProcess.arrivalTime) {
        currentTime = firstProcess.arrivalTime;
    }

    ganttChart[ganttIndex++] = firstProcess.pid;
    currentTime += firstProcess.burstTime;
    firstProcess.completionTime = currentTime;
    firstProcess.turnAroundTime = firstProcess.completionTime - firstProcess.arrivalTime;
    firstProcess.waitingTime = firstProcess.turnAroundTime - firstProcess.burstTime;

    processes[leastArrivalIndex] = processes[0];
    processes[0] = firstProcess;
    sortRemainingByPriority(processes, 1, n, priorityType);

    for (int i = 1; i < n; i++) {
        if (currentTime < processes[i].arrivalTime) {
            currentTime = processes[i].arrivalTime;
        }

        ganttChart[ganttIndex++] = processes[i].pid;
        currentTime += processes[i].burstTime;
        processes[i].completionTime = currentTime;
        processes[i].turnAroundTime = processes[i].completionTime - processes[i].arrivalTime;
        processes[i].waitingTime = processes[i].turnAroundTime - processes[i].burstTime;
    }

    printf("\nGantt Chart:\n|");
    for (int i = 0; i < ganttIndex; i++) {
        printf(" P%d |", ganttChart[i]);
    }
    printf("\nTime: 0 ");
    currentTime = 0;
    for (int i = 0; i < ganttIndex; i++) {
        currentTime += processes[i].burstTime;
        printf("%d ", currentTime);
    }
    printf("\n");
}

void findAvgTime(struct Process processes[], int n, int priorityType) {
    int totalWaitingTime = 0, totalTurnAroundTime = 0;

    findWaitingAndTurnAroundTimes(processes, n, priorityType);

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
        processes[i].waitingTime = 0;
        processes[i].turnAroundTime = 0;
        processes[i].completionTime = 0;
    }

    printf("Choose priority type (1 for lower number higher priority, 2 for higher number higher priority): ");
    scanf("%d", &priorityType);

    findAvgTime(processes, n, priorityType);
    return 0;
}
