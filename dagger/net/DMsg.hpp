
#ifndef DMSG_H
#define DMSG_H

#include <dagger/Dagger.hpp>
#include "DMsgHandler.hpp"

namespace Dagger {

class DMsg {
public:
    virtual void Encode(DStream *out) = 0;
    virtual void Decode(DStream *in) = 0;
    virtual void Visit(DCommunicator *com, DMsgHandlerBase *handler) {
        handler->ProcessMsgBase(com, this);
    }
};

}

#endif /* DMSG_H */
