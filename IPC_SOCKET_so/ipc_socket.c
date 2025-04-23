// ipc_socket.c
#include <stdio.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/un.h>
#include <unistd.h>

#define SERVER_SOCK_FILE "/tmp/server_socket"
#define CLIENT_SOCK_FILE "/tmp/client_socket"

// Function to create and bind a Unix domain socket (server side)
int create_server_socket() {
    int fd;
    struct sockaddr_un addr;

    if ((fd = socket(PF_UNIX, SOCK_DGRAM, 0)) < 0) {
        perror("socket");
        return -1;
    }

    memset(&addr, 0, sizeof(addr));
    addr.sun_family = AF_UNIX;
    strcpy(addr.sun_path, SERVER_SOCK_FILE);

    unlink(SERVER_SOCK_FILE);  // Remove any pre-existing socket
    if (bind(fd, (struct sockaddr *)&addr, sizeof(addr)) < 0) {
        perror("bind");
        close(fd);
        return -1;
    } else {
    printf("Server bound to %s\n", SERVER_SOCK_FILE);
    }

    return fd;
}

// Function to receive a message (server side)
ssize_t receive_message(int fd, char *buff, size_t len) {
    struct sockaddr_un from;
    socklen_t fromlen = sizeof(from);
    return recvfrom(fd, buff, len, 0, (struct sockaddr *)&from, &fromlen);
}

// Function to create a client-side socket and connect to the server
int create_client_socket() {
    int fd;
    struct sockaddr_un addr;

    if ((fd = socket(PF_UNIX, SOCK_DGRAM, 0)) < 0) {
        perror("socket");
        return -1;
    } else {
	printf("client socket creation success");    
    }

    memset(&addr, 0, sizeof(addr));
    addr.sun_family = AF_UNIX;
    strcpy(addr.sun_path, SERVER_SOCK_FILE);  // Connect to the server's socket

    if (connect(fd, (struct sockaddr *)&addr, sizeof(addr)) == -1) {
        perror("connect");
        close(fd);
        return -1;
    }else {
	    printf("\nClient socket connect success");
    }

    return fd;
}

// Function to send a message (client side)
int send_message(int fd, const char *message) {
    if (send(fd, message, strlen(message) + 1, 0) == -1) {
        perror("send");
        close(fd);
        return -1;
    }
    return 0;
}

