#include <stdio.h>
#include <stdlib.h>
void fcfs(int requests[], int n, int head) {
    int total_seek_time = 0;
    int current_head = head;
    printf("Seek Sequence: %d ", head);
    for (int i = 0; i < n; i++) {
        total_seek_time += abs(current_head - requests[i]);
        current_head = requests[i];
        printf("%d ", current_head);
    }   
    printf("\nTotal Seek Time: %d\n", total_seek_time);
}
int main() {
    int n, head;
    printf("Enter the number of requests: ");
    scanf("%d", &n);
    int requests[n];
    printf("Enter the requests: ");
    for (int i = 0; i < n; i++) {
        scanf("%d", &requests[i]);
    }
    printf("Enter the initial head position: ");
    scanf("%d", &head);
    fcfs(requests, n, head);
    return 0;
}
