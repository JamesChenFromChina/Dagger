
#include <gtest/gtest.h>
#include "Dagger.hpp"

class TestMsg1 : public DMsg {
};

class TestMsg2 : public DMsg {
};

class TestMsgHandler
    : public DMsgHandlerBase
    , public DMsgHandler<TestMsg1>
    , public DMsgHandler<TestMsg2> {
public:
    virtual void ProcessMsg(DCommunicator *com,TestMsg1 *msg) {
    }

    virtual void ProcessMsg(DCommunicator *com,TestMsg2 *msg) {

    }
};

DHttpProtocol proto;
DMsgRegister<string, TestMsg1, TestMsgHandler> regist1("/default", proto);
DMsgRegister<string, TestMsg2, TestMsgHandler> regist2("index", proto);

TEST(FrameTesting, MsgRoute) {
    DService testService(DNetAddr(127.0.0.1,8800), &proto);
    testService.Run();

}

