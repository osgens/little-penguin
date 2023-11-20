#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <fcntl.h>
#include <unistd.h>

#define THREAD_COUNT 5
#define ITERATIONS 10

void *read_thread(void *arg) {
    int fd = open("/sys/kernel/debug/fortytwo/foo", O_RDONLY);
    if (fd == -1) {
        perror("Error opening foo for reading");
        exit(EXIT_FAILURE);
    }

    char buffer[1024];
    ssize_t bytesRead;

    for (int i = 0; i < ITERATIONS; ++i) {
        bytesRead = read(fd, buffer, sizeof(buffer));
        if (bytesRead == -1) {
            perror("Error reading foo");
            exit(EXIT_FAILURE);
        }

        buffer[bytesRead] = '\0';
        printf("Read thread %lu: %s\n", (unsigned long)arg, buffer);

        // Sleep for a short duration to allow other threads to execute
        usleep(10000);
    }

    close(fd);
    return NULL;
}

void *write_thread(void *arg) {
    int fd = open("/sys/kernel/debug/fortytwo/foo", O_WRONLY);
    if (fd == -1) {
        perror("Error opening foo for writing");
        exit(EXIT_FAILURE);
    }

    char data[] = "Test data from write thread";
    ssize_t bytesWritten;

    for (int i = 0; i < ITERATIONS; ++i) {
        bytesWritten = write(fd, data, sizeof(data) - 1);
        if (bytesWritten == -1) {
            perror("Error writing foo");
            exit(EXIT_FAILURE);
        }

        printf("Write thread %lu: Wrote %ld bytes\n", (unsigned long)arg, bytesWritten);

        // Sleep for a short duration to allow other threads to execute
        usleep(10000);
    }

    close(fd);
    return NULL;
}

int main() {
    pthread_t readThreads[THREAD_COUNT];
    pthread_t writeThreads[THREAD_COUNT];

    // Create threads for reading and writing
    for (unsigned long i = 0; i < THREAD_COUNT; ++i) {
        pthread_create(&readThreads[i], NULL, read_thread, (void *)i);
        pthread_create(&writeThreads[i], NULL, write_thread, (void *)i);
    }

    // Join threads
    for (unsigned long i = 0; i < THREAD_COUNT; ++i) {
        pthread_join(readThreads[i], NULL);
        pthread_join(writeThreads[i], NULL);
    }

    return 0;
}
