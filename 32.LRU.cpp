#include <stdio.h>
#include <stdlib.h>
#define MAX_PAGES 100
#define MAX_FRAMES 10
void lru_paging(int page_sequence[], int num_pages, int num_frames) {
    int frames[MAX_FRAMES];
    int last_used[MAX_FRAMES];
    int page_faults = 0;
    for (int i = 0; i < num_frames; i++) {
        frames[i] = -1;
        last_used[i] = -1;
    }
    printf("Page Sequence: ");
    for (int i = 0; i < num_pages; i++) {
        printf("%d ", page_sequence[i]);
    }
    printf("\n");
    for (int i = 0; i < num_pages; i++) {
        int page = page_sequence[i];
        int page_found = 0;
        int replace_index = -1;
        int oldest_time = __INT_MAX__;
        for (int j = 0; j < num_frames; j++) {
            if (frames[j] == page) {
                page_found = 1;
                last_used[j] = i;
                break;
            }
        }
        if (!page_found) {
            for (int j = 0; j < num_frames; j++) {
                if (last_used[j] < oldest_time) {
                    oldest_time = last_used[j];
                    replace_index = j;
                }
            }
            frames[replace_index] = page;
            last_used[replace_index] = i;
            page_faults++;
            printf("Page Fault: Replace page with %d\n", page);
            printf("Frames: ");
            for (int k = 0; k < num_frames; k++) {
                if (frames[k] == -1) {
                    printf("_ ");
                } else {
                    printf("%d ", frames[k]);
                }
            }
            printf("\n");
        }
    }
    printf("Total Page Faults: %d\n", page_faults);
}
int main() {
    int page_sequence[MAX_PAGES];
    int num_pages, num_frames;
    printf("Enter the number of pages: ");
    scanf("%d", &num_pages);
    printf("Enter the page sequence: ");
    for (int i = 0; i < num_pages; i++) {
        scanf("%d", &page_sequence[i]);
    }
    printf("Enter the number of frames: ");
    scanf("%d", &num_frames);
    if (num_frames > MAX_FRAMES) {
        printf("Number of frames exceeds maximum allowed (%d).\n", MAX_FRAMES);
        return 1;
    }
    lru_paging(page_sequence, num_pages, num_frames);
    return 0;
}
