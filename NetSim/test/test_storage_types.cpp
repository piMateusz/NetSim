//
// Created by PC on 19.12.2019.
//
#include "gtest/gtest.h"
#include "storage_types.hpp"


TEST(NetWork_storage_types_test, lifo_pop) {
    PackageQueue lifo_queue = PackageQueue(PackageQueueType::LIFO);
    Package package3 = Package();
    Package package4 = Package();
    Package package5 = Package();
    EXPECT_EQ(package3.get_id(), 1);
    EXPECT_EQ(package4.get_id(), 2);
    EXPECT_EQ(package5.get_id(), 3);
    lifo_queue.push(std::move(package3));
    lifo_queue.push(std::move(package4));
    lifo_queue.push(std::move(package5));
    auto popped_product1 = lifo_queue.pop();
    EXPECT_EQ(popped_product1.get_id(), 3);
    EXPECT_EQ(lifo_queue.size(), 2);
}

TEST(NetWork_storage_types_test, fifo_pop) {
    PackageQueue fifo_queue = PackageQueue(PackageQueueType::FIFO);
    Package package1 = Package();
    Package package2 = Package();
    Package package3 = Package();
    EXPECT_EQ(package1.get_id(), 1);
    EXPECT_EQ(package2.get_id(), 2);
    EXPECT_EQ(package3.get_id(), 3);
    fifo_queue.push(std::move(package1));
    fifo_queue.push(std::move(package2));
    fifo_queue.push(std::move(package3));
    auto popped_product = fifo_queue.pop();
    EXPECT_EQ(popped_product.get_id(), 1);
    EXPECT_EQ(fifo_queue.size(), 2);
}

TEST(NetWork_storage_types_test, empty) {
    PackageQueue fifo_queue = PackageQueue(PackageQueueType::FIFO);
    Package package1 = Package();
    Package package2 = Package();
    fifo_queue.push(std::move(package1));
    fifo_queue.push(std::move(package2));
    ASSERT_FALSE(fifo_queue.empty());
    auto popped1 = fifo_queue.pop();
    auto popped2 = fifo_queue.pop();
    ASSERT_TRUE(fifo_queue.empty());
}

TEST(NetWork_storage_types_test, size) {
    PackageQueue fifo_queue = PackageQueue(PackageQueueType::FIFO);
    Package package1 = Package();
    Package package2 = Package();
    Package package3 = Package();
    fifo_queue.push(std::move(package1));
    fifo_queue.push(std::move(package2));
    fifo_queue.push(std::move(package3));
    EXPECT_EQ(fifo_queue.size(), 3);
}