#include <Arduino.h>
#include <ESP8266WiFi.h>        // Include the Wi-Fi library
#include <ESP8266WebServer.h>
#include <DNSServer.h>
#include <WiFiManager.h>
#include <Servo.h>
#include "CustomSocketIoClient.h"

String SOCKET_HOST = "cat-feeder-server.onrender.com";
const int SOCKET_PORT = 443;

CustomSocketIoClient socket;
WiFiManager wifiManager;
Servo servo;
