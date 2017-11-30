#ifndef DNETCONNECTION_H
#define DNETCONNECTION_H

#include "dagger/net/DMsg.hpp"
#include "dagger/system/DSocket.hpp"

namespace Dagger {

/**
 *  \brief Message based connection, Used to send and recv DMsg objects.
 *
 *
 *  \author chenpeng <chenpengsmail@qq.com>
 *  \date 2017-11-30
 */
class DNetConnection {
public:
    DNetConnection(const DNetAddr &addr, DProtocolBase *protocol) {
    }
    void Send(DMsg *msg) {
    }
    DMsg *Recv() {
        return NULL;
    }
};

}

#endif /* DNETCONNECTION_H */
