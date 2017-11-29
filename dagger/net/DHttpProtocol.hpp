#ifndef DHTTPPROTOCOL_H
#define DHTTPPROTOCOL_H

#include "DProtocol.hpp"

class DHttpProtocol : public DProtocol<string>  {
public:
    virtual void Regist(string &key, DaggerMsgHandler &handler) {

    }

    DaggerMsgHandler *GetHandler(string &key) {
        
    }
};


#endif /* DHTTPPROTOCOL_H */
