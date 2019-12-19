//
// Created by PC on 18.12.2019.
//

#include "gtest/gtest.h"
#include "package.hpp"

TEST(NetWork_package_test, new_object) {
    Package package = Package();

    EXPECT_EQ(package.get_id(), 1);
}