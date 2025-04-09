//
// Created by universe on 2025/3/25.
//

#include "WebSocketHelper.h"

void WebSocketHelper::newWebSocket(const std::string &url) {
    std::promise<void> wsPromise;
    auto wsFuture = wsPromise.get_future();
    ws->onOpen([&wsPromise, this]() {
        if (this->whenOpen) {
            this->whenOpen();
        }
        wsPromise.set_value();
    });
    ws->onError([&wsPromise, this](std::string s) {
        if (this->whenError) {
            this->whenError(s);
        }
        wsPromise.set_exception(std::make_exception_ptr(std::runtime_error(s)));
    });
    ws->onClosed([this]() {
        if (this->whenClosed) {
            this->whenClosed();
        }
    });
    ws->onMessage([this](auto data) -> void {
        if (!std::holds_alternative<std::string>(data)) {
            if (this->whenBinaryMessage) {
                std::vector<std::byte> msg = std::get<std::vector<std::byte>>(data);
                this->whenBinaryMessage(msg);
            }
        } else {
            if (this->whenTextMessage) {
                std::string msg = std::get<std::string>(data);
                std::cout<< msg << std::endl;
                try {
                    this->whenTextMessage(msg);
                } catch (const std::exception& e) {
                    std::cerr << "Exception in onTextMessage: " << e.what() << std::endl;
                } catch (...) {
                    std::cerr << "Caught an unknown exception in onTextMessage" << std::endl;
                }
            }
        }
    });
    std::cout << "ws url: " << url << std::endl;
    try {
        ws->open(url);
    } catch (const std::exception& e) {
        std::cerr << "Caught: " << e.what() << std::endl;
    }
    wsFuture.get();
}
