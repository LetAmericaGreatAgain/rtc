#include <iostream>

#include <random>
#include <chrono>
#include "lib/RtcHelper.h"

std::string randomId(size_t length) {
    using std::chrono::high_resolution_clock;
    static thread_local std::mt19937 rng(
            static_cast<unsigned int>(high_resolution_clock::now().time_since_epoch().count()));
    static const std::string characters(
            "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz");
    std::string id(length, '0');
    std::uniform_int_distribution<int> uniform(0, int(characters.size() - 1));
    std::generate(id.begin(), id.end(), [&]() { return characters.at(uniform(rng)); });
    return id;
}

int main() {
    IceConfig iceConfig;
    iceConfig.noStun = true;
    iceConfig.stunServer = "stun.l.google.com";
    iceConfig.stunPort = 19302;
    iceConfig.udpMux = true;
    iceConfig.webSocketServer = "127.0.0.1";
    iceConfig.webSocketPort = 8000;
    DataChannelConfig dataChannelConfig;
    dataChannelConfig.onOpen = [](){
        std::cout << "datachannel open" << std::endl;
    };
    dataChannelConfig.onTextMessage = [](const char* data) {
        std::cout << std::string(data) << std::endl;
    };
    std::string randomString = randomId(4);
//    const char* localId = randomString.c_str();
    const char* localId = "abcd";
    createRtcContext(localId, 4, &iceConfig, &dataChannelConfig);
    return 0;
}
