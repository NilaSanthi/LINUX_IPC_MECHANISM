#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include "ipc_socket.h"

#define MAX_BUFFER_SIZE 256

int main() {
    char buffer[MAX_BUFFER_SIZE];

    // Create the server-side socket and bind it
    int server_fd = create_server_socket();
    if (server_fd < 0) {
        printf("Failed to create server socket\n");
        return 1;
    }

    printf("Server is listening...\n");

    while (1) {
        // Wait for a message from the client
        ssize_t len = receive_message(server_fd, buffer, sizeof(buffer));
        if (len < 0) {
            printf("Error receiving message\n");
            break;  // Exit on error
        }

        // Null-terminate the received message (in case it wasn't)
        buffer[len] = '\0';

        // Print the received message
        printf("Received message: %s\n", buffer);

        // Here, you could perform additional processing or send a response to the client
        // For now, we'll just continue waiting for more messages.
    }

    // Close the server socket before exiting
    close(server_fd);
    return 0;
}
