#include <stdio.h>
#include <stdlib.h>

#define MAX_RECORDS 100
#define RECORD_SIZE 50

typedef struct File {
    char records[MAX_RECORDS][RECORD_SIZE];
    int num_records;
} File;

typedef struct Directory {
    File* file;
} Directory;

void create_file(Directory* dir, int num_records) {
    if (num_records <= 0 || num_records > MAX_RECORDS) {
        printf("Invalid number of records\n");
        return;
    }

    File* new_file = (File*)malloc(sizeof(File));
    if (new_file == NULL) {
        printf("Memory allocation failed\n");
        exit(1);
    }

    new_file->num_records = num_records;
    for (int i = 0; i < num_records; i++) {
        printf("Enter record %d: ", i + 1);
        scanf(" %[^\n]", new_file->records[i]); // Read a line of input
    }

    dir->file = new_file;
}

void display_file(File* file) {
    if (file == NULL || file->num_records == 0) {
        printf("File does not exist or is empty\n");
        return;
    }

    printf("File contents:\n");
    for (int i = 0; i < file->num_records; i++) {
        printf("Record %d: %s\n", i + 1, file->records[i]);
    }
}

void delete_file(Directory* dir) {
    if (dir->file == NULL) {
        printf("No file to delete\n");
        return;
    }

    free(dir->file);
    dir->file = NULL;
    printf("File deleted.\n");
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
        getchar(); 

        switch (choice) {
            case 1: {
                int num_records;
                printf("Enter the number of records: ");
                scanf("%d", &num_records);
                getchar(); // To consume the newline character left in buffer
                create_file(&dir, num_records);
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
