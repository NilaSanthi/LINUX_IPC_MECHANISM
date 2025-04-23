CC = gcc
CFLAGS = -Wall -g $(shell pkg-config --cflags dbus-1)
LDFLAGS = $(shell pkg-config --libs dbus-1)

SRCS = ipc_dbus.c server.c client.c
OBJS = $(SRCS:.c=.o)

all: server client

server: server.o ipc_dbus.o
	$(CC) -o $@ $^ $(LDFLAGS)

client: client.o ipc_dbus.o
	$(CC) -o $@ $^ $(LDFLAGS)

%.o: %.c ipc_dbus.h
	$(CC) $(CFLAGS) -c $<

clean:
	rm -f *.o server client
