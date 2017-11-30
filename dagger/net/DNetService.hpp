#ifndef DNETSERVICE_H
#define DNETSERVICE_H

#include "dagger/system/DSocket.hpp"
#include "dagger/net/DProtocol.hpp"

namespace Dagger
{
class DNetService
{
   private:
    DNetAddr _addr;
    DProtocolBase *_protocol;
   public:
    DNetService(const DNetAddr &addr, DProtocolBase *protocol);
    void Run();
};
}

#endif /* DNETSERVICE_H */
