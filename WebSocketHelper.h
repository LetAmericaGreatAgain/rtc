//
// Created by universe on 2025/3/25.
//

#ifndef RTC_TEST_WEBSOCKETHELPER_H
#define RTC_TEST_WEBSOCKETHELPER_H

#include <functional>
#include <utility>
#include <vector>
#include <string>
#include <variant>

#include "rtc/rtc.hpp"

class WebSocketHelper {
private:
    std::shared_ptr<rtc::WebSocket> ws = nullptr;
    std::function<void()> whenOpen = nullptr;
    std::function<void()> whenClosed = nullptr;
    std::function<void(std::string error)> whenError = nullptr;
    std::function<void(std::vector<std::byte>)> whenBinaryMessage = nullptr;
    std::function<void(std::string)> whenTextMessage = nullptr;
public:
    void newWebSocket(const std::string& url);
public:
    
    class Builder {
    private:
        std::shared_ptr<rtc::WebSocket> ws;
        std::function<void()> whenOpen;
        std::function<void()> whenClosed;
        std::function<void(std::string)> whenError;
        std::function<void(std::vector<std::byte>)> whenBinaryMessage;
        std::function<void(std::string)> whenTextMessage;

    public:
        Builder() = default;

        explicit Builder(const std::shared_ptr<rtc::WebSocket> &ws) : ws(ws) {}

        
        Builder& setWebSocket(std::shared_ptr<rtc::WebSocket> &websocket) {
            ws = websocket;
            return *this;
        }

        
        Builder& onOpen(std::function<void()> callback) {
            whenOpen = std::move(callback);
            return *this;
        }

       
        Builder& onClosed(std::function<void()> callback) {
            whenClosed = std::move(callback);
            return *this;
        }

        
        Builder& onError(std::function<void(std::string)> callback) {
            whenError = std::move(callback);
            return *this;
        }

        
        Builder& onBinaryMessage(std::function<void(std::vector<std::byte>)> callback) {
            whenBinaryMessage = std::move(callback);
            return *this;
        }

        
        Builder& onTextMessage(std::function<void(std::string)> callback) {
            whenTextMessage = std::move(callback);
            return *this;
        }

        
        std::unique_ptr<WebSocketHelper> build() {
            std::unique_ptr<WebSocketHelper> helper = std::make_unique<WebSocketHelper>();
            helper->ws = ws;
            helper->whenOpen = std::move(whenOpen);
            helper->whenClosed = std::move(whenClosed);
            helper->whenError = std::move(whenError);
            helper->whenBinaryMessage = std::move(whenBinaryMessage);
            helper->whenTextMessage = std::move(whenTextMessage);
            return helper;
        }
    };
};


#endif //RTC_TEST_WEBSOCKETHELPER_H
