#include <stdio.h>
#include <pthread.h>
#include <semaphore.h>
#include <stdlib.h>
#include <unistd.h>

#define BUFFER_SIZE 10
#define PRODUCER_COUNT 2
#define CONSUMER_COUNT 2
#define ITEMS_TO_PRODUCE 10

sem_t empty;
sem_t full;
pthread_mutex_t mutex;

int buffer[BUFFER_SIZE];
int in = 0;
int out = 0;

typedef struct {
    int id;
} ThreadArg;

void *producer(void *arg) {
    ThreadArg *targ = (ThreadArg *)arg;
    int id = targ->id;

    for (int i = 0; i < ITEMS_TO_PRODUCE; i++) {
        sem_wait(&empty);
        pthread_mutex_lock(&mutex);

        buffer[in] = i;
        printf("Producer %d produced %d\n", id, buffer[in]);
        in = (in + 1) % BUFFER_SIZE;

        pthread_mutex_unlock(&mutex);
        sem_post(&full);

        sleep(rand() % 2);
    }
    return NULL;
}

void *consumer(void *arg) {
    ThreadArg *targ = (ThreadArg *)arg;
    int id = targ->id;

    for (int i = 0; i < ITEMS_TO_PRODUCE; i++) {
        sem_wait(&full);
        pthread_mutex_lock(&mutex);

        int item = buffer[out];
        printf("Consumer %d consumed %d\n", id, item);
        out = (out + 1) % BUFFER_SIZE;

        pthread_mutex_unlock(&mutex);
        sem_post(&empty);

        sleep(rand() % 2);
    }
    return NULL;
}

int main() {
    pthread_t producers[PRODUCER_COUNT], consumers[CONSUMER_COUNT];
    ThreadArg producer_args[PRODUCER_COUNT];
    ThreadArg consumer_args[CONSUMER_COUNT];
    
    sem_init(&empty, 0, BUFFER_SIZE);
    sem_init(&full, 0, 0);
    pthread_mutex_init(&mutex, NULL);

    for (int i = 0; i < PRODUCER_COUNT; i++) {
        producer_args[i].id = i + 1;
        pthread_create(&producers[i], NULL, producer, &producer_args[i]);
    }

    for (int i = 0; i < CONSUMER_COUNT; i++) {
        consumer_args[i].id = i + 1;
        pthread_create(&consumers[i], NULL, consumer, &consumer_args[i]);
    }

    for (int i = 0; i < PRODUCER_COUNT; i++) {
        pthread_join(producers[i], NULL);
    }

    for (int i = 0; i < CONSUMER_COUNT; i++) {
        pthread_join(consumers[i], NULL);
    }

    sem_destroy(&empty);
    sem_destroy(&full);
    pthread_mutex_destroy(&mutex);

    return 0;
}

