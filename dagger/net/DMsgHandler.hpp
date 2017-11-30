
#ifndef DMSGHANDLER_H
#define DMSGHANDLER_H

#include "DCommunicator.hpp"
#include "DVisitor.hpp"

namespace Dagger {

class DMsg;

class DMsgHandlerBase {
public:
    virtual void ProcessMsgBase(DCommunicator *com, DMsg *msg) = 0;
};

template<typename MsgType>
class DMsgHandler {
public:
    virtual void ProcessMsgBase(DCommunicator *com, DMsg *msg) {
        ProcessMsg(com, (MsgType *)msg);
    }

    virtual void ProcessMsg(DCommunicator *com, MsgType *msg) = 0;
};

}

#endif /* DMSGHANDLER_H */
