
#ifndef DMSGHANDLER_H
#define DMSGHANDLER_H

#include "DMsg.hpp"
#include "DVisitor.hpp"

template<typename MsgType>
class DMsgHandler {
public:
    virtual void ProcessMsg(MsgType *msg) = 0;
};


#endif /* DMSGHANDLER_H */
