#include <Arduino.h>
#include <ESP8266WiFi.h>        
#include <ESP8266WebServer.h>
#include <SocketIoClient.h>

void socket_connected(const char* payload, size_t length) {
    Serial.println("Socket.IO Connected!");
    Serial.println(payload);
}

void socket_event(const char* payload, size_t length) {
    Serial.print("got message: ");
    Serial.println(payload);
}

void socket_test(const char* payload, size_t length) {
    Serial.print("test message:  ");
    Serial.println(payload);
}

void socket_setup(SocketIoClient &socket, const char* host, int port, const char* path) {
    socket.on("connect", socket_connected);
    socket.on("event", socket_event);
    socket.on("test", socket_test);
    socket.begin(host, port, path);
}

