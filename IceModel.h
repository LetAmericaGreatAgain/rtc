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
    
    IceModel()
    {
        _n = false; 
        _m = false;  
        _s = "stun.l.google.com"; 
        _t = 19302;   
        _w = "localhost";
        _x = 8000;    
        _h = false;   
    }

    
    void setNoStun(bool n) { _n = n; }
    void setUdpMux(bool m) { _m = m; }
    void setStunServer(const std::string& s) { _s = s; }
    void setStunPort(int t) { _t = t; }
    void setWebSocketServer(const std::string& w) { _w = w; }
    void setWebSocketPort(int x) { _x = x; }

    
    bool noStun() const { return _n; }
    bool udpMux() const { return _m; }
    std::string stunServer() const { return _s; }
    int stunPort() const { return _t; }
    std::string webSocketServer() const { return _w; }
    int webSocketPort() const { return _x; }
};


#endif //RTC_TEST_ICEMODEL_H
