#include <stdio.h>
#include <stdlib.h>
void sort(int arr[], int n) {
    int i, j, temp;
    for (i = 0; i < n-1; i++) {
        for (j = i+1; j < n; j++) {
            if (arr[i] > arr[j]) {
                temp = arr[i];
                arr[i] = arr[j];
                arr[j] = temp;
            }
        }
    }
}
void scan(int requests[], int n, int head, int disk_size, int direction) {
    int i, seek_sequence[n+1], seek_count = 0;
    int left[n], right[n], left_size = 0, right_size = 0;
    if (direction == 0) {
        left[left_size++] = 0; 
    } else {
        right[right_size++] = disk_size - 1; 
    }

    for (i = 0; i < n; i++) {
        if (requests[i] < head)
            left[left_size++] = requests[i];
        else
            right[right_size++] = requests[i];
    }
    sort(left, left_size);
    sort(right, right_size);
    if (direction == 0) {
        for (i = left_size-1; i >= 0; i--) {
            seek_sequence[seek_count++] = left[i];
        }
        for (i = 0; i < right_size; i++) {
            seek_sequence[seek_count++] = right[i];
        }
    } else {
        for (i = 0; i < right_size; i++) {
            seek_sequence[seek_count++] = right[i];
        }
        for (i = left_size-1; i >= 0; i--) {
            seek_sequence[seek_count++] = left[i];
        }
    }
    int total_seek_time = 0;
    int current_head = head;
    for (i = 0; i < seek_count; i++) {
        total_seek_time += abs(current_head - seek_sequence[i]);
        current_head = seek_sequence[i];
    }
    printf("Seek Sequence: ");
    for (i = 0; i < seek_count; i++) {
        printf("%d ", seek_sequence[i]);
    }
    printf("\nTotal Seek Time: %d\n", total_seek_time);
}
int main() {
    int n, i, disk_size, head, direction;
    printf("Enter the number of requests: ");
    scanf("%d", &n);
    int requests[n];
    printf("Enter the requests: ");
    for (i = 0; i < n; i++) {
        scanf("%d", &requests[i]);
    }
    printf("Enter the initial head position: ");
    scanf("%d", &head);
    printf("Enter the disk size: ");
    scanf("%d", &disk_size);
    printf("Enter the direction (0 for left, 1 for right): ");
    scanf("%d", &direction);
    scan(requests, n, head, disk_size, direction);
    return 0;
}
