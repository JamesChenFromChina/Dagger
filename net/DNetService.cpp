
#include <dagger/net/net.hpp>

namespace Dagger {
    DNetService::DNetService(const DNetAddr &addr, DProtocolBase *protocol) {
        DNetConnect connect(addr, protocol);
        DCommunicator::GetInstance()->RegistSocket(connect->GetSocket());
    }

    void DNetService::Run() {

    }
}
