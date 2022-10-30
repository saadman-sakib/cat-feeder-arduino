#include <Arduino.h>
#include <WebSocketsClient.h>
#include <SocketIOclient.h>

class CustomSocketIoClient : public SocketIOclient {
private:
protected:
    virtual void runIOCbEvent(socketIOmessageType_t type, uint8_t * payload, size_t length) {
        switch (type) {
        case sIOtype_DISCONNECT:
            Serial.printf("[IOc] Disconnected!\n");
            break;
        case sIOtype_CONNECT:
            Serial.printf("[IOc] Connected to url: %s\n", payload);
            this->send(sIOtype_CONNECT, "/");
            this->sendEVENT("[\"test1\", \"GGWP BOIS\"]");
            this->emit("test1", "Helloooooooo");
            break;
        case sIOtype_EVENT:
            Serial.printf("[IOc] get event: %s\n", payload);

            break;
        case sIOtype_ACK:
            Serial.printf("[IOc] get ack: %u\n", length);
            hexdump(payload, length);
            break;
        case sIOtype_ERROR:
            Serial.printf("[IOc] get error: %u\n", length);
            hexdump(payload, length);
            break;
        case sIOtype_BINARY_EVENT:
            Serial.printf("[IOc] get binary: %u\n", length);
            hexdump(payload, length);
            break;
        case sIOtype_BINARY_ACK:
            Serial.printf("[IOc] get binary ack: %u\n", length);
            hexdump(payload, length);
            break;
        }
    }

public:
    void begin(String SOCKET_HOST, int port){
        SocketIOclient::begin(SOCKET_HOST, port, "/socket.io/?EIO=4");
    }

    void emit(String event, String payload){
        String serialized = "[\"" + event + "\", \"" + payload + "\"]";
        SocketIOclient::sendEVENT(serialized);
    }

};