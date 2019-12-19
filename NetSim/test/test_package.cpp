//
// Created by PC on 18.12.2019.
//

#include "gtest/gtest.h"
#include "storage_types.hpp"

TEST(NetWork_package_test, new_product) {
    Package package = Package();

    EXPECT_EQ(package.get_id(), 1);
}

TEST(NetWork_package_test, new_produc_from_assignedID){
    Package package1 = Package();
    Package package2 = Package();
    Package package3 = Package();
    package2.~Package();
    Package package4 = Package();

    EXPECT_EQ(package4.get_id(), 2);
}

TEST(NetWork_package_test, equal_oparator_test){
    Package package1 = Package();
    Package &package2 = package1;

    EXPECT_EQ(package2.get_id(), 1);
}
