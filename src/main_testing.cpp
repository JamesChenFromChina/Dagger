
#include <gtest/gtest.h>

int main(int argc, char *argv[])
{
    testing::InitGoogleTest(&argc,argv);
    int reval = RUN_ALL_TESTS();
    return reval;
}
