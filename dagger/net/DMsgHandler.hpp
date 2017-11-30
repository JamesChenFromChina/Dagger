
#ifndef DMSGHANDLER_H
#define DMSGHANDLER_H

#include "DVisitor.hpp"

namespace Dagger {

class DMsgHandlerBase {
public:
    virtual void ProcessMsgBase(DConnect *con, DMsg *msg) = 0;
};

template<typename MsgType>
class DMsgHandler {
public:
    virtual void ProcessMsgBase(DConnect *com, DMsg *msg) {
        ProcessMsg(com, (MsgType *)msg);
    }

    virtual void ProcessMsg(DConnect *com, MsgType *msg) = 0;
};

}

#endif /* DMSGHANDLER_H */
