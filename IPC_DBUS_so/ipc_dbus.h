#ifndef IPC_DBUS_H
#define IPC_DBUS_H

#include <dbus/dbus.h>

// DBus service name, object path, and interface
#define DBUS_INTERFACE "com.example.DBusExample"
#define DBUS_OBJECT_PATH "/com/example/DBusExample"
#define DBUS_METHOD "SayHello"

// Function declarations
DBusConnection* dbus_connect_to_bus();
int dbus_request_name(DBusConnection *conn);
void dbus_send_message(DBusConnection *conn, const char *message);
void dbus_handle_method_call(DBusConnection *conn);

#endif // IPC_DBUS_H
