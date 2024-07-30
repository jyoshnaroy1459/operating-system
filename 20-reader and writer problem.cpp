#include <stdio.h>
#include <pthread.h>
#include <semaphore.h>

sem_t mutex, wrt;
int readcount = 0;

void *reader(void *arg) {
    int id = *((int *)arg);
    sem_wait(&mutex);
    readcount++;
    if (readcount == 1) sem_wait(&wrt);
    sem_post(&mutex);

    printf("Reader %d is reading\n", id);

    sem_wait(&mutex);
    readcount--;
    if (readcount == 0) sem_post(&wrt);
    sem_post(&mutex);
    return NULL;
}

void *writer(void *arg) {
    int id = *((int *)arg);
    sem_wait(&wrt);
    printf("Writer %d is writing\n", id);
    sem_post(&wrt);
    return NULL;
}

int main() {
    pthread_t r, w;
    int id = 1;

    sem_init(&mutex, 0, 1);
    sem_init(&wrt, 0, 1);

    pthread_create(&r, NULL, reader, &id);
    pthread_create(&w, NULL, writer, &id);

    pthread_join(r, NULL);
    pthread_join(w, NULL);

    sem_destroy(&mutex);
    sem_destroy(&wrt);
    return 0;
}

