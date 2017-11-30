
#ifndef DSOCKET_H
#define DSOCKET_H

#include <arpa/inet.h>
#include <string>

namespace Dagger {

class DNetAddr {
private:
    struct in_addr _addr;
    uint16_t _port;
public:
    DNetAddr(std::string ip, uint16_t port) : _port(port) {
        inet_aton(ip.c_str(), &this->_addr);
    }

    uint16_t GetPort() {
        return _port;
    }
};

class DSocket {

};

}

#endif /* DSOCKET_H */
