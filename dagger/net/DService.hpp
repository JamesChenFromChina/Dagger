
#ifndef DSERVICE_H
#define DSERVICE_H

#include <utility/DUtility.hpp>

class DService {
public:
    virtual void Run() = 0;
};

class DHttpService : public DService {
    uint16_t _port;
public:
    DHttpService(uint16_t port) : _port(port) {
    }
    virtual vod Run();
};


#endif /* DSERVICE_H */
