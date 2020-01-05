//
// Created by PC on 05.01.2020.
//

#include "gtest/gtest.h"
#include "nodes.hpp"
#include "helpers.hpp"

TEST(NetWork_package_sender_test, is_buffer_empty) {

    //wysyłanie półproduktu: czy po wysłaniu bufor jest pusty?

    ProbabilityGenerator function = probability_generator_1;

    //storehouse
    PackageQueueType queueType_lifo_storehouse = PackageQueueType::LIFO;
    std::unique_ptr<PackageQueue> storehouse_queue_ptr = std::make_unique<PackageQueue>(queueType_lifo_storehouse);
    Storehouse storehouse1 = Storehouse(1, std::move(storehouse_queue_ptr));

    //worker
    PackageQueueType queueType_lifo = PackageQueueType::LIFO;
    std::unique_ptr<PackageQueue> package_queue_ptr = std::make_unique<PackageQueue>(queueType_lifo);
    ReceiverPreferences worker_preferences = ReceiverPreferences(function);
    IPackageReceiver* receiver_ptr_worker = &storehouse1;
    worker_preferences.add_receiver(receiver_ptr_worker);
    Worker worker1 = Worker(1, std::move(package_queue_ptr), worker_preferences, 2);

    //ramp
    ReceiverPreferences ramp_preferences = ReceiverPreferences(function);
    IPackageReceiver* receiver_ptr = &worker1;
    ramp_preferences.add_receiver(receiver_ptr);
    Ramp ramp1 = Ramp(1, 1, ramp_preferences);

    //ramp delivers
    ramp1.deliver_goods(1);

    //EXPECT_EQ(worker1.get_sending_buffer(), 1);
}