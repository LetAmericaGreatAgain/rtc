//
// Created by universe on 2025/3/26.
//

#ifndef RTC_TEST_ICEMODEL_H
#define RTC_TEST_ICEMODEL_H

#include <string>

class IceModel {
private:
    /* parameters */
    bool _n;
    bool _m;
    std::string _s;
    int _t;
    std::string _w;
    int _x;
    bool _h;

public:
    /* 构造函数改为手动配置 */
    IceModel()
    {
        _n = false;  // 不使用 STUN
        _m = false;  // 不使用 UDP multiplex
        _s = "stun.l.google.com"; // STUN 服务器地址
        _t = 19302;   // STUN 端口
        _w = "localhost"; // WebSocket 服务器
        _x = 8000;    // WebSocket 端口
        _h = false;   // 是否显示帮助信息
    }

    /* 手动设置参数的方法 */
    void setNoStun(bool n) { _n = n; }
    void setUdpMux(bool m) { _m = m; }
    void setStunServer(const std::string& s) { _s = s; }
    void setStunPort(int t) { _t = t; }
    void setWebSocketServer(const std::string& w) { _w = w; }
    void setWebSocketPort(int x) { _x = x; }

    /* 读取参数 */
    bool noStun() const { return _n; }
    bool udpMux() const { return _m; }
    std::string stunServer() const { return _s; }
    int stunPort() const { return _t; }
    std::string webSocketServer() const { return _w; }
    int webSocketPort() const { return _x; }
};


#endif //RTC_TEST_ICEMODEL_H
