#include <stdio.h>
#include <stdlib.h>
#define MAX_BLOCKS 100
#define BLOCK_SIZE 10
typedef struct Block {
    int data[BLOCK_SIZE];
} Block;
typedef struct File {
    Block* index_block[MAX_BLOCKS];
    int num_blocks;
} File;
typedef struct Directory {
    File* file;
} Directory;
Block* allocate_block(int* data, int size) {
    Block* new_block = (Block*)malloc(sizeof(Block));
    if (new_block == NULL) {
        printf("Memory allocation failed\n");
        exit(1);
    }
    for (int i = 0; i < BLOCK_SIZE && i < size; i++) {
        new_block->data[i] = data[i];
    }
    return new_block;
}
void deallocate_blocks(File* file) {
    for (int i = 0; i < file->num_blocks; i++) {
        free(file->index_block[i]);
    }
    free(file);
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
    new_file->num_blocks = (size + BLOCK_SIZE - 1) / BLOCK_SIZE;
    for (int i = 0; i < new_file->num_blocks; i++) {
        new_file->index_block[i] = allocate_block(&data[i * BLOCK_SIZE], size - i * BLOCK_SIZE);
    }
    dir->file = new_file;
}
void display_file(File* file) {
    if (file == NULL || file->num_blocks == 0) {
        printf("File does not exist\n");
        return;
    }
    printf("File content:\n");
    for (int i = 0; i < file->num_blocks; i++) {
        for (int j = 0; j < BLOCK_SIZE; j++) {
            printf("%d ", file->index_block[i]->data[j]);
        }
        printf("\n");
    }
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
                printf("Enter the number of data elements: ");
                scanf("%d", &size);
                int data[size];
                printf("Enter the data elements: ");
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
                deallocate_blocks(dir.file);
                dir.file = NULL;
                printf("File deleted.\n");
                break;
            case 4:
                deallocate_blocks(dir.file); // Clean up before exit
                printf("Exiting...\n");
                break;
            default:
                printf("Invalid choice. Please enter a number between 1 and 4.\n");
        }
    } while (choice != 4);
    return 0;
}
