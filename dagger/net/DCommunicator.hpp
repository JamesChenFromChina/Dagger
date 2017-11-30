#ifndef DCOMMUNICATOR_H
#define DCOMMUNICATOR_H

namespace Dagger {

class DCommunicator {
public:
    DCommunicator() = delete;
    DCommunicator *GetInstance();
    void RegistSocket(DSocket *socket);
};

}

#endif /* DCOMMUNICATOR_H */
