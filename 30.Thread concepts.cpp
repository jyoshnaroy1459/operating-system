#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>
void* thread_function(void* arg) {
    printf("Thread %ld is running\n", (long)arg);
    sleep(1); 
    pthread_exit(NULL);
}
int main() {
    pthread_t thread1, thread2;
    int result;
    result = pthread_create(&thread1, NULL, thread_function, (void*)1);
    if (result != 0) {
        fprintf(stderr, "Error creating thread 1\n");
        exit(EXIT_FAILURE);
    }
    result = pthread_create(&thread2, NULL, thread_function, (void*)2);
    if (result != 0) {
        fprintf(stderr, "Error creating thread 2\n");
        exit(EXIT_FAILURE);
    }
    result = pthread_join(thread1, NULL);
    if (result != 0) {
        fprintf(stderr, "Error joining thread 1\n");
        exit(EXIT_FAILURE);
    }
    result = pthread_join(thread2, NULL);
    if (result != 0) {
        fprintf(stderr, "Error joining thread 2\n");
        exit(EXIT_FAILURE);
    }
    if (pthread_equal(thread1, thread2)) {
        printf("Thread 1 and Thread 2 are equal\n");
    } else {
        printf("Thread 1 and Thread 2 are not equal\n");
    }
    
    printf("Both threads have terminated\n");
    
    return 0;
}
