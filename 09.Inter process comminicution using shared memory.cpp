#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/wait.h>
int main() {
    key_t key = ftok("shmfile", 65);
    int shmid = shmget(key, 1024, 0666 | IPC_CREAT);
    pid_t pid = fork();

    if (pid < 0) {
        perror("Fork failed");
        exit(1);
    } else if (pid == 0) {
        char *str = (char*) shmat(shmid, (void*)0, 0);
        printf("Child: Write Data: ");
        fgets(str, 1024, stdin);
        shmdt(str);
    } else {
        wait(NULL);
        char *str = (char*) shmat(shmid, (void*)0, 0);
        printf("Parent: Data read from memory: %s\n", str);
        shmdt(str);
        shmctl(shmid, IPC_RMID, NULL);
    }

    return 0;
}
