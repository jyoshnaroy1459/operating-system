#include <stdio.h>
#include <stdlib.h>
#define MAX_BLOCKS 100
typedef struct Block {
    int data;
    struct Block* next;
} Block;
typedef struct File {
    Block* start;
    Block* end;
} File;
typedef struct Directory {
    File* file;
} Directory;
Block* allocate_block(int data) {
    Block* new_block = (Block*)malloc(sizeof(Block));
    if (new_block == NULL) {
        printf("Memory allocation failed\n");
        exit(1);
    }
    new_block->data = data;
    new_block->next = NULL;
    return new_block;
}

void deallocate_blocks(Block* start) {
    Block* temp;
    while (start != NULL) {
        temp = start;
        start = start->next;
        free(temp);
    }
}
void create_file(Directory* dir, int* data, int size) {
    if (size <= 0) {
        printf("Invalid file size\n");
        return;
    }
    File* new_file = (File*)malloc(sizeof(File));
    if (new_file == NULL) {
        printf("Memory allocation failed\n");
        exit(1);
    }
    new_file->start = allocate_block(data[0]);
    Block* current = new_file->start;
    for (int i = 1; i < size; i++) {
        current->next = allocate_block(data[i]);
        current = current->next;
    }
    new_file->end = current;
    dir->file = new_file;
}
void display_file(File* file) {
    if (file == NULL || file->start == NULL) {
        printf("File does not exist\n");
        return;
    }
    Block* current = file->start;
    printf("File content: ");
    while (current != NULL) {
        printf("%d ", current->data);
        current = current->next;
    }
    printf("\n");
}

void delete_file(Directory* dir) {
    if (dir->file == NULL) {
        printf("No file to delete\n");
        return;
    }
    deallocate_blocks(dir->file->start);
    free(dir->file);
    dir->file = NULL;
}
int main() {
    Directory dir;
    dir.file = NULL;
    int choice;
    do {
        printf("\nFile Allocation Simulation Menu:\n");
        printf("1. Create File\n");
        printf("2. Display File\n");
        printf("3. Delete File\n");
        printf("4. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);
        switch (choice) {
            case 1: {
                int size;
                printf("Enter the number of blocks: ");
                scanf("%d", &size);
                int data[size];
                printf("Enter the data for each block: ");
                for (int i = 0; i < size; i++) {
                    scanf("%d", &data[i]);
                }
                create_file(&dir, data, size);
                break;
            }
            case 2:
                display_file(dir.file);
                break;
            case 3:
                delete_file(&dir);
                break;
            case 4:
                delete_file(&dir); // Clean up before exit
                printf("Exiting...\n");
                break;
            default:
                printf("Invalid choice. Please enter a number between 1 and 4.\n");
        }
    } while (choice != 4);
    return 0;
}
