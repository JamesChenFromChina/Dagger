
#ifndef DSERVICE_H
#define DSERVICE_H

#include <utility/DUtility.hpp>

class DService {
public:
    DService(const DNetAddr &addr, DProtocolBase *protocol);
    virtual void Run() = 0;
};


#endif /* DSERVICE_H */
