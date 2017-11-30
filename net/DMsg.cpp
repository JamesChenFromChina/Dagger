
#include "dagger/Dagger.hpp"

using namespace Dagger;

void DMsg::Visit(DConnect *com, DMsgHandlerBase *handler)
{
    handler->ProcessMsgBase(com, this);
}
