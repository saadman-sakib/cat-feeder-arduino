#include <Arduino.h>
#include <WebSocketsClient.h>
#include <SocketIOclient.h>
#include <sstream>
#include <map>

class CustomSocketIoClient : public SocketIOclient {
private:
    std::map <String, std::function<void(String)>> _callback_functions;

    String _str_to_STR(std::string str){
        String s="";
        for(auto x: str){
            s += x;
        }
        return s;
    }

    std::pair<String, String> _parse_str(String str) {

        std::string s="";

        for(auto x: str){
            s.push_back(x);
        }

        if (s.size() < 4) return { "null","null" };
        s = s.substr(2, s.size() - 4);

        std::string delimiter = "\",\"";

        size_t pos = 0;
        std::string token;
        std::vector<std::string> tokens;

        while ((pos = s.find(delimiter)) != std::string::npos) {
            token = s.substr(0, pos);
            tokens.push_back(token);
            s.erase(0, pos + delimiter.length());
        }
        tokens.push_back(s);
        if (tokens.size() == 2) return { _str_to_STR(tokens[0]), _str_to_STR(tokens[1]) };
        return { "null","null" };
    }



protected:
    virtual void runIOCbEvent(socketIOmessageType_t type, uint8_t* payload, size_t length) {
        
        std::pair<String, String> event_payload = _parse_str(String((char *)payload));
        String event = event_payload.first;
        String payload_only = event_payload.second;

        switch (type) {
        case sIOtype_DISCONNECT:
            Serial.printf("[IOc] Disconnected!\n");
            break;
        case sIOtype_CONNECT:
            Serial.printf("[IOc] Connected to url: %s:%d\n", this->_host.c_str(), this->_port);
            this->send(sIOtype_CONNECT, "/");
            break;
        case sIOtype_EVENT:
            Serial.printf("[IOc] got event: %s\n", payload);

            if (this->_callback_functions.count(event) > 0) {
                this->_callback_functions[event](payload_only);
            }

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
    void begin(String SOCKET_HOST, int port) {
        SocketIOclient::begin(SOCKET_HOST, port, "/socket.io/?EIO=4");
    }

    void emit(String event, String payload) {
        String serialized = "[\"" + event + "\", \"" + payload + "\"]";
        SocketIOclient::sendEVENT(serialized);
    }

    void on(String event, std::function<void(String)> func) {
        this->_callback_functions[event] = func;
    }

    

};