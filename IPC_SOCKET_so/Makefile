CC = gcc
CFLAGS = -Wall -fPIC
LDFLAGS = -shared
LIB_NAME = libipc_socket.so
SERVER_BIN = server
CLIENT_BIN = client

# All target
all: $(LIB_NAME) $(SERVER_BIN) $(CLIENT_BIN)

# Create shared library
$(LIB_NAME): ipc_socket.o
	$(CC) $(LDFLAGS) -o $@ ipc_socket.o

# Create object file from source
ipc_socket.o: ipc_socket.c
	$(CC) $(CFLAGS) -o $@ -c ipc_socket.c

# Compile server
$(SERVER_BIN): server.c $(LIB_NAME)
	$(CC) $(CFLAGS) -o $@ server.c -L. -lipc_socket

# Compile client
$(CLIENT_BIN): client.c $(LIB_NAME)
	$(CC) $(CFLAGS) -o $@ client.c -L. -lipc_socket

# Run server with LD_LIBRARY_PATH set
run-server: $(SERVER_BIN)
	LD_LIBRARY_PATH=.:$$LD_LIBRARY_PATH ./$(SERVER_BIN)

# Run client with LD_LIBRARY_PATH set
run-client: $(CLIENT_BIN)
	LD_LIBRARY_PATH=.:$$LD_LIBRARY_PATH ./$(CLIENT_BIN)

# Clean up
clean:
	rm -f $(LIB_NAME) $(SERVER_BIN) $(CLIENT_BIN) ipc_socket.o

.PHONY: all clean run-server run-client
