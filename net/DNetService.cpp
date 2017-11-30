
#include <dagger/net/DNet.hpp>

namespace Dagger {
    DNetService::DNetService(const DNetAddr &addr, DProtocolBase *protocol) : _addr(addr), _protocol(protocol) {
        DNetConnection *connect = DCommunicator::GetInstance()->BuildConnection(addr);
    }

    void DNetService::Run() {

    }
}
