#include <stdio.h>
#include <stdlib.h>

int compare(const void *a, const void *b) {
    return (*(int *)a - *(int *)b);
}

void FCFS(int requests[], int n, int head) {
    int seek_count = 0;
    printf("FCFS Disk Scheduling:\n");
    for (int i = 0; i < n; i++) {
        int distance = abs(requests[i] - head);
        seek_count += distance;
        printf("Move from %d to %d with Seek %d\n", head, requests[i], distance);
        head = requests[i];
    }
    printf("Total Seek Operations: %d\n\n", seek_count);
}

void SSTF(int requests[], int n, int head) {
    int seek_count = 0, completed = 0;
    int *visited = (int *)calloc(n, sizeof(int));
    printf("SSTF Disk Scheduling:\n");

    while (completed < n) {
        int min_distance = 1e5, index = -1;
        for (int i = 0; i < n; i++) {
            if (!visited[i]) {
                int distance = abs(requests[i] - head);
                if (distance < min_distance) {
                    min_distance = distance;
                    index = i;
                }
            }
        }
        visited[index] = 1;
        seek_count += min_distance;
        printf("Move from %d to %d with Seek %d\n", head, requests[index], min_distance);
        head = requests[index];
        completed++;
    }
    free(visited);
    printf("Total Seek Operations: %d\n\n", seek_count);
}

void SCAN(int requests[], int n, int head, int disk_size, int direction) {
    int seek_count = 0, max_pos = disk_size - 1;
    printf("SCAN Disk Scheduling:\n");

    requests[n] = head;
    n++;
    qsort(requests, n, sizeof(int), compare);

    int index;
    for (index = 0; index < n; index++) {
        if (requests[index] == head) break;
    }

    if (direction == 1) {  // Moving towards high end
        for (int i = index; i < n; i++) {
            printf("Move from %d to %d with Seek %d\n", head, requests[i], abs(requests[i] - head));
            seek_count += abs(requests[i] - head);
            head = requests[i];
        }
        if (head != max_pos) {
            printf("Move from %d to %d with Seek %d\n", head, max_pos, abs(max_pos - head));
            seek_count += abs(max_pos - head);
            head = max_pos;
        }
        for (int i = index - 1; i >= 0; i--) {
            printf("Move from %d to %d with Seek %d\n", head, requests[i], abs(requests[i] - head));
            seek_count += abs(requests[i] - head);
            head = requests[i];
        }
    } else {  // Moving towards low end
        for (int i = index; i >= 0; i--) {
            printf("Move from %d to %d with Seek %d\n", head, requests[i], abs(requests[i] - head));
            seek_count += abs(requests[i] - head);
            head = requests[i];
        }
        if (head != 0) {
            printf("Move from %d to 0 with Seek %d\n", head, head);
            seek_count += head;
            head = 0;
        }
        for (int i = index + 1; i < n; i++) {
            printf("Move from %d to %d with Seek %d\n", head, requests[i], abs(requests[i] - head));
            seek_count += abs(requests[i] - head);
            head = requests[i];
        }
    }
    printf("Total Seek Operations: %d\n\n", seek_count);
}

void CSCAN(int requests[], int n, int head, int disk_size) {
    int seek_count = 0, max_pos = disk_size - 1;
    printf("C-SCAN Disk Scheduling:\n");

    requests[n] = head;
    n++;
    qsort(requests, n, sizeof(int), compare);

    int index;
    for (index = 0; index < n; index++) {
        if (requests[index] == head) break;
    }

    for (int i = index; i < n; i++) {
        printf("Move from %d to %d with Seek %d\n", head, requests[i], abs(requests[i] - head));
        seek_count += abs(requests[i] - head);
        head = requests[i];
    }
    if (head != max_pos) {
        printf("Move from %d to %d with Seek %d\n", head, max_pos, abs(max_pos - head));
        seek_count += abs(max_pos - head);
        head = max_pos;
    }
    printf("Move from %d to 0 with Seek %d\n", head, head);
    seek_count += head;
    head = 0;
    for (int i = 0; i < index; i++) {
        printf("Move from %d to %d with Seek %d\n", head, requests[i], abs(requests[i] - head));
        seek_count += abs(requests[i] - head);
        head = requests[i];
    }
    printf("Total Seek Operations: %d\n\n", seek_count);
}

void LOOK(int requests[], int n, int head, int direction) {
    int seek_count = 0;
    printf("LOOK Disk Scheduling:\n");

    requests[n] = head;
    n++;
    qsort(requests, n, sizeof(int), compare);

    int index;
    for (index = 0; index < n; index++) {
        if (requests[index] == head) break;
    }

    if (direction == 1) {  // Move towards high end
        for (int i = index; i < n; i++) {
            printf("Move from %d to %d with Seek %d\n", head, requests[i], abs(requests[i] - head));
            seek_count += abs(requests[i] - head);
            head = requests[i];
        }
        for (int i = index - 1; i >= 0; i--) {
            printf("Move from %d to %d with Seek %d\n", head, requests[i], abs(requests[i] - head));
            seek_count += abs(requests[i] - head);
            head = requests[i];
        }
    } else {  // Move towards low end
        for (int i = index; i >= 0; i--) {
            printf("Move from %d to %d with Seek %d\n", head, requests[i], abs(requests[i] - head));
            seek_count += abs(requests[i] - head);
            head = requests[i];
        }
        for (int i = index + 1; i < n; i++) {
            printf("Move from %d to %d with Seek %d\n", head, requests[i], abs(requests[i] - head));
            seek_count += abs(requests[i] - head);
            head = requests[i];
        }
    }
    printf("Total Seek Operations: %d\n\n", seek_count);
}

int main() {
    int n, disk_size, head, direction;

    printf("Enter the number of requests: ");
    scanf("%d", &n);

    int requests[n + 1];
    printf("Enter the requests:\n");
    for (int i = 0; i < n; i++) {
        scanf("%d", &requests[i]);
    }

    printf("Enter the initial head position: ");
    scanf("%d", &head);

    printf("Enter the disk size: ");
    scanf("%d", &disk_size);

    printf("Enter the direction (1 for high, 0 for low): ");
    scanf("%d", &direction);

    FCFS(requests, n, head);
    SSTF(requests, n, head);
    SCAN(requests, n, head, disk_size, direction);
    CSCAN(requests, n, head, disk_size);
    LOOK(requests, n, head, direction);

    return 0;
}
