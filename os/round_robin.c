#include <stdio.h>

struct Process {
    int id;
    int burstTime;
    int remainingTime;
    int waitingTime;
    int turnaroundTime;
    int arrivalTime;
    int completionTime;
};

void findWaitingTime(struct Process proc[], int n, int quantum) {
    int t = 0;
    int completed = 0;
    while (completed < n) {
        int done = 1;
        for (int i = 0; i < n; i++) {
            if (proc[i].remainingTime > 0 && proc[i].arrivalTime <= t) {
                done = 0;
                if (proc[i].remainingTime > quantum) {
                    t += quantum;
                    proc[i].remainingTime -= quantum;
                } else {
                    t += proc[i].remainingTime;
                    proc[i].remainingTime = 0;
                    proc[i].waitingTime = t - proc[i].burstTime - proc[i].arrivalTime;
                    proc[i].turnaroundTime = t - proc[i].arrivalTime;
                    proc[i].completionTime = t;
                    completed++;
                }
            }
        }
        if (done) {
            t++;
        }
    }
}

void findAvgTime(struct Process proc[], int n, int quantum) {
    findWaitingTime(proc, n, quantum);

    float totalWaitingTime = 0, totalTurnAroundTime = 0;

    printf("\nProcesses  Arrival Time  Burst Time  Waiting Time  Turnaround Time  Completion Time\n");
    for (int i = 0; i < n; i++) {
        totalWaitingTime += proc[i].waitingTime;
        totalTurnAroundTime += proc[i].turnaroundTime;

        printf("  %d\t\t%d\t\t%d\t\t%d\t\t%d\t\t%d\n",
            proc[i].id,
            proc[i].arrivalTime,
            proc[i].burstTime,
            proc[i].waitingTime,
            proc[i].turnaroundTime,
            proc[i].completionTime);
    }

    printf("\nAverage Waiting Time: %.2f\n", totalWaitingTime / n);
    printf("Average Turnaround Time: %.2f\n", totalTurnAroundTime / n);
}

void printGanttChart(struct Process proc[], int n, int quantum) {
    int t = 0;


    for (int i = 0; i < n; i++) {
        proc[i].remainingTime = proc[i].burstTime;
    }

    printf("\nGantt Chart:\n");
    printf("Time: %d ", t);

    while (1) {
        int done = 1;
        for (int i = 0; i < n; i++) {
            if (proc[i].remainingTime > 0 && proc[i].arrivalTime <= t) {
                done = 0;
                printf("| P%d ", proc[i].id);
                if (proc[i].remainingTime > quantum) {
                    t += quantum;
                    proc[i].remainingTime -= quantum;
                } else {
                    t += proc[i].remainingTime;
                    proc[i].remainingTime = 0;
                    proc[i].completionTime = t;
                }
                printf("%d ", t);
            }
        }
        if (done) break;
    }
    printf("|\n");
}

int main() {
    int n, quantum;
    printf("Enter number of processes: ");
    scanf("%d", &n);

    struct Process proc[n];
    for (int i = 0; i < n; i++) {
        proc[i].id = i + 1;
        printf("Enter Arrival Time for Process %d: ", proc[i].id);
        scanf("%d", &proc[i].arrivalTime);
        printf("Enter Burst Time for Process %d: ", proc[i].id);
        scanf("%d", &proc[i].burstTime);
        proc[i].remainingTime = proc[i].burstTime;
    }

    printf("Enter Time Quantum: ");
    scanf("%d", &quantum);

    findAvgTime(proc, n, quantum);
    printGanttChart(proc, n, quantum);

    return 0;
}
