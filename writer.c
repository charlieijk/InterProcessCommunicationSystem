#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <unistd.h>
#include <string.h>

#define PIPE_NAME "my_pipe"
#define BUFFER_SIZE 1024

int main() {
    FILE *file;
    int pipe_fd;
    char buffer[BUFFER_SIZE];

    // Open the file for reading
    file = fopen("sensor_data.csv", "r");
    if (file == NULL) {
        perror("Debug 1: Failed to open file");
        return EXIT_FAILURE;
    }
    // Remove existing pipe if it exists
    unlink(PIPE_NAME);
    
    // Create the named pipe
    if (mkfifo(PIPE_NAME, 0666) == -1) {
        perror("Failed to create pipe");
        fclose(file);
        return EXIT_FAILURE;
    }

    // Open the pipe for writing (this will block until the reader connects)
    printf("Waiting for reader to connect...\n");
    pipe_fd = open(PIPE_NAME, O_WRONLY);
    if (pipe_fd == -1) {
        perror("Failed to open pipe");
        fclose(file);
        unlink(PIPE_NAME);
        return EXIT_FAILURE;
    }

    // Read the file line by line and write to the pipe
    while (fgets(buffer, BUFFER_SIZE, file) != NULL) {
        if (write(pipe_fd, buffer, strlen(buffer)) == -1) {
            perror("Failed to write to pipe");
            break;
        }
    }

    // Clean up
    fclose(file);
    close(pipe_fd);
    unlink(PIPE_NAME);

    return EXIT_SUCCESS;
}