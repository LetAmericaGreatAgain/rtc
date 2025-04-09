//
// Created by universe on 2025/3/27.
//

#ifndef RTC_TEST_FFM_RTC_H
#define RTC_TEST_FFM_RTC_H

#include "RtcManager.h"

struct IceConfig {
    int noStun;          
    const char* stunServer;  
    int stunPort;     
    int udpMux;        
    const char* webSocketServer; 
    int webSocketPort; 
};

struct DataChannelConfig {
    void (*onOpen)() = nullptr;
    void (*onClosed)() = nullptr;
    void (*onTextMessage)(const char *) = nullptr;
    void (*onBinaryMessage)(const unsigned char *, long long length) = nullptr;
};

extern std::unique_ptr<RtcManager> rtcManager;

extern std::atomic<int> state;

extern "C" __declspec(dllexport) void print(const char* localId, int logLevel, IceConfig* iceConfig, DataChannelConfig* dataChannelConfig);

extern "C" __declspec(dllexport) void printIceConfig(IceConfig* iceConfig);

extern "C" __declspec(dllexport) void testDataChannelConfig(DataChannelConfig* dataChannelConfig);

extern "C" __declspec(dllexport) void createRtcContext(const char* localId, int logLevel, IceConfig* iceConfig, DataChannelConfig* dataChannelConfig);

#endif //RTC_TEST_FFM_RTC_H
