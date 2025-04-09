//
// Created by universe on 2025/3/25.
//

#ifndef RTC_TEST_RTCMANAGER_H
#define RTC_TEST_RTCMANAGER_H

#include "rtc/rtc.hpp"

#include <nlohmann/json.hpp>

#include "DataChannelListener.h"
#include "IceModel.h"
#include "WebSocketHelper.h"

using nlohmann::json;

class RtcManager {
private:
    std::string localId;
    rtc::Configuration config;
    std::unordered_map<std::string, std::shared_ptr<rtc::PeerConnection>> peerConnectionMap;
    std::unordered_map<std::string, std::shared_ptr<rtc::DataChannel>> dataChannelMap;
//    template <class T> std::weak_ptr<T> make_weak_ptr(std::shared_ptr<T> ptr) { return ptr; }
    std::shared_ptr<rtc::WebSocket> ws = std::make_shared<rtc::WebSocket>();
    std::shared_ptr<DataChannelListener> dataChannelListener = nullptr;
public:
    explicit RtcManager() = default;

    explicit RtcManager(std::string& localId);

    void setLocalId(std::string& localId);
};


#endif //RTC_TEST_RTCMANAGER_H
