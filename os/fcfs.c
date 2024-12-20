#include <stdio.h>

struct Process {
    int pid;
    int burstTime;
    int waitingTime;
    int turnAroundTime;
    int completionTime;
};

void findWaitingTime(struct Process processes[], int n) {
    int currentTime = 0;

    printf("\nGantt Chart:\n");
    printf("0");

    for (int i = 0; i < n; i++) {
        processes[i].completionTime = currentTime + processes[i].burstTime;
        processes[i].turnAroundTime = processes[i].completionTime;
        processes[i].waitingTime = processes[i].turnAroundTime - processes[i].burstTime;

        currentTime = processes[i].completionTime;

        printf(" -- P%d -- %d", processes[i].pid, currentTime);
    }
    printf("\n");
}

void findAvgTime(struct Process processes[], int n) {
    int totalWaitingTime = 0, totalTurnAroundTime = 0;

    findWaitingTime(processes, n);

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
    }

    findAvgTime(processes, n);
    return 0;
}
