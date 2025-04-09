//
// Created by universe on 2025/3/31.
//

#ifndef RTC_TEST_RTCHELPER_H
#define RTC_TEST_RTCHELPER_H
struct IceConfig {
    int noStun;           // 是否禁用 STUN
    const char* stunServer;  // STUN 服务器地址（固定长度字符串）
    int stunPort;     // STUN 端口
    int udpMux;           // 是否启用 UDP 多路复用
    const char* webSocketServer; // WebSocket 服务器地址
    int webSocketPort;    // WebSocket 端口
};

struct DataChannelConfig {
    void (*onOpen)();
    void (*onClosed)();
    void (*onTextMessage)(const char *);
    void (*onBinaryMessage)(const unsigned char *, long long length);
};

extern "C" void createRtcContext(const char* localId, int logLevel, struct IceConfig* iceConfig, struct DataChannelConfig* dataChannelConfig);

extern "C" void createPeerConnection(const char* remoteId);

extern "C" void createDataChannel(const char* remoteId, const char* label);

extern "C" void sendTextMessageByDataChannel(const char* remoteId, const char* msg);

extern "C" void sendBinaryMessageByDataChannel(const char* remoteId, unsigned char* msg, long long length);

extern "C" void destroyRtcContext(void (*onClosed)());
#endif //RTC_TEST_RTCHELPER_H
