#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Function to create and write to a file
void create_and_write_file(const char *filename, const char *content) {
    // Open the file for writing. If the file does not exist, it will be created.
    FILE *file = fopen(filename, "w");
    if (file == NULL) {
        perror("Error creating file");
        exit(EXIT_FAILURE);
    }
    // Write the content to the file
    fprintf(file, "%s", content);
    // Close the file
    fclose(file);
    printf("File '%s' created and written successfully.\n", filename);
}

// Function to read from a file
void read_file(const char *filename) {
    // Open the file for reading
    FILE *file = fopen(filename, "r");
    if (file == NULL) {
        perror("Error opening file");
        exit(EXIT_FAILURE);
    }
    char buffer[256];
    // Print the contents of the file
    printf("Contents of '%s':\n", filename);
    while (fgets(buffer, sizeof(buffer), file) != NULL) {
        printf("%s", buffer);
    }
    // Close the file
    fclose(file);
}

// Function to delete a file
void delete_file(const char *filename) {
    // Remove the file from the filesystem
    if (remove(filename) == 0) {
        printf("File '%s' deleted successfully.\n", filename);
    } else {
        perror("Error deleting file");
    }
}

int main() {
    const char *filename = "example.txt";
    const char *content = "This is a sample text for file management.\n";

    // Create and write to the file
    create_and_write_file(filename, content);

    // Read from the file
    read_file(filename);

    // Delete the file
    delete_file(filename);

    return 0;
}
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <dirent.h>
#include <errno.h>

// Function to demonstrate the use of fcntl
void demo_fcntl(const char *filename) {
    int fd = open(filename, O_RDONLY);
    if (fd < 0) {
        perror("Error opening file with open");
        exit(EXIT_FAILURE);
    }

    int flags = fcntl(fd, F_GETFL);
    if (flags == -1) {
        perror("Error getting file flags");
        close(fd);
        exit(EXIT_FAILURE);
    }

    printf("File descriptor flags: %d\n", flags);

    // Add the O_NONBLOCK flag
    if (fcntl(fd, F_SETFL, O_NONBLOCK) == -1) {
        perror("Error setting file to non-blocking");
        close(fd);
        exit(EXIT_FAILURE);
    }
    
    printf("File descriptor set to non-blocking mode.\n");

    close(fd);
}

// Function to demonstrate the use of lseek
void demo_lseek(const char *filename) {
    int fd = open(filename, O_RDONLY);
    if (fd < 0) {
        perror("Error opening file with open");
        exit(EXIT_FAILURE);
    }

    off_t offset = lseek(fd, 0, SEEK_END);
    if (offset == -1) {
        perror("Error seeking to end of file");
        close(fd);
        exit(EXIT_FAILURE);
    }

    printf("File size: %ld bytes\n", (long)offset);

    close(fd);
}

// Function to demonstrate the use of stat
void demo_stat(const char *filename) {
    struct stat file_info;

    if (stat(filename, &file_info) == -1) {
        perror("Error getting file status");
        exit(EXIT_FAILURE);
    }

    printf("File size: %ld bytes\n", (long)file_info.st_size);
    printf("File permissions: %o\n", file_info.st_mode & (S_IRWXU | S_IRWXG | S_IRWXO));
}
void demo_opendir_readdir(const char *directory) {
    DIR *dir = opendir(directory);
    if (dir == NULL) {
        perror("Error opening directory");
        exit(EXIT_FAILURE);
    }
    struct dirent *entry;
    printf("Contents of directory '%s':\n", directory);
    while ((entry = readdir(dir)) != NULL) {
        printf("%s\n", entry->d_name);
    }
    closedir(dir);
}
int main() {
    const char *filename = "example.txt";
    const char *directory = "."; 
    demo_fcntl(filename);
    demo_lseek(filename);
    demo_stat(filename);
    demo_opendir_readdir(directory);

    return 0;
}

