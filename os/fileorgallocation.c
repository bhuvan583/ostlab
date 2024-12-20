#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define SIZE 10  // Hash table size for direct access

struct Record {
    int id;
    char name[30];
    long offset;  // Used only for indexed file organization
};

// Function declarations
void sequentialFile();
void directFile();
void indexedFile();
void clusteredFile();

// Hash function for Direct (Hashed) File Organization
int hashFunction(int id) {
    return id % SIZE;
}

// Menu function
int main() {
    int choice;

    do {
        printf("\nFile Organization Techniques\n");
        printf("1. Sequential File\n");
        printf("2. Direct (Hashed) File\n");
        printf("3. Indexed File\n");
        printf("4. Clustered File\n");
        printf("5. Exit\n");
        printf("Choose an option: ");
        scanf("%d", &choice);

        // Clear the input buffer to avoid any leftover input
        while (getchar() != '\n');

        switch (choice) {
            case 1:
                sequentialFile();
                break;
            case 2:
                directFile();
                break;
            case 3:
                indexedFile();
                break;
            case 4:
                clusteredFile();
                break;
            case 5:
                printf("Exiting...\n");
                break;
            default:
                printf("Invalid option! Please try again.\n");
        }
    } while (choice != 5);

    return 0;
}

// 1. Sequential File Organization
void sequentialFile() {
    FILE *file = fopen("sequential.txt", "a+");  // Open in append+read mode
    struct Record rec;
    int n;

    printf("Enter number of records: ");
    scanf("%d", &n);

    // Clear the input buffer to avoid any leftover input
    while (getchar() != '\n');

    for (int i = 0; i < n; i++) {
        printf("Enter ID and Name: ");
        if (scanf("%d %29[^\n]", &rec.id, rec.name) != 2) {
            printf("Invalid input format. Please try again.\n");
            while (getchar() != '\n'); // clear the buffer
            i--; // retry current record entry
            continue;
        }
        fwrite(&rec, sizeof(struct Record), 1, file);  // Write record to file
    }

    rewind(file);  // Reset the file pointer to the beginning to read the written records

    printf("Reading Sequential File:\n");
    while (fread(&rec, sizeof(struct Record), 1, file)) {  // Read from the beginning of the file
        printf("ID: %d, Name: %s\n", rec.id, rec.name);
    }
    fclose(file);
}

// 2. Direct (Hashed) File Organization
void directFile() {
    struct Record rec;
    int id, index, n;
    char filename[20];

    // Ask for the number of records to be input
    printf("Enter number of records: ");
    scanf("%d", &n);

    // Clear the input buffer to avoid leftover data
    while (getchar() != '\n');

    // Loop to input multiple records
    for (int i = 0; i < n; i++) {
        printf("Enter ID and Name for record %d: ", i + 1);
        if (scanf("%d %29[^\n]", &rec.id, rec.name) != 2) {
            printf("Invalid input format. Please try again.\n");
            while (getchar() != '\n'); // Clear input buffer
            i--; // Retry the current record
            continue;
        }

        // Calculate index based on the hash function
        index = hashFunction(rec.id);
        sprintf(filename, "direct%d.txt", index);  // Construct filename based on index

        // Open the file and write the record
        FILE *file = fopen(filename, "a+");  // Open in append mode to add records
        if (!file) {
            printf("Error opening file.\n");
            return;
        }
        fwrite(&rec, sizeof(struct Record), 1, file);
        fclose(file);
    }

    // Ask for an ID to search for the record
    printf("Enter ID to read: ");
    if (scanf("%d", &id) != 1) {
        printf("Invalid input.\n");
        return;
    }

    // Calculate index again to check the specific file
    index = hashFunction(id);
    sprintf(filename, "direct%d.txt", index);
    FILE *file = fopen(filename, "r");

    // Read the record from the file if it exists
    int found = 0;
    while (file && fread(&rec, sizeof(struct Record), 1, file)) {
        if (rec.id == id) {
            printf("ID: %d, Name: %s\n", rec.id, rec.name);
            found = 1;
            break;
        }
    }
    if (!found) {
        printf("Record not found.\n");
    }

    fclose(file);
}

// 3. Indexed File Organization
void createIndexFile() {
    FILE *file = fopen("indexed.txt", "a+");
    FILE *indexFile = fopen("index.txt", "a+");
    struct Record rec;
    int n;

    printf("Enter number of records: ");
    scanf("%d", &n);

    // Clear the input buffer
    while (getchar() != '\n');

    for (int i = 0; i < n; i++) {
        printf("Enter ID and Name: ");
        if (scanf("%d %29[^\n]", &rec.id, rec.name) != 2) {
            printf("Invalid input format. Please try again.\n");
            while (getchar() != '\n'); // clear the buffer
            i--; // retry current record entry
            continue;
        }
        rec.offset = ftell(file);
        fwrite(&rec, sizeof(struct Record), 1, file);
        fwrite(&rec, sizeof(struct Record), 1, indexFile);
    }
    fclose(file);
    fclose(indexFile);
}

void readIndexedFile(int id) {
    FILE *file = fopen("indexed.txt", "r");
    FILE *indexFile = fopen("index.txt", "r");
    struct Record rec;

    while (fread(&rec, sizeof(struct Record), 1, indexFile)) {
        if (rec.id == id) {
            fseek(file, rec.offset, SEEK_SET);
            fread(&rec, sizeof(struct Record), 1, file);
            printf("ID: %d, Name: %s\n", rec.id, rec.name);
            fclose(file);
            fclose(indexFile);
            return;
        }
    }
    printf("Record not found\n");
    fclose(file);
    fclose(indexFile);
}

void indexedFile() {
    int choice, id;
    printf("1. Add records\n2. Read record by ID\nChoose an option: ");
    scanf("%d", &choice);
    if (choice == 1) {
        createIndexFile();
    } else if (choice == 2) {
        printf("Enter ID to read: ");
        scanf("%d", &id);
        readIndexedFile(id);
    } else {
        printf("Invalid option!\n");
    }
}

// 4. Clustered File Organization
void clusteredFile() {
    FILE *file = fopen("clustered.txt", "a+");
    struct Record rec;
    int n;

    printf("Enter number of records: ");
    scanf("%d", &n);

    // Clear the input buffer
    while (getchar() != '\n');

    for (int i = 0; i < n; i++) {
        printf("Enter ID and Name: ");
        if (scanf("%d %29[^\n]", &rec.id, rec.name) != 2) {
            printf("Invalid input format. Please try again.\n");
            while (getchar() != '\n'); // clear the buffer
            i--; // retry current record entry
            continue;
        }
        fwrite(&rec, sizeof(struct Record), 1, file);
    }
    rewind(file);

    printf("Reading Clustered File:\n");
    while (fread(&rec, sizeof(struct Record), 1, file)) {
        printf("ID: %d, Name: %s\n", rec.id, rec.name);
    }
    fclose(file);
}
