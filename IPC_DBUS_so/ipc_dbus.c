#include "ipc_dbus.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dbus/dbus.h>

DBusConnection* dbus_connect_to_bus() {
    DBusConnection *conn;
    DBusError err;
    dbus_error_init(&err);

    conn = dbus_bus_get(DBUS_BUS_SESSION, &err);
    if (dbus_error_is_set(&err)) {
        fprintf(stderr, "Connection failed: %s\n", err.message);
        dbus_error_free(&err);
        return NULL;
    }

    return conn;
}

int dbus_request_name(DBusConnection *conn) {
    DBusError err;
    dbus_error_init(&err);

    if (!dbus_bus_request_name(conn, "com.example.DBusExample", DBUS_NAME_FLAG_REPLACE_EXISTING, &err)) {
        fprintf(stderr, "Name request failed: %s\n", err.message);
        dbus_error_free(&err);
        return 0;
    }

    return 1;
}

void dbus_send_message(DBusConnection *conn, const char *message) {
    DBusMessage *msg;
    DBusMessage *reply;
    DBusError err;
    char *response;

    dbus_error_init(&err);

    msg = dbus_message_new_method_call("com.example.DBusExample", DBUS_OBJECT_PATH, DBUS_INTERFACE, DBUS_METHOD);
    if (!msg) {
        fprintf(stderr, "Message creation failed\n");
        return;
    }

    dbus_message_append_args(msg, DBUS_TYPE_STRING, &message, DBUS_TYPE_INVALID);

    reply = dbus_connection_send_with_reply_and_block(conn, msg, -1, &err);
    dbus_message_unref(msg);

    if (dbus_error_is_set(&err)) {
        fprintf(stderr, "Error sending message: %s\n", err.message);
        dbus_error_free(&err);
        return;
    }

    if (dbus_message_get_args(reply, &err, DBUS_TYPE_STRING, &response, DBUS_TYPE_INVALID)) {
        printf("Response: %s\n", response);
    } else {
        fprintf(stderr, "Failed to get reply arguments: %s\n", err.message);
        dbus_error_free(&err);
    }

    dbus_message_unref(reply);
}

void dbus_handle_method_call(DBusConnection *conn) {
    DBusMessage *msg;
    DBusMessage *reply;
    DBusError err;
    const char *input;
    char response[256];

    dbus_error_init(&err);

    while (dbus_connection_read_write_dispatch(conn, -1)) {
        msg = dbus_connection_pop_message(conn);
        if (msg == NULL) continue;

        if (dbus_message_is_method_call(msg, DBUS_INTERFACE, DBUS_METHOD)) {
            if (!dbus_message_get_args(msg, &err, DBUS_TYPE_STRING, &input, DBUS_TYPE_INVALID)) {
                fprintf(stderr, "Failed to get arguments: %s\n", err.message);
                dbus_error_free(&err);
                dbus_message_unref(msg);
                continue;
            }

            snprintf(response, sizeof(response), "Hello, %s", input);
            printf("Received input: %s\n", input);
            printf("Prepared response: %s\n", response);

            reply = dbus_message_new_method_return(msg);
            if (reply == NULL) {
                fprintf(stderr, "Failed to create reply message\n");
                dbus_message_unref(msg);
                continue;
            }

            const char *res_ptr = response;
            if (!dbus_message_append_args(reply, DBUS_TYPE_STRING, &res_ptr, DBUS_TYPE_INVALID)) {
                fprintf(stderr, "Failed to append args to reply message\n");
                dbus_message_unref(reply);
                dbus_message_unref(msg);
                continue;
            }

            printf("Argument added to reply message: %s\n", response);

            if (!dbus_connection_send(conn, reply, NULL)) {
                fprintf(stderr, "Failed to send message\n");
                dbus_message_unref(reply);
                dbus_message_unref(msg);
                continue;
            }

            printf("Message sent successfully with argument\n");

            dbus_message_unref(reply);
        }

        dbus_message_unref(msg);  // <-- ✅ THIS was the missing/faulty line before
    }
}
