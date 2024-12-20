#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <mqueue.h>
#include <string.h>

#define MQ_NAME "/message_queue"
#define MAX_MESSAGE_LEN 100

int main() {
    // Message queue attributes
    struct mq_attr attr;
    attr.mq_flags = 0;
    attr.mq_maxmsg = 10;
    attr.mq_msgsize = MAX_MESSAGE_LEN;
    attr.mq_curmsgs = 0;

    // Open the message queue
    mqd_t mq = mq_open(MQ_NAME, O_CREAT | O_RDWR);
    if (mq == (mqd_t)-1) {
        perror("mq_open");
        exit(1);
    }

    printf("Consuming messages...\n");

    char message[MAX_MESSAGE_LEN];
    while (1) {
        // Receive a message from the queue
        ssize_t bytes_read = mq_receive(mq, message, MAX_MESSAGE_LEN, NULL);
        if (bytes_read >= 0) {
            printf("Message: %s\n", message);
        } else {
            perror("mq_receive");
            break;
        }
    }

    // Cleanup: Close and unlink the message queue
    mq_close(mq);
    mq_unlink(MQ_NAME);

    return 0;
}
