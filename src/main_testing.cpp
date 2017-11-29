
#include <gtest/gtest.h>
#include "Dagger.hpp"

class TestMsg1 : public DMsg {
};

class TestMsg2 : public DMsg {
};

class DaggerMsgHandler
    : public DMsgHandlerBase
    , public DMsgHandler<TestMsg1>
    , public DMsgHandler<TestMsg2> {
public:
    virtual void ProcessMsg(DCommunicator *com,TestMsg1 *msg) {

    }

    virtual void ProcessMsg(DCommunicator *com,TestMsg2 *msg) {

    }
};

void RunNetTest() {

}

int main(int argc, char *argv[])
{
    testing::InitGoogleTest(&argc,argv);
    int reval = RUN_ALL_TESTS();

    RunNetTest();

    return reval;
}
