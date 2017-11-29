#ifndef DPROTOCOL_H
#define DPROTOCOL_H


namespace Dagger {

class DProtocolBase {
public:
};

template<typename KeyType>
class DProtocol {
public:
    template<typename MsgType>
    void Regist(KeyType key, ObjFactoryBase<MsgType> *factory);
    virtual void Dispatch(DStream in) = 0;
};

    template<typename KeyType,typename MsgType,typename HandlerType>
    class DMsgRegister {
    };

};

#endif /* DPROTOCOL_H */
