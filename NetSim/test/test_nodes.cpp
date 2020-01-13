//
// Created by PC on 05.01.2020.
//

#include "gtest/gtest.h"
#include "nodes.hpp"
#include "helpers.hpp"
/*double fun1(){
    return 0.4;
}
double fun2(){
    return 0.6;
}

TEST(NetWork_package_sender_test, is_buffer_empty) {

    //wysyłanie półproduktu: czy po wysłaniu bufor jest pusty?

    ProbabilityGenerator function = probability_generator;

    //storehouse
    PackageQueueType queueType_lifo_storehouse = PackageQueueType::FIFO;
    std::unique_ptr<PackageQueue> storehouse_queue_ptr = std::make_unique<PackageQueue>(queueType_lifo_storehouse);
    Storehouse storehouse1 = Storehouse(1, std::move(storehouse_queue_ptr));

    //worker
    PackageQueueType queueType_lifo = PackageQueueType::FIFO;
    std::unique_ptr<PackageQueue> package_queue_ptr = std::make_unique<PackageQueue>(queueType_lifo);
    ReceiverPreferences worker_preferences = ReceiverPreferences(function);
    IPackageReceiver* receiver_ptr_worker = &storehouse1;
    worker_preferences.add_receiver(receiver_ptr_worker);
    Worker worker1 = Worker(1, std::move(package_queue_ptr), worker_preferences, 1);

    //ramp
    ReceiverPreferences ramp_preferences = ReceiverPreferences(function);
    IPackageReceiver* receiver_ptr = &worker1;
    ramp_preferences.add_receiver(receiver_ptr);
    Ramp ramp1 = Ramp(1, 1, ramp_preferences);

    //ramp delivers
    EXPECT_EQ(worker1.get_sending_buffer().has_value(), false);
    ramp1.deliver_goods(1);
    EXPECT_EQ(worker1.get_sending_buffer().has_value(), true);
    //worker does work
    worker1.do_work(1);
    worker1.do_work(2);
    EXPECT_EQ((*storehouse1.cbegin()).get_id(), 1);
    EXPECT_EQ(worker1.get_sending_buffer().has_value(), false);
}

TEST(NetWork_receiver_preferences_test, probability_scaling) {
    //dodawanie/usuwanie odbiorcy: skalowanie prawdopodobieństwa


    ProbabilityGenerator function = fun1;  //0.4

    //storehouse
    PackageQueueType queueType_lifo_storehouse = PackageQueueType::LIFO;
    std::unique_ptr<PackageQueue> storehouse_queue_ptr = std::make_unique<PackageQueue>(queueType_lifo_storehouse);
    Storehouse storehouse1 = Storehouse(1, std::move(storehouse_queue_ptr));

    //worker1
    PackageQueueType queueType_lifo = PackageQueueType::LIFO;
    std::unique_ptr<PackageQueue> package_queue_ptr = std::make_unique<PackageQueue>(queueType_lifo);
    ReceiverPreferences worker_preferences = ReceiverPreferences(function);
    IPackageReceiver* receiver_ptr_worker = &storehouse1;
    worker_preferences.add_receiver(receiver_ptr_worker);
    Worker worker1 = Worker(1, std::move(package_queue_ptr), worker_preferences, 2);

    //worker2
    ReceiverPreferences worker_preferences2 = ReceiverPreferences(function);
    std::unique_ptr<PackageQueue> package_queue_ptr2 = std::make_unique<PackageQueue>(queueType_lifo);
    Worker worker2 = Worker(2, std::move(package_queue_ptr2), worker_preferences, 1);
    IPackageReceiver* receiver_ptr_worker2 = &worker2;
    worker_preferences.add_receiver(receiver_ptr_worker2);

    IPackageReceiver* receiver_ptr_worker3 = &worker1;
    worker_preferences.add_receiver(receiver_ptr_worker3);
    EXPECT_LE(worker_preferences.get_preferences()[receiver_ptr_worker]- 0.4, 0.01);
*//*    EXPECT_EQ(worker_preferences.get_preferences()[receiver_ptr_worker2],0.2);
    EXPECT_EQ(worker_preferences.get_preferences()[receiver_ptr_worker],0.4);
    EXPECT_EQ(worker_preferences.get_preferences()[receiver_ptr_worker3],0.4);*//*

}

TEST(NetWork_ramp_test, is_corectly_tour){
//dostawa: czy dostawa odbywa się we właściwej turze? czy półprodukt trafia od razu do bufora?
    ProbabilityGenerator function = probability_generator;

//storehouse 1
    PackageQueueType queueType_lifo_storehouse = PackageQueueType::LIFO;
    std::unique_ptr<PackageQueue> storehouse_queue_ptr = std::make_unique<PackageQueue>(queueType_lifo_storehouse);
    Storehouse storehouse1 = Storehouse(1, std::move(storehouse_queue_ptr));

//worker 2
    PackageQueueType queueType_fifo = PackageQueueType::FIFO;
    std::unique_ptr<PackageQueue> package_queue_ptr2 = std::make_unique<PackageQueue>(queueType_fifo);
    ReceiverPreferences worker_preferences2 = ReceiverPreferences(function);
    IPackageReceiver* receiver_ptr_worker2 = &storehouse1;
    worker_preferences2.add_receiver(receiver_ptr_worker2);
    Worker worker2 = Worker(2, std::move(package_queue_ptr2), worker_preferences2, 1);

//worker 1
    PackageQueueType queueType_lifo = PackageQueueType::LIFO;
    std::unique_ptr<PackageQueue> package_queue_ptr = std::make_unique<PackageQueue>(queueType_lifo);
    ReceiverPreferences worker_preferences = ReceiverPreferences(function);
    IPackageReceiver* receiver_ptr_worker = &worker2;
    worker_preferences.add_receiver(receiver_ptr_worker);
    Worker worker1 = Worker(1, std::move(package_queue_ptr), worker_preferences, 2);

//ramp 1
    ReceiverPreferences ramp_preferences2 = ReceiverPreferences(function);
    IPackageReceiver* receiver_ptr2 = &worker1;
    ramp_preferences2.add_receiver(receiver_ptr2);
    Ramp ramp1 = Ramp(1, 2, ramp_preferences2);
//ramp 2
    ReceiverPreferences ramp_preferences = ReceiverPreferences(function);
    IPackageReceiver* receiver_ptr = &worker2;
    ramp_preferences.add_receiver(receiver_ptr);
    Ramp ramp2 = Ramp(2,1,ramp_preferences);

    //tura 1
    //dostawa i przekazanie
    ramp1.deliver_goods(1);     //przekaze do buffera worker1
    ramp2.deliver_goods(1);     //przekaze do buffera worker2

    EXPECT_EQ(worker1.get_sending_buffer().has_value(), true);
    EXPECT_EQ(worker2.get_sending_buffer().has_value(), true);

    //przetworzenie
    worker1.do_work(1);     //dalej przetwarza
    worker2.do_work(1);     //przetworzyl i wyslal na storehouse1

    EXPECT_EQ(storehouse1.stockpile_queue_ptr->size(), 1);

    //tura 2
    //dostawa i przekazanie

    ramp1.deliver_goods(2);     //nie przekaze
    ramp2.deliver_goods(2);     //przekaze do buffera worker2

    //przetworzenie
    worker1.do_work(2);     //przetworzyl i wyslal do kolejki workera2
    worker2.do_work(2);     //przetworzyl i wyslal na storehouse1

    EXPECT_EQ(worker1.get_sending_buffer().has_value(), false);
    EXPECT_EQ(worker2.get_sending_buffer().has_value(), false);
    EXPECT_EQ(storehouse1.stockpile_queue_ptr->size(), 2);
    EXPECT_EQ(worker2.package_queue_ptr_->size(),1);

    //
}
TEST(NetWork_worker_test,is_corectly_Queue_insert){
    ProbabilityGenerator function = probability_generator;

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
    ramp1.deliver_goods(1);
    worker1.do_work(2);
    EXPECT_EQ(worker1.get_processing_duration(), 2);
}
TEST(NetWork_Storehause_test,is_correct_insert_to_storehause){
    ProbabilityGenerator function = probability_generator;

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
    ramp1.deliver_goods(1);
}*/

