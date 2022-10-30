#include "constants.h"

void handleRoot();
void handleLogin();

void setup() {
	Serial.begin(9600);
	delay(10);
	
	start_access_point(SSID, PASSWORD);

	server.on("/", handleRoot);
	server.on("/login", handleLogin);
	server.begin();
}


void loop() {
	server.handleClient();
	socket.loop();
	delay(10);
}


void handleRoot() {
	server.send(200, "text/html", index_html);
}


void handleLogin() {
	String wifi_ssid = server.arg(0);
	String wifi_password = server.arg(1);

	bool res = external_wifi_login(wifi_ssid, wifi_password);

	if (res){
		server.send(200, "text/html", "connected");
        socket.begin(SOCKET_HOST, SOCKET_PORT);
	}
	else{
		server.send(200, "text/html", "couldn't connect");
	}
}

