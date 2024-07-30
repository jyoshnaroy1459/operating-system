#include <stdio.h>
#include <pthread.h>
#include <unistd.h> // For sleep()

// Critical Section Problem
#define NUM_CS_THREADS 2
pthread_mutex_t cs_mutex;

void* critical_section(void* arg) {
    int thread_id = *((int*)arg);

    pthread_mutex_lock(&cs_mutex);
    printf("Critical Section: Thread %d is in the critical section\n", thread_id);
    sleep(1); // Simulate work
    printf("Critical Section: Thread %d is leaving the critical section\n", thread_id);
    pthread_mutex_unlock(&cs_mutex);

    pthread_exit(NULL);
}

// Producer-Consumer Problem
#define BUFFER_SIZE 5
#define NUM_PRODUCERS 1
#define NUM_CONSUMERS 1

int buffer[BUFFER_SIZE];
int count = 0;
pthread_mutex_t pc_mutex;
pthread_cond_t pc_full;
pthread_cond_t pc_empty;

void* producer(void* arg) {
    for (int i = 0; i < 10; i++) {
        pthread_mutex_lock(&pc_mutex);

        while (count == BUFFER_SIZE) {
            pthread_cond_wait(&pc_full, &pc_mutex);
        }

        buffer[count] = i;
        printf("Producer: Produced %d\n", i);
        count++;

        pthread_cond_signal(&pc_empty);
        pthread_mutex_unlock(&pc_mutex);

        sleep(1);
    }
    pthread_exit(NULL);
}

void* consumer(void* arg) {
    for (int i = 0; i < 10; i++) {
        pthread_mutex_lock(&pc_mutex);

        while (count == 0) {
            pthread_cond_wait(&pc_empty, &pc_mutex);
        }

        int item = buffer[count - 1];
        count--;
        printf("Consumer: Consumed %d\n", item);

        pthread_cond_signal(&pc_full);
        pthread_mutex_unlock(&pc_mutex);

        sleep(2);
    }
    pthread_exit(NULL);
}

// Reader-Writer Problem
#define NUM_READERS 3
#define NUM_WRITERS 2

int data = 0;
int read_count = 0;
pthread_mutex_t rw_mutex;
pthread_mutex_t rw_read_mutex;
pthread_mutex_t rw_write_mutex;

void* reader(void* arg) {
    int reader_id = *((int*)arg);
    for (int i = 0; i < 5; i++) {
        pthread_mutex_lock(&rw_read_mutex);
        pthread_mutex_lock(&rw_mutex);

        read_count++;
        if (read_count == 1) {
            pthread_mutex_lock(&rw_write_mutex);
        }

        pthread_mutex_unlock(&rw_mutex);
        pthread_mutex_unlock(&rw_read_mutex);

        printf("Reader %d: Read data = %d\n", reader_id, data);

        pthread_mutex_lock(&rw_mutex);
        read_count--;
        if (read_count == 0) {
            pthread_mutex_unlock(&rw_write_mutex);
        }
        pthread_mutex_unlock(&rw_mutex);

        sleep(1);
    }
    pthread_exit(NULL);
}

void* writer(void* arg) {
    int writer_id = *((int*)arg);
    for (int i = 0; i < 5; i++) {
        pthread_mutex_lock(&rw_write_mutex);

        data++;
        printf("Writer %d: Wrote data = %d\n", writer_id, data);

        pthread_mutex_unlock(&rw_write_mutex);

        sleep(2);
    }
    pthread_exit(NULL);
}

int main() {
    pthread_t cs_threads[NUM_CS_THREADS];
    pthread_t producers[NUM_PRODUCERS];
    pthread_t consumers[NUM_CONSUMERS];
    pthread_t readers[NUM_READERS];
    pthread_t writers[NUM_WRITERS];

    // Initialize mutexes and condition variables
    pthread_mutex_init(&cs_mutex, NULL);
    pthread_mutex_init(&pc_mutex, NULL);
    pthread_cond_init(&pc_full, NULL);
    pthread_cond_init(&pc_empty, NULL);
    pthread_mutex_init(&rw_mutex, NULL);
    pthread_mutex_init(&rw_read_mutex, NULL);
    pthread_mutex_init(&rw_write_mutex, NULL);

    // Critical Section Problem
    int cs_ids[NUM_CS_THREADS];
    for (int i = 0; i < NUM_CS_THREADS; i++) {
        cs_ids[i] = i + 1;
        pthread_create(&cs_threads[i], NULL, critical_section, (void*)&cs_ids[i]);
    }
    for (int i = 0; i < NUM_CS_THREADS; i++) {
        pthread_join(cs_threads[i], NULL);
    }

    // Producer-Consumer Problem
    for (int i = 0; i < NUM_PRODUCERS; i++) {
        pthread_create(&producers[i], NULL, producer, NULL);
    }
    for (int i = 0; i < NUM_CONSUMERS; i++) {
        pthread_create(&consumers[i], NULL, consumer, NULL);
    }
    for (int i = 0; i < NUM_PRODUCERS; i++) {
        pthread_join(producers[i], NULL);
    }
    for (int i = 0; i < NUM_CONSUMERS; i++) {
        pthread_join(consumers[i], NULL);
    }

    // Reader-Writer Problem
    int reader_ids[NUM_READERS];
    int writer_ids[NUM_WRITERS];
    for (int i = 0; i < NUM_READERS; i++) {
        reader_ids[i] = i + 1;
        pthread_create(&readers[i], NULL, reader, (void*)&reader_ids[i]);
    }
    for (int i = 0; i < NUM_WRITERS; i++) {
        writer_ids[i] = i + 1;
        pthread_create(&writers[i], NULL, writer, (void*)&writer_ids[i]);
    }
    for (int i = 0; i < NUM_READERS; i++) {
        pthread_join(readers[i], NULL);
    }
    for (int i = 0; i < NUM_WRITERS; i++) {
        pthread_join(writers[i], NULL);
    }

    // Destroy mutexes and condition variables
    pthread_mutex_destroy(&cs_mutex);
    pthread_mutex_destroy(&pc_mutex);
    pthread_cond_destroy(&pc_full);
    pthread_cond_destroy(&pc_empty);
    pthread_mutex_destroy(&rw_mutex);
    pthread_mutex_destroy(&rw_read_mutex);
    pthread_mutex_destroy(&rw_write_mutex);

    return 0;
}

