#include <stdio.h>
#include <stdlib.h>

// Function to simulate page access and handle page faults
void accessPage(int pageReference, int *frames, int maxFrames, int *pageTable, int maxPages) {
    int found = 0;

    // Check if the page is already in one of the frames
    for (int i = 0; i < maxFrames; i++) {
        if (frames[i] == pageReference) {
            found = 1;
            break;
        }
    }

    if (found) {
        printf("Page %d is already in physical memory.\n", pageReference);
    } else {
        printf("Page %d caused a page fault.\n", pageReference);

        // Find the first empty frame or replace the page in the first empty slot
        for (int i = 0; i < maxFrames; i++) {
            if (frames[i] == -1) {  // Empty slot in physical memory
                frames[i] = pageReference;
                break;
            }
        }
    }

    // Print the current state of physical memory (frames)
    printf("Current Physical Memory: ");
    for (int i = 0; i < maxFrames; i++) {
        if (frames[i] != -1) {
            printf("Page %d ", frames[i]);
        } else {
            printf("_ ");
        }
    }
    printf("\n");
}

int main() {
    int maxFrames, maxPages;

    // Get user input for the number of frames (physical memory) and pages (logical memory)
    printf("Enter the number of frames (physical memory): ");
    scanf("%d", &maxFrames);

    printf("Enter the number of pages (logical memory): ");
    scanf("%d", &maxPages);

    // Allocate arrays for page table and frames
    int frames[maxFrames];  // To simulate physical memory
    int pageTable[maxPages]; // To simulate logical memory (page table)

    // Initialize frames and pageTable to -1 (empty or not loaded in memory)
    for (int i = 0; i < maxFrames; i++) {
        frames[i] = -1;  // No pages loaded initially
    }

    for (int i = 0; i < maxPages; i++) {
        pageTable[i] = -1;  // No pages loaded initially
    }

    // Get the page reference string from the user
    int numReferences;
    printf("Enter the number of page references: ");
    scanf("%d", &numReferences);

    int reference[numReferences];
    printf("Enter the page reference string: ");
    for (int i = 0; i < numReferences; i++) {
        scanf("%d", &reference[i]);
    }

    // Simulate page accesses
    printf("\n--- Simulating Paging (Logical to Physical Memory) ---\n");
    for (int i = 0; i < numReferences; i++) {
        int pageReference = reference[i];
        accessPage(pageReference, frames, maxFrames, pageTable, maxPages);
    }

    return 0;
}
