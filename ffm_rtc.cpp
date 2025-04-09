//
// Created by universe on 2025/3/27.
//

#include "ffm_rtc.h"

std::unique_ptr<RtcManager> rtcManager = nullptr;

std::atomic<int> state = 0;

void print(const char* localId, int logLevel, IceConfig* iceConfig, DataChannelConfig* dataChannelConfig) {
    std::cout << localId << std::endl;
    std::cout << std::to_string(logLevel) << std::endl;
    std::cout << iceConfig->webSocketServer << std::endl;
    dataChannelConfig->onOpen();
}

void printIceConfig(IceConfig* iceConfig) {
    std::cout << iceConfig->webSocketServer << std::endl;
}

void testDataChannelConfig(DataChannelConfig* dataChannelConfig) {
    dataChannelConfig->onOpen();
    dataChannelConfig->onTextMessage("123");
}

void createRtcContext(const char* localId, int logLevel, IceConfig* iceConfig, DataChannelConfig* dataChannelConfig) {
    std::cout << "1" << std::endl;
    int expected = 0;
    bool success = state.compare_exchange_strong(expected, 1);
    if (!success) return;
    if (localId == nullptr) return;
    if (iceConfig == nullptr) return;
    if (dataChannelConfig == nullptr) return;
    std::cout << "2" << std::endl;
    std::string id = std::string(localId);
    std::cout << "2 1" << " " << id << std::endl;
    std::make_unique<int>(3);
    std::cout << "2 1 1" << std::endl;
    rtcManager = std::make_unique<RtcManager>(); // Crash here!
    std::cout << "2 1 2" << std::endl;

}

