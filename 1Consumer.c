#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/mman.h>      // Required for mmap, shm_open, munmap, PROT_READ, PROT_WRITE, MAP_SHARED
#include <sys/stat.h>      // Required for shm_open
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
    int shm_fd;
    SharedData *shared_data;

    // Open shared memory
    shm_fd = shm_open(SHM_NAME, O_RDWR, 0666);
    if (shm_fd == -1) {
        perror("shm_open");
        exit(1);
    }

    // Map shared memory
    size_t total_size = sizeof(SharedData) + MAX_MESSAGE_LEN * sizeof(char) * 100; // Example buffer size
    shared_data = mmap(0, total_size, PROT_READ | PROT_WRITE, MAP_SHARED, shm_fd, 0);
    if (shared_data == MAP_FAILED) {
        perror("mmap");
        exit(1);
    }

    // Dynamically allocated buffer inside shared memory
    char (*buffer)[MAX_MESSAGE_LEN] = (char (*)[MAX_MESSAGE_LEN])(shared_data + 1);

    printf("Consuming messages...\n");

    for (int i = 0; i < shared_data->buffer_size; i++) {
        // Busy wait until there's an item in the buffer
        while (shared_data->count == 0) {
            // Wait for producer to produce
        }

        // Consume item
        printf("Consumed: %s\n", buffer[shared_data->out]);

        shared_data->out = (shared_data->out + 1) % shared_data->buffer_size;
        shared_data->count--;

        sleep(1);  // Simulate time to consume
    }

    // Cleanup
    munmap(shared_data, total_size);
    shm_unlink(SHM_NAME);

    return 0;
}
