#include <stdio.h>
#include <limits.h> // For INT_MAX

// Define the structure for a memory block
struct Block {
    int size;
    int allocated; // 0 if not allocated, 1 if allocated
};

// Define the structure for a process
struct Process {
    int size;
    int allocated; // 0 if not allocated, 1 if allocated
};

// First Fit Allocation
void firstFit(struct Block blocks[], struct Process processes[], int numBlocks, int numProcesses) {
    printf("--- First Fit Allocation ---\n");
    for (int i = 0; i < numProcesses; i++) {
        int allocated = 0;
        for (int j = 0; j < numBlocks; j++) {
            if (!blocks[j].allocated && blocks[j].size >= processes[i].size) {
                blocks[j].allocated = 1;
                processes[i].allocated = 1;
                printf("Process %d (size %d) allocated to Block %d (size %d)\n", i + 1, processes[i].size, j + 1, blocks[j].size);
                allocated = 1;
                break;
            }
        }
        if (!allocated)
            printf("Process %d (size %d) could not be allocated a block\n", i + 1, processes[i].size);
    }
}

// Best Fit Allocation
void bestFit(struct Block blocks[], struct Process processes[], int numBlocks, int numProcesses) {
    printf("--- Best Fit Allocation ---\n");
    for (int i = 0; i < numProcesses; i++) {
        int bestIdx = -1;
        int minSpaceLeft = INT_MAX; // Initialize with a very large value

        for (int j = 0; j < numBlocks; j++) {
            if (!blocks[j].allocated && blocks[j].size >= processes[i].size) {
                int spaceLeft = blocks[j].size - processes[i].size;
                if (spaceLeft < minSpaceLeft) {
                    minSpaceLeft = spaceLeft;
                    bestIdx = j;
                }
            }
        }

        if (bestIdx != -1) {
            blocks[bestIdx].allocated = 1;
            processes[i].allocated = 1;
            printf("Process %d (size %d) allocated to Block %d (size %d)\n", i + 1, processes[i].size, bestIdx + 1, blocks[bestIdx].size);
        } else {
            printf("Process %d (size %d) could not be allocated a block\n", i + 1, processes[i].size);
        }
    }
}

// Worst Fit Allocation
void worstFit(struct Block blocks[], struct Process processes[], int numBlocks, int numProcesses) {
    printf("--- Worst Fit Allocation ---\n");
    for (int i = 0; i < numProcesses; i++) {
        int worstIdx = -1;
        int maxSpaceLeft = -1; // Initialize with a very small value

        for (int j = 0; j < numBlocks; j++) {
            if (!blocks[j].allocated && blocks[j].size >= processes[i].size) {
                int spaceLeft = blocks[j].size - processes[i].size;
                if (spaceLeft > maxSpaceLeft) {
                    maxSpaceLeft = spaceLeft;
                    worstIdx = j;
                }
            }
        }

        if (worstIdx != -1) {
            blocks[worstIdx].allocated = 1;
            processes[i].allocated = 1;
            printf("Process %d (size %d) allocated to Block %d (size %d)\n", i + 1, processes[i].size, worstIdx + 1, blocks[worstIdx].size);
        } else {
            printf("Process %d (size %d) could not be allocated a block (No block has enough space)\n", i + 1, processes[i].size);
        }
    }
}

int main() {
    int numBlocks, numProcesses;

    // Get the number of blocks and processes
    printf("Enter number of memory blocks: ");
    scanf("%d", &numBlocks);

    struct Block blocks[numBlocks];
    for (int i = 0; i < numBlocks; i++) {
        printf("Block %d size: ", i + 1);
        scanf("%d", &blocks[i].size);
        blocks[i].allocated = 0; // Initialize block as not allocated
    }

    printf("Enter number of processes: ");
    scanf("%d", &numProcesses);

    struct Process processes[numProcesses];
    for (int i = 0; i < numProcesses; i++) {
        printf("Process %d size: ", i + 1);
        scanf("%d", &processes[i].size);
        processes[i].allocated = 0; // Initialize process as not allocated
    }

    // Perform the allocation using First Fit, Best Fit, and Worst Fit
    firstFit(blocks, processes, numBlocks, numProcesses);
    printf("\n");

    // Reset block allocation status before the next allocation
    for (int i = 0; i < numBlocks; i++) blocks[i].allocated = 0;
    for (int i = 0; i < numProcesses; i++) processes[i].allocated = 0;

    bestFit(blocks, processes, numBlocks, numProcesses);
    printf("\n");

    // Reset block allocation status before the next allocation
    for (int i = 0; i < numBlocks; i++) blocks[i].allocated = 0;
    for (int i = 0; i < numProcesses; i++) processes[i].allocated = 0;

    worstFit(blocks, processes, numBlocks, numProcesses);

    return 0;
}
