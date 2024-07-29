#include <stdio.h>
#include <pthread.h>

void* threadFunction(void* arg) {
    printf("Thread %d is running.\n", *(int*)arg);
    return NULL;
}

int main() {
    pthread_t threads[3];
    int args[3] = {1, 2, 3};

    for (int i = 0; i < 3; i++)
        pthread_create(&threads[i], NULL, threadFunction, &args[i]);

    for (int i = 0; i < 3; i++)
        pthread_join(threads[i], NULL);

    return 0;
}
