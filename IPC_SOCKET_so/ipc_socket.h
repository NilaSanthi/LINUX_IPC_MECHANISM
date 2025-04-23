// ipc_socket.h

#ifndef IPC_SOCKET_H
#define IPC_SOCKET_H

// Function declarations for creating server and client sockets, sending, and receiving messages
int create_server_socket();
ssize_t receive_message(int fd, char *buff, size_t len);
int create_client_socket();
int send_message(int fd, const char *message);

#endif // IPC_SOCKET_H

