#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <mqueue.h>
#include <string.h>

#define MQ_NAME "/message_queue"
#define MAX_MESSAGE_LEN 100
#define MAX_MESSAGES 10

int main() {
    // Message queue attributes
    struct mq_attr attr;
    attr.mq_flags = 0;
    attr.mq_maxmsg = MAX_MESSAGES;
    attr.mq_msgsize = MAX_MESSAGE_LEN;
    attr.mq_curmsgs = 0;

    // Create or open the message queue
    mqd_t mq = mq_open(MQ_NAME, O_CREAT | O_RDWR, 0666, &attr);
    if (mq == (mqd_t)-1) {
        perror("mq_open");
        exit(1);
    }

    char message[MAX_MESSAGE_LEN];
    while (1) {
        // Prompt the user to enter a message
        printf("Enter a message to send (or 'exit' to quit): ");
        fgets(message, MAX_MESSAGE_LEN, stdin);

        // Remove newline character from the message
        message[strcspn(message, "\n")] = '\0';

        // Exit condition if the user types 'exit'
        if (strcmp(message, "exit") == 0) {
            break;
        }

        // Send the message to the message queue
        if (mq_send(mq, message, strlen(message) + 1, 0) == -1) {
            perror("mq_send");
            exit(1);
        }

        printf("Message sent: %s\n", message);
    }

    // Cleanup: Close and unlink the message queue
    mq_close(mq);
    mq_unlink(MQ_NAME);

    return 0;
}
