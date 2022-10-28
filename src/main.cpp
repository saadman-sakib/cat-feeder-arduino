#include <Arduino.h>
#include <ESP8266WiFi.h>        // Include the Wi-Fi library
#include <ESP8266WebServer.h>
#include <SocketIoClient.h>
#include "index.h"
#include "wifiManager.h"
#include "server.h"
#include "socketManager.h"


String SSID = "ESP8266 Access Point"; // The name of the Wi-Fi network that will be created
String PASSWORD = "Sakib123";   // The password required to connect to it, leave blank for an open network
String wifi_ssid = "";
String wifi_password = "";

const char* SOCKET_HOST = "10.0.0.2";
const int SOCKET_PORT = 8080;
const char* SOCKET_PATH = "/";


ESP8266WebServer server(80);
WiFiClient client;
SocketIoClient socket;


void handleRoot() {
	server.send(200, "text/html", index_html);
}

// connects with wifi after login credentials are given
void handleLogin() {
	wifi_ssid = server.arg(0);
	wifi_password = server.arg(1);

	Serial.println(wifi_ssid);
	Serial.println(wifi_password);

	bool res = external_wifi_login(wifi_ssid, wifi_password);

	if (res){
		server.send(200, "text/html", "connected");
		socket_setup(socket, SOCKET_HOST, SOCKET_PORT, SOCKET_PATH);
    	socket.emit("test1", "GGWP");
		socket.loop();
	}
	else{
		server.send(200, "text/html", "couldn't connect");
	}
}



void setup() {
	Serial.begin(9600);
	delay(10);
	Serial.println('\n');

	WiFi.softAP(SSID, PASSWORD);             // Start the access point

	Serial.print("Access Point \"");
	Serial.print(SSID);
	Serial.println("\" started");

	Serial.print("IP address:\t");
	Serial.println(WiFi.softAPIP());         // Send the IP address of the ESP8266 to the computer

	server.on("/index", handleRoot);
	server.on("/login", handleLogin);

	server.begin();
}


void loop() {
	server.handleClient();
	socket.loop();
}

