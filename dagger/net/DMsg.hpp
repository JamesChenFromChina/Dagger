
#ifndef DMSG_H
#define DMSG_H

#include "dagger/utility/DUtility.hpp"


namespace Dagger
{

class DConnect;
class DMsgHandlerBase;
class DMsg
{
   public:
    virtual void Encode(DStream *out) = 0;
    virtual void Decode(DStream *in) = 0;
    virtual void Visit(DConnect *com, DMsgHandlerBase *handler);
};

}

#endif /* DMSG_H */
