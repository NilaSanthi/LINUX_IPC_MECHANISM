// client.c
#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include "ipc_socket.h"

int main() {
    const char *message = "REML-SOC-Meta_uml";

    // Create client-side socket and connect to the server
    int fd = create_client_socket();
    if (fd < 0) {
        printf("Failed to create client socket\n");
        return 1;
    }

    // Send the message to the server
    if (send_message(fd, message) == 0) {
        printf("Message sent: %s\n", message);
    } else {
        printf("Failed to send message\n");
    }

    // Close the client socket
    close(fd);
    return 0;
}

