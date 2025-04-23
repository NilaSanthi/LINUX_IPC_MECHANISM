#include <stdio.h>
#include <stdlib.h>
#include "ipc_dbus.h"

int main(int argc, char **argv) {
    if (argc < 2) {
        fprintf(stderr, "Usage: %s <name>\n", argv[0]);
        return 1;
    }

    DBusConnection *conn;
    char *name = argv[1];

    // Connect to DBus
    conn = dbus_connect_to_bus();
    if (conn == NULL) return 1;

    // Send message to the server
    dbus_send_message(conn, name);

    // Clean up
    dbus_connection_unref(conn);
    return 0;
}
