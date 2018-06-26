#include "lib.h"
#include <gtest/gtest.h>

TEST(lib_tests, valide_version) {
ASSERT_TRUE(version() > 0);
}

int main(int argc, char **argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
