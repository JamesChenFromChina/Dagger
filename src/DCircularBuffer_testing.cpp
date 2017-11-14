
#include <gtest/gtest.h>
#include "Dagger.hpp"

TEST(DaggerBase,CircularBuffer) {
    DCircularBuffer testbuf(0);
    ASSERT_EQ(testbuf.Capacity(),0UL);

    testbuf.Expand(100);
    ASSERT_EQ(testbuf.Capacity(),100UL);
}
