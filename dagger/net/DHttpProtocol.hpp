#ifndef DHTTPPROTOCOL_H
#define DHTTPPROTOCOL_H

#include "DProtocol.hpp"

namespace Dagger
{
class DHttpProtocol : public DProtocol<std::string>
{
   public:
    DMsgHandlerBase *GetHandler(std::string &key) { return NULL; }
};
}

#endif /* DHTTPPROTOCOL_H */
