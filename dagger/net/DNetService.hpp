
#ifndef DNETSERVICE_H
#define DNETSERVICE_H

#include "dagger/system/DSocket.hpp"
#include "dagger/net/DProtocol.hpp"

namespace Dagger
{
class DNetService
{
   public:
    DNetService(const DNetAddr &addr, DProtocolBase *protocol);
    void Run();
};
}
#endif /* DNETSERVICE_H */
