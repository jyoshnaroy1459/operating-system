#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <errno.h>
#include <string.h>

#define BUFFER_SIZE 1024

void create_and_write_file(const char *filename, const char *content) {
    // Create and open a file with read-write permissions
    int fd = open(filename, O_WRONLY | O_CREAT | O_TRUNC, S_IRUSR | S_IWUSR);
    if (fd < 0) {
        perror("Error opening file for writing");
        exit(EXIT_FAILURE);
    }

    // Write content to the file
    ssize_t bytes_written = write(fd, content, strlen(content));
    if (bytes_written < 0) {
        perror("Error writing to file");
        close(fd);
        exit(EXIT_FAILURE);
    }

    printf("Written %ld bytes to '%s'.\n", (long)bytes_written, filename);

    // Close the file
    if (close(fd) < 0) {
        perror("Error closing file");
        exit(EXIT_FAILURE);
    }
}

void read_file(const char *filename) {
    // Open the file for reading
    int fd = open(filename, O_RDONLY);
    if (fd < 0) {
        perror("Error opening file for reading");
        exit(EXIT_FAILURE);
    }

    char buffer[BUFFER_SIZE];
    ssize_t bytes_read;

    // Read from the file
    while ((bytes_read = read(fd, buffer, sizeof(buffer) - 1)) > 0) {
        buffer[bytes_read] = '\0'; // Null-terminate the buffer
        printf("Read: %s", buffer);
    }

    if (bytes_read < 0) {
        perror("Error reading from file");
        close(fd);
        exit(EXIT_FAILURE);
    }

    // Close the file
    if (close(fd) < 0) {
        perror("Error closing file");
        exit(EXIT_FAILURE);
    }
}

void get_file_info(const char *filename) {
    struct stat file_info;

    // Get file information
    if (stat(filename, &file_info) < 0) {
        perror("Error getting file information");
        exit(EXIT_FAILURE);
    }

    printf("File size: %ld bytes\n", (long)file_info.st_size);
    printf("File permissions: %o\n", file_info.st_mode & (S_IRWXU | S_IRWXG | S_IRWXO));
}

int main() {
    const char *filename = "example.txt";
    const char *content = "This is a sample text for file management demonstration.\n";

    // Create and write to the file
    create_and_write_file(filename, content);

    // Read from the file
    printf("\nReading file contents:\n");
    read_file(filename);

    // Get file information
    get_file_info(filename);

    return 0;
}

