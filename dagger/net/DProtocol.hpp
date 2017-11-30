#ifndef DPROTOCOL_H
#define DPROTOCOL_H

#include <dagger/utility/DObjFactory.hpp>

namespace Dagger
{
class DProtocolBase
{
   public:
    virtual std::string &&GetProtocolName()
    {
        return ::std::move(std::string(""));
    }
};

template <typename KeyType>
class DProtocol : public DProtocolBase
{
   public:
    template <typename MsgType>
    void Regist(KeyType key, DObjFactoryBase<MsgType> *factory)
    {
    }
};

template <typename KeyType, typename MsgType, typename HandlerType>
class DMsgRegister
{
   public:
    DMsgRegister(KeyType key, DProtocolBase *proto)
    {
        DProtocol<KeyType> *protoImpl =
            dynamic_cast<DProtocol<KeyType> *>(proto);
        DObjFactoryBase<DMsg> *factory = new DObjFactoryImpl<DMsg, MsgType>();
        protoImpl->Regist(key, factory);
    }
};
};

#endif /* DPROTOCOL_H */
