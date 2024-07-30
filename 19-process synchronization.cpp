#include <stdio.h>
#include <pthread.h>

#define NUM_THREADS 5

pthread_mutex_t mutex;
int shared_resource = 0;

void *thread_function(void *arg) {
    int thread_id = *((int *)arg);

    pthread_mutex_lock(&mutex);
    printf("Thread %d: Accessing shared resource\n", thread_id);
    shared_resource++;
    printf("Thread %d: Shared resource value: %d\n", thread_id, shared_resource);
    pthread_mutex_unlock(&mutex);

    return NULL;
}

int main() {
    pthread_t threads[NUM_THREADS];
    int thread_ids[NUM_THREADS];
    
    pthread_mutex_init(&mutex, NULL);

    for (int i = 0; i < NUM_THREADS; i++) {
        thread_ids[i] = i + 1;
        pthread_create(&threads[i], NULL, thread_function, &thread_ids[i]);
    }

    for (int i = 0; i < NUM_THREADS; i++) {
        pthread_join(threads[i], NULL);
    }

    pthread_mutex_destroy(&mutex);

    return 0;
}

