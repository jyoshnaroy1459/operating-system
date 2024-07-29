#include <stdio.h>
#include <pthread.h>
#include <unistd.h>

#define N 2
#define ITERATIONS 1
pthread_mutex_t chopsticks[N];

void* philosopher(void* num) {
    int id = *(int*)num;
    for (int i = 0; i < ITERATIONS; i++) {
        printf("Philosopher %d is thinking.\n", id);
        sleep(1);
        pthread_mutex_lock(&chopsticks[id]);
        pthread_mutex_lock(&chopsticks[(id + 1) % N]);
        printf("Philosopher %d is eating.\n", id);
        sleep(1);
        pthread_mutex_unlock(&chopsticks[(id + 1) % N]);
        pthread_mutex_unlock(&chopsticks[id]);
        printf("Philosopher %d finished eating.\n", id);
        sleep(1);
    }
    return NULL;
}

int main() {
    pthread_t philosophers[N];
    int ids[N];
    for (int i = 0; i < N; i++) {
        ids[i] = i;
        pthread_mutex_init(&chopsticks[i], NULL);
        pthread_create(&philosophers[i], NULL, philosopher, &ids[i]);
    }
    for (int i = 0; i < N; i++) pthread_join(philosophers[i], NULL);
    for (int i = 0; i < N; i++) pthread_mutex_destroy(&chopsticks[i]);
    return 0;
}
