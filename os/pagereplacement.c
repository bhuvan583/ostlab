#include <stdio.h>
#include <stdlib.h>

// Function for FIFO Page Replacement
void fifo(int pages[], int n, int frames) {
    int frame[frames];
    for (int i = 0; i < frames; i++)
        frame[i] = -1;

    int index = 0, pageFaults = 0;

    printf("\nFIFO Page Replacement:\n");
    for (int i = 0; i < n; i++) {
        int found = 0;
        for (int j = 0; j < frames; j++) {
            if (frame[j] == pages[i]) {
                found = 1;
                break;
            }
        }

        if (!found) {
            frame[index] = pages[i];
            index = (index + 1) % frames;
            pageFaults++;
        }

        printf("Page %d: ", pages[i]);
        for (int j = 0; j < frames; j++) {
            if (frame[j] != -1)
                printf("%d ", frame[j]);
            else
                printf("- ");
        }
        printf("\n");
    }
    printf("Total Page Faults (FIFO): %d\n", pageFaults);
}

// Function for LRU Page Replacement
void lru(int pages[], int n, int frames) {
    int frame[frames], counter[frames];
    for (int i = 0; i < frames; i++) {
        frame[i] = -1;
        counter[i] = 0;
    }

    int pageFaults = 0, time = 0;

    printf("\nLRU Page Replacement:\n");
    for (int i = 0; i < n; i++) {
        int found = 0;
        for (int j = 0; j < frames; j++) {
            if (frame[j] == pages[i]) {
                found = 1;
                counter[j] = ++time;
                break;
            }
        }

        if (!found) {
            int lruIndex = 0;
            for (int j = 1; j < frames; j++) {
                if (counter[j] < counter[lruIndex])
                    lruIndex = j;
            }
            frame[lruIndex] = pages[i];
            counter[lruIndex] = ++time;
            pageFaults++;
        }

        printf("Page %d: ", pages[i]);
        for (int j = 0; j < frames; j++) {
            if (frame[j] != -1)
                printf("%d ", frame[j]);
            else
                printf("- ");
        }
        printf("\n");
    }
    printf("Total Page Faults (LRU): %d\n", pageFaults);
}

// Helper function to predict optimal page replacement
int predict(int pages[], int frame[], int frames, int n, int index) {
    int res = -1, farthest = index;
    for (int i = 0; i < frames; i++) {
        int j;
        for (j = index; j < n; j++) {
            if (frame[i] == pages[j]) {
                if (j > farthest) {
                    farthest = j;
                    res = i;
                }
                break;
            }
        }
        if (j == n)
            return i;
    }
    return (res == -1) ? 0 : res;
}

// Function for Optimal Page Replacement
void optimal(int pages[], int n, int frames) {
    int frame[frames];
    for (int i = 0; i < frames; i++)
        frame[i] = -1;

    int pageFaults = 0;

    printf("\nOptimal Page Replacement:\n");
    for (int i = 0; i < n; i++) {
        int found = 0;
        for (int j = 0; j < frames; j++) {
            if (frame[j] == pages[i]) {
                found = 1;
                break;
            }
        }

        if (!found) {
            if (i < frames)
                frame[i] = pages[i];
            else {
                int j = predict(pages, frame, frames, n, i + 1);
                frame[j] = pages[i];
            }
            pageFaults++;
        }

        printf("Page %d: ", pages[i]);
        for (int j = 0; j < frames; j++) {
            if (frame[j] != -1)
                printf("%d ", frame[j]);
            else
                printf("- ");
        }
        printf("\n");
    }
    printf("Total Page Faults (Optimal): %d\n", pageFaults);
}

// Main function to run all algorithms
int main() {
    int n, frames;

    printf("Enter the number of pages: ");
    scanf("%d", &n);

    int pages[n];
    printf("Enter the page reference sequence:\n");
    for (int i = 0; i < n; i++) {
        printf("Page %d: ", i + 1);
        scanf("%d", &pages[i]);
    }

    printf("Enter the number of frames: ");
    scanf("%d", &frames);

    fifo(pages, n, frames);
    lru(pages, n, frames);
    optimal(pages, n, frames);

    return 0;
}
