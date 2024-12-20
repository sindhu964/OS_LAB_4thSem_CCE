
#include <stdio.h>
#include <pthread.h>
#include <semaphore.h>
#include<unistd.h>

#define NUM_READERS 5
#define NUM_WRITERS 3

sem_t mutex;        // Controls access to readers_count
sem_t wrt;          // Controls access to the shared resource (writing)

int readers_count = 0;  // Number of readers currently reading

void *reader(void *arg) {
    int id = *(int *)arg;
    while (1) {
        // Reader tries to enter the critical section
        sem_wait(&mutex);
        readers_count++;
        if (readers_count == 1) {
            // First reader locks the resource from writers
            sem_wait(&wrt);
        }
        sem_post(&mutex);

        // Reading the shared resource
        printf("Reader %d is reading...\n", id);
        // Simulate reading
        sleep(1);

        // Reader exits the critical section
        sem_wait(&mutex);
        readers_count--;
        if (readers_count == 0) {
            // Last reader releases the resource for writers
            sem_post(&wrt);
        }
        sem_post(&mutex);

        // Reader goes to sleep for some time before reading again
        sleep(2);
    }
    return NULL;
}

void *writer(void *arg) {
    int id = *(int *)arg;
    while (1) {
        // Writer tries to enter the critical section
        sem_wait(&wrt);

        // Writing to the shared resource
        printf("Writer %d is writing...\n", id);
        // Simulate writing
        sleep(1);

        // Writer exits the critical section
        sem_post(&wrt);

        // Writer goes to sleep for some time before writing again
        sleep(2);
    }
    return NULL;
}

int main() {
    pthread_t readers[NUM_READERS], writers[NUM_WRITERS];
    int reader_ids[NUM_READERS], writer_ids[NUM_WRITERS];

    // Initialize semaphores
    sem_init(&mutex, 0, 1);
    sem_init(&wrt, 0, 1);

    // Create reader threads
    for (int i = 0; i < NUM_READERS; i++) {
        reader_ids[i] = i + 1;
        pthread_create(&readers[i], NULL, reader, &reader_ids[i]);
    }

    // Create writer threads
    for (int i = 0; i < NUM_WRITERS; i++) {
        writer_ids[i] = i + 1;
        pthread_create(&writers[i], NULL, writer, &writer_ids[i]);
    }

    // Wait for reader threads to finish
    for (int i = 0; i < NUM_READERS; i++) {
        pthread_join(readers[i], NULL);
    }

    // Wait for writer threads to finish
    for (int i = 0; i < NUM_WRITERS; i++) {
        pthread_join(writers[i], NULL);
    }

    // Destroy semaphores
    sem_destroy(&mutex);
    sem_destroy(&wrt);

    return 0;
}

