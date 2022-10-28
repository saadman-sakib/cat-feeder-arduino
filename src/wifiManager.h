#include <Arduino.h>
#include <ESP8266WiFi.h>        // Include the Wi-Fi library
#include <ESP8266WebServer.h>

bool external_wifi_login(String ssid, String password) {
    delay(10);
    Serial.println('\n');
    WiFi.begin(ssid, password);             // Connect to the network
    Serial.print("Connecting to " + ssid + " ...");

    int i = 0;
    while (WiFi.status() != WL_CONNECTED) { // Wait for the Wi-Fi to connect
        delay(1000);
        Serial.print(++i); Serial.print(' ');

        if (i > 40) {
            Serial.println("Cannot Connect!!!");
            return 0;
        }
    }


    Serial.println('\n');
    Serial.println("Connection established!");
    Serial.print("IP address:\t");
    Serial.println(WiFi.localIP());         // Send the IP address of the ESP8266 to the computer

    return 1;
}