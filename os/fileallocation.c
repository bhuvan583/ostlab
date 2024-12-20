#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define BLOCK_SIZE 50  // Size of each block

// Sequential Allocation function
void sequentialAllocation(int totalBlocks) {
    char fileData[totalBlocks][BLOCK_SIZE];  // Array to hold the data for each block

    // User input for each block's data
    printf("\nEnter data for each block (max %d characters per block):\n", BLOCK_SIZE);
    for (int i = 0; i < totalBlocks; i++) {
        printf("Block %d: ", i + 1);
        fgets(fileData[i], BLOCK_SIZE, stdin);
        fileData[i][strcspn(fileData[i], "\n")] = '\0';  // Remove newline character
    }

    // Displaying the blocks (sequential access)
    printf("\nSequential File Allocation (Contiguous Storage):\n");
    for (int i = 0; i < totalBlocks; i++) {
        printf("Block %d: %s\n", i + 1, fileData[i]);
    }

    // Additional Info: Sequential allocation allows accessing blocks one by one
    printf("\nIn sequential allocation, data is stored in contiguous memory locations.\n");
    printf("Blocks are accessed sequentially from Block 1 to Block %d.\n", totalBlocks);
}

// Indexed Allocation function
void indexedAllocation(int totalBlocks) {
    char fileData[totalBlocks][BLOCK_SIZE];  // Array to hold the data for each block
    int index[totalBlocks];  // Array to simulate the index block (storing pointers)

    // User input for each block's data
    printf("\nEnter data for each block (max %d characters per block):\n", BLOCK_SIZE);
    for (int i = 0; i < totalBlocks; i++) {
        printf("Block %d: ", i + 1);
        fgets(fileData[i], BLOCK_SIZE, stdin);
        fileData[i][strcspn(fileData[i], "\n")] = '\0';  // Remove newline character
        index[i] = i;  // Each entry in the index points to the corresponding block
    }

    // Displaying the index block and data blocks
    printf("\nIndexed File Allocation (Using Index Block):\n");
    printf("Index Block: ");
    for (int i = 0; i < totalBlocks; i++) {
        printf("%d ", index[i]);  // Displaying the index block
    }
    printf("\n");

    // Display the data from each block using the index block
    for (int i = 0; i < totalBlocks; i++) {
        printf("Block %d (Index %d): %s\n", i + 1, index[i], fileData[index[i]]);
    }

    // Additional Info: Indexed allocation uses an index block to point to data blocks
    printf("\nIn indexed allocation, there is an index block storing the pointers to the data blocks.\n");
    printf("Each block can be accessed randomly using the index block.\n");
}

// Linked Allocation function
struct Block {
    char data[BLOCK_SIZE];
    struct Block* next;  // Pointer to the next block
};

void linkedAllocation(int totalBlocks) {
    struct Block* head = NULL;  // Head of the linked list (file)
    struct Block* current = NULL;  // Pointer to traverse the linked list

    // User input for each block's data
    printf("\nEnter data for each block (max %d characters per block):\n", BLOCK_SIZE);
    for (int i = 0; i < totalBlocks; i++) {
        struct Block* newBlock = (struct Block*)malloc(sizeof(struct Block));
        if (!newBlock) {
            perror("Memory allocation failed");
            return;
        }

        printf("Block %d: ", i + 1);
        fgets(newBlock->data, BLOCK_SIZE, stdin);
        newBlock->data[strcspn(newBlock->data, "\n")] = '\0';  // Remove newline character
        newBlock->next = NULL;  // Initialize the next pointer to NULL

        if (head == NULL) {
            head = newBlock;  // Set the first block as the head
        } else {
            current->next = newBlock;  // Link the previous block to the new one
        }

        current = newBlock;  // Move current to the new block
    }

    // Displaying the blocks (traversing the linked list)
    printf("\nLinked File Allocation (Using Linked List):\n");
    current = head;
    int blockNumber = 1;
    while (current != NULL) {
        printf("Block %d: %s\n", blockNumber++, current->data);
        current = current->next;  // Move to the next block
    }

    // Additional Info: Linked allocation stores a linked list of blocks
    printf("\nIn linked allocation, each block contains a pointer to the next block.\n");
    printf("To access the data, you must traverse the linked list from the head to the end.\n");

    // Freeing the allocated memory
    current = head;
    while (current != NULL) {
        struct Block* temp = current;
        current = current->next;
        free(temp);
    }
}

// Main function
int main() {
    int totalBlocks, choice;

    // Get the number of blocks from the user
    printf("Enter the total number of blocks: ");
    scanf("%d", &totalBlocks);
    getchar();  // To consume the newline character left by scanf()

    // Display menu
    printf("\nFile Allocation Strategies\n");
    printf("1. Sequential Allocation\n");
    printf("2. Indexed Allocation\n");
    printf("3. Linked Allocation\n");
    printf("Enter your choice (1-3): ");
    scanf("%d", &choice);
    getchar();  // To consume the newline character left by scanf()

    // Execute chosen allocation strategy
    switch (choice) {
        case 1:
            sequentialAllocation(totalBlocks);
            break;
        case 2:
            indexedAllocation(totalBlocks);
            break;
        case 3:
            linkedAllocation(totalBlocks);
            break;
        default:
            printf("Invalid choice! Please enter 1, 2, or 3.\n");
    }

    return 0;
}
