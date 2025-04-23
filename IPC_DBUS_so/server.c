#include <stdio.h>
#include <stdlib.h>
#include <dbus/dbus.h>
#include "ipc_dbus.h"

int main() {
    DBusConnection *conn;
    DBusError err;
    dbus_error_init(&err);

    // Connect to the DBus session bus
    conn = dbus_connect_to_bus();
    if (conn == NULL) {
        fprintf(stderr, "Failed to connect to DBus\n");
        return 1;
    }

    // Request the name for the service
    if (!dbus_request_name(conn)) {
        fprintf(stderr, "Failed to request DBus service name\n");
        dbus_connection_unref(conn);
        return 1;
    }

    // Listen for DBus messages
    printf("Server is running. Waiting for DBus messages...\n");
    dbus_handle_method_call(conn);

    // Clean up and close DBus connection
    dbus_connection_unref(conn);
    return 0;
}
