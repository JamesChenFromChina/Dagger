
#ifndef DMSG_H
#define DMSG_H

#include <utility/DUtility.hpp>

class DMsg {
public:
    virtual void Encode(DStream *out) = 0;
    virtual void Decode(DStream *in) = 0;
};


#endif /* DMSG_H */
