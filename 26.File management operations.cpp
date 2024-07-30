#include <stdio.h>
#include <stdlib.h>
#include <string.h>
void create_and_write_file(const char *filename, const char *content) {
    FILE *file = fopen(filename, "w");
    if (file == NULL) {
        perror("Error creating file");
        exit(EXIT_FAILURE);
    }
    fprintf(file, "%s", content);
    fclose(file);
    printf("File '%s' created and written successfully.\n", filename);
}

// Function to read from a file
void read_file(const char *filename) {
    FILE *file = fopen(filename, "r");
    if (file == NULL) {
        perror("Error opening file");
        exit(EXIT_FAILURE);
    }
    char buffer[256];
    printf("Contents of '%s':\n", filename);
    while (fgets(buffer, sizeof(buffer), file) != NULL) {
        printf("%s", buffer);
    }
    fclose(file);
}
void delete_file(const char *filename) {
    if (remove(filename) == 0) {
        printf("File '%s' deleted successfully.\n", filename);
    } else {
        perror("Error deleting file");
    }
}
int main() {
    const char *filename = "example.txt";
    const char *content = "This is a sample text for file management.\n";

    create_and_write_file(filename, content);
    read_file(filename);
    delete_file(filename);

    return 0;
}
