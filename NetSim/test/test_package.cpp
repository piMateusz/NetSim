//
// Created by PC on 18.12.2019.
//

#include "gtest/gtest.h"
#include "storage_types.hpp"

TEST(NetWork_package_test, new_product) {
    Package package = Package();
    Package package1 = Package();
    EXPECT_EQ(package.get_id(), 1);
    EXPECT_EQ(package1.get_id(), 2);
}

TEST(NetWork_package_test, new_produc_from_assignedID){
    Package package1 = Package();
    Package package2 = Package();
    Package package3 = Package();
    package2.~Package();
    package3.~Package();
    Package package4 = Package();
    Package package5 = Package();

    EXPECT_EQ(package4.get_id(), 2);
    EXPECT_EQ(package5.get_id(), 3);
}

TEST(NetWork_package_test, equal_oparator_test){
    Package package1 = Package();
    Package &package2 = package1;
//    Package package3 = Package();         //uncomment if fixed above
//    Package package4 = Package();
//    package3 = package2;
//    Package package5 = Package();

    EXPECT_EQ(package2.get_id(), 1);
    EXPECT_EQ(package1.get_id(), 0);
//    EXPECT_EQ(package3.get_id(), 1);
//    EXPECT_EQ(package4.get_id(), 3);
//    EXPECT_EQ(package5.get_id(), 2);
}
