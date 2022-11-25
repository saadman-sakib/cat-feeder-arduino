#include <Arduino.h>
#include <ESP8266WiFi.h>        // Include the Wi-Fi library
#include <ESP8266WebServer.h>
#include "CustomSocketIoClient.h"
#include "wifiManager.h"
#include "index.h"

String SSID = "ESP8266 Access Point"; // The name of the Wi-Fi network that will be created
String PASSWORD = "Sakib123";   // The password required to connect to it, leave blank for an open network

String SOCKET_HOST = "10.0.0.2";
const int SOCKET_PORT = 5000;

ESP8266WebServer server(80);
CustomSocketIoClient socket;
