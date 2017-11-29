#ifndef DPROTOCOL_H
#define DPROTOCOL_H


namespace Dagger {

class DProtocolBase {
public:
    virtual void Dispatch(KeyType key) = 0;
}

template<typename KeyType>
class DProtocol {
public:
    template<MsgType>
    virtual void Regist(KeyType key, ObjFactoryBase<MsgType> *factory) = 0;
    virtual void Dispatch(DInStream in) = 0;
};

    template<KeyType, MsgType, HandlerType>
    class DMsgRegister {
    }

}

#endif /* DPROTOCOL_H */
