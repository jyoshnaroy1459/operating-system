#include <stdio.h>
#include <stdbool.h>

#define P 5
#define R 3

int available[R] = {10, 5, 7};
int max[P][R] = {
    {7, 5, 3},
    {3, 2, 2},
    {9, 0, 2},
    {2, 2, 2},
    {4, 3, 3}
};
int allot[P][R] = {
    {0, 1, 0},
    {2, 0, 0},
    {3, 0, 2},
    {2, 1, 1},
    {0, 0, 2}
};

void calculateNeed(int need[][R]) {
    for (int i = 0; i < P; i++)
        for (int j = 0; j < R; j++)
            need[i][j] = max[i][j] - allot[i][j];
}

bool isSafe(int need[][R]) {
    bool finish[P] = {0};
    int safeSeq[P];
    int work[R];
    
    for (int i = 0; i < R; i++)
        work[i] = available[i];

    int count = 0;
    while (count < P) {
        bool found = false;
        for (int p = 0; p < P; p++) {
            if (!finish[p]) {
                int j;
                for (j = 0; j < R; j++)
                    if (need[p][j] > work[j])
                        break;

                if (j == R) {
                    for (int k = 0; k < R; k++)
                        work[k] += allot[p][k];

                    safeSeq[count++] = p;
                    finish[p] = 1;
                    found = true;
                }
            }
        }

        if (!found) {
            printf("System is not in a safe state.\n");
            return false;
        }
    }

    printf("System is in a safe state.\nSafe sequence is: ");
    for (int i = 0; i < P; i++)
        printf("%d ", safeSeq[i]);
    printf("\n");

    return true;
}

bool requestResources(int process, int request[]) {
    int need[P][R];
    calculateNeed(need);

    for (int i = 0; i < R; i++)
        if (request[i] > need[process][i])
            return false;

    for (int i = 0; i < R; i++)
        if (request[i] > available[i])
            return false;

    for (int i = 0; i < R; i++) {
        available[i] -= request[i];
        allot[process][i] += request[i];
    }

    if (isSafe(need))
        return true;
    else {
        for (int i = 0; i < R; i++) {
            available[i] += request[i];
            allot[process][i] -= request[i];
        }
        return false;
    }
}

int main() {
    int request[R];
    int process;

    printf("Enter process number (0-%d): ", P-1);
    scanf("%d", &process);

    printf("Enter request for %d resources: ", R);
    for (int i = 0; i < R; i++)
        scanf("%d", &request[i]);

    if (requestResources(process, request))
        printf("Request granted.\n");
    else
        printf("Request denied.\n");

    return 0;
}

