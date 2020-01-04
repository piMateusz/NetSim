//
// Created by pilecki on 11.12.2019.
//

#ifndef NETSIM_NODES_HPP
#define NETSIM_NODES_HPP

#include "storage_types.hpp"
#include <memory>
#include <map>

enum class ReceiverType{
    Ramp, Worker, Storehouse
};

class IPackageReceiver{
    virtual void receive_package(Package &&package) = 0;
    virtual elementID get_id() = 0;
};

class Storehouse: public IPackageReceiver{
    private:
        elementID id_;
        std::unique_ptr<IPackageStockpile> stockpile_queue_ptr;
        ReceiverType receiver_type = ReceiverType::Storehouse;
    public:
        Storehouse(elementID id, std::unique_ptr<IPackageStockpile> stockpile_queue_ptr_): id_(id), stockpile_queue_ptr(stockpile_queue_ptr_) {};
        virtual void receive_package(Package &&package) override ;      //TO DO
        virtual elementID get_id() override { return id_;}
        ReceiverType get_receiver_type() { return receiver_type;}
};

// zrobione ale czy dobrze ?

class ReceiverPreferences{
    using preferences_t = std::map<IPackageReceiver*, double>;
    using const_iterator = preferences_t::const_iterator;
    using iterator = preferences_t::iterator;

    private:
        preferences_t preferences_map;

    public:
        const_iterator cbegin() const { return preferences_map.cbegin(); }
        const_iterator cend() const { return preferences_map.cend(); }
        const_iterator begin() const { return preferences_map.cbegin(); }
        const_iterator end() const { return preferences_map.cend(); }

        void add_receiver(IPackageReceiver* receiver_ptr, ProbabilityGenerator random_function);
        void remove_receiver(IPackageReceiver* receiver_prt);
        IPackageReceiver* choose_receiver();
        ReceiverPreferences(ProbabilityGenerator random_function, std::vector<IPackageReceiver*> receivers_vector);
};

// prawie skonczone

class PackageSender{
    private:
        std::optional<Package> sending_buffer = std::nullopt;

    public:
        ReceiverPreferences receiver_preferences_;
        void send_package();        //TO DO - faktyczne przekazanie odbywa się w etapie symulacji “Przekazanie półproduktów do odbiorców”,
        std::optional<Package> get_sending_buffer(){ return sending_buffer;}

    protected:
        void push_package(Package &&package){sending_buffer.emplace(package);};
};

class Ramp: public PackageSender{
    private:
        elementID id_;
        TimeOffset period_;
        Time start_time_;
        ReceiverType receiver_type = ReceiverType::Ramp;
    public:
        Ramp(elementID id, TimeOffset period, Time start_time): id_(id), period_(period), start_time_(start_time) {};
        void deliver_goods(Time time);      //TO DO
        TimeOffset get_delivery_interval(){ return period_;}
        elementID get_id() { return id_;};
        ReceiverType get_receiver_type() { return receiver_type;}
};

class Worker: public IPackageReceiver, PackageSender{
    private:
        elementID id_;
        std::unique_ptr<PackageQueue> package_queue_ptr_;
        ReceiverType receiver_type = ReceiverType::Worker;
        TimeOffset period_;
        Time start_time_;
    public:
        Worker(elementID id, TimeOffset period, Time start_time, std::unique_ptr<PackageQueue> package_queue_ptr):
            id_(id), period_(period), start_time_(start_time), package_queue_ptr_(package_queue_ptr) {};
        virtual void receive_package(Package &&package) override ;      //TO DO
        virtual elementID get_id() override { return id_;}
        ReceiverType get_receiver_type() { return receiver_type;}
        void do_work(Time time);            //TO DO
        TimeOffset get_processing_duration(){ return period_;}
        Time get_package_processing_start_time(){ return start_time_;}
};
#endif //NETSIM_NODES_HPP
