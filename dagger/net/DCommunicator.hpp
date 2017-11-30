#ifndef DCOMMUNICATOR_H
#define DCOMMUNICATOR_H

namespace Dagger {

class DCommunicator {
public:
    DCommunicator() = delete;
    static DCommunicator *GetInstance();
    DNetConnection *BuildConnection(const DNetAddr &addr);
};

}

#endif /* DCOMMUNICATOR_H */
