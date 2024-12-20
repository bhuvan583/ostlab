#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/mman.h>      // Correct header for shared memory
#include <sys/stat.h>
#include <string.h>

#define SHM_NAME "/shm_buffer"
#define MAX_MESSAGE_LEN 100

typedef struct {
    int in;
    int out;
    int count;
    int buffer_size;
} SharedData;

int main() {
    int buffer_size;

    // Prompt the user for buffer size
    printf("Enter the buffer size: ");
    scanf("%d", &buffer_size);

    if (buffer_size <= 0) {
        printf("Buffer size must be a positive integer.\n");
        exit(1);
    }

    int shm_fd;
    SharedData *shared_data;

    // Create shared memory
    shm_fd = shm_open(SHM_NAME, O_CREAT | O_RDWR, 0666);
    if (shm_fd == -1) {
        perror("shm_open");
        exit(1);
    }

    // Set shared memory size
    size_t total_size = sizeof(SharedData) + buffer_size * MAX_MESSAGE_LEN * sizeof(char);
    if (ftruncate(shm_fd, total_size) == -1) {
        perror("ftruncate");
        exit(1);
    }

    // Map shared memory
    shared_data = mmap(0, total_size, PROT_WRITE | PROT_READ, MAP_SHARED, shm_fd, 0);
    if (shared_data == MAP_FAILED) {
        perror("mmap");
        exit(1);
    }

    // Initialize shared variables
    shared_data->in = 0;
    shared_data->out = 0;
    shared_data->count = 0;
    shared_data->buffer_size = buffer_size;

    // Dynamically allocated buffer inside shared memory
    char (*buffer)[MAX_MESSAGE_LEN] = (char (*)[MAX_MESSAGE_LEN])(shared_data + 1);

    printf("Producing messages...\n");

    for (int i = 0; i < buffer_size; i++) {
        // Busy wait until there's space in the buffer
        while (shared_data->count == buffer_size) {
            // Wait for consumer to consume
        }

        // Produce item
        char item[MAX_MESSAGE_LEN];
        snprintf(item, MAX_MESSAGE_LEN, "Message %d", i);

        strncpy(buffer[shared_data->in], item, MAX_MESSAGE_LEN);
        printf("Produced: %s\n", item);

        shared_data->in = (shared_data->in + 1) % buffer_size;
        shared_data->count++;

        sleep(1);  // Simulate time to produce
    }

    // Cleanup
    munmap(shared_data, total_size);
    close(shm_fd);

    return 0;
}
