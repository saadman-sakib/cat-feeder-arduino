#include "constants.h"

void feed(){
	servo.write(120);
	delay(800);
	servo.write(0);
	delay(900);
}

void setup() {
	Serial.begin(9600);
	delay(10);
	servo.attach(15);

	socket.on("test", [](String payload){
		Serial.println("");
		Serial.println("event: test");
		Serial.printf("payload: %s\n", payload.c_str());
		Serial.println("");
	});

	socket.on("feed", [](String payload){
		Serial.println("");
		Serial.println("event: feed");
		Serial.printf("payload: %s\n", payload.c_str());
		Serial.println("");

		feed();

	});

	wifiManager.autoConnect("AutoConnectAP");
    socket.begin(SOCKET_HOST, SOCKET_PORT);
    Serial.println("connected to wifi)");

}


void loop() {
	socket.loop();
	delay(10);
}


