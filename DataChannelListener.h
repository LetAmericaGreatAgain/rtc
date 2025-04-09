//
// Created by universe on 2025/3/26.
//

#ifndef RTC_TEST_DATACHANNELLISTENER_H
#define RTC_TEST_DATACHANNELLISTENER_H


#include <memory>

#include "rtc/rtc.hpp"

class DataChannelListener {
private:
    void (*onOpen)() = nullptr;

    void (*onClosed)() = nullptr;

    void (*onTextMessage)(const char *) = nullptr;

    void (*onBinaryMessage)(const unsigned char *, long long length) = nullptr;

public:
    DataChannelListener() = default;

    void setOnOpen(void (*callback)()) { onOpen = callback; }

    void setOnClosed(void (*callback)()) { onClosed = callback; }

    void setOnTextMessage(void (*callback)(const char *)) { onTextMessage = callback; }

    void setOnBinaryMessage(void (*callback)(const unsigned char *, long long length)) { onBinaryMessage = callback; }

    void triggerOnOpen() const { if (onOpen) onOpen(); }

    void triggerOnClosed() { if (onClosed) onClosed(); }

    void triggerOnTextMessage(const char *msg) { if (onTextMessage) onTextMessage(msg); }

    void triggerOnBinaryMessage(const unsigned char *data, const long long length) { if (onBinaryMessage) onBinaryMessage(data, length); }

    void listen(std::shared_ptr<rtc::DataChannel> dc, std::shared_ptr<DataChannelListener> self) {
        dc->onOpen([self]() -> void {
            self->triggerOnOpen();
        });
        dc->onClosed([self]() {
            self->triggerOnClosed();
        });
        dc->onMessage([self](rtc::message_variant data) -> void {
            if (std::holds_alternative<std::string>(data)) {
                std::string msg = std::get<std::string>(data);
                self->triggerOnTextMessage(msg.c_str());
            } else {
                std::vector<std::byte> msg = std::get<std::vector<std::byte>>(data);
                self->triggerOnBinaryMessage(reinterpret_cast<const unsigned char*>(msg.data()), msg.size());
            }
        });
    }

    class Builder {
    private:
        std::unique_ptr<DataChannelListener> listener = std::make_unique<DataChannelListener>();

    public:
        Builder &withOnOpen(void (*callback)()) {
            listener->setOnOpen(callback);
            return *this;
        }

        Builder &withOnClosed(void (*callback)()) {
            listener->setOnClosed(callback);
            return *this;
        }

        Builder &withOnTextMessage(void (*callback)(const char *)) {
            listener->setOnTextMessage(callback);
            return *this;
        }

        Builder &withOnBinaryMessage(void (*callback)(const unsigned char *, long long length)) {
            listener->setOnBinaryMessage(callback);
            return *this;
        }

        std::unique_ptr<DataChannelListener> build() {
            return std::move(listener);
        }
    };
};


#endif //RTC_TEST_DATACHANNELLISTENER_H
