//
// Created by PC on 19.12.2019.
//
#include "gtest/gtest.h"
#include "storage_types.hpp"
#include "package.hpp"

TEST(NetWork_storage_types_test, fifo_pop) {
    PackageQueue fifo_queue = PackageQueue(PackageQueueType::FIFO);
    Package package1 = Package();
    Package package2 = Package();
    fifo_queue.push(package1);
    fifo_queue.push(package2);
    auto popped_product = fifo_queue.pop();

    EXPECT_EQ(popped_product.get_id(), 1);
    EXPECT_EQ(fifo_queue.size(), 1);
}

TEST(NetWork_storage_types_test, lifo_pop) {
    PackageQueue lifo_queue = PackageQueue(PackageQueueType::LIFO);
    Package package1 = Package();
    Package package2 = Package();
    lifo_queue.push(package1);
    lifo_queue.push(package2);
    auto popped_product = lifo_queue.pop();

    EXPECT_EQ(popped_product.get_id(), 2);
    EXPECT_EQ(lifo_queue.size(), 1);
}

TEST(NetWork_storage_types_test, empty) {
    PackageQueue fifo_queue = PackageQueue(PackageQueueType::FIFO);
    Package package1 = Package();
    Package package2 = Package();
    fifo_queue.push(package1);
    fifo_queue.push(package2);

    ASSERT_FALSE(fifo_queue.empty());

}

TEST(NetWork_storage_types_test, size) {
    PackageQueue fifo_queue = PackageQueue(PackageQueueType::FIFO);
    Package package1 = Package();
    Package package2 = Package();
    fifo_queue.push(package1);
    fifo_queue.push(package2);

    EXPECT_EQ(fifo_queue.size(), 2);
}