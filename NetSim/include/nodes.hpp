//
// Created by pilecki on 11.12.2019.
//

#ifndef NETSIM_NODES_HPP
#define NETSIM_NODES_HPP

#include "storage_types.hpp"
#include <memory>
#include <map>

enum class ReceiverType{
    Worker, Storehouse
};

class IPackageReceiver{
    public:
        using const_package_it = std::list<Package>::const_iterator;
        virtual void receive_package(Package &&package) = 0;
        virtual elementID get_id() = 0;
        virtual ReceiverType get_receiver_type() = 0;
        virtual const_package_it cbegin() const = 0;
        virtual const_package_it cend() const = 0;
        virtual const_package_it begin() const = 0;
        virtual const_package_it end() const = 0;
};

class Storehouse: public IPackageReceiver{
    private:
        elementID id_;
        std::unique_ptr<IPackageStockpile> stockpile_queue_ptr;
        ReceiverType receiver_type = ReceiverType::Storehouse;
    public:
        Storehouse(elementID id, std::unique_ptr<IPackageStockpile> stockpile_queue_ptr_): id_(id), stockpile_queue_ptr(std::move(stockpile_queue_ptr_)) {};
        virtual void receive_package(Package &&package) override;      //TO DO
        virtual ReceiverType get_receiver_type() override { return receiver_type;}
        virtual elementID get_id() override { return id_;}
        virtual const_package_it cbegin() const override { return stockpile_queue_ptr->cbegin();}
        virtual const_package_it cend() const override { return stockpile_queue_ptr->cend();}
        virtual const_package_it begin() const override { return stockpile_queue_ptr->begin();}
        virtual const_package_it end() const override { return stockpile_queue_ptr->end();}
};


class ReceiverPreferences{
    using preferences_t = std::map<IPackageReceiver*, double>;
    using const_iterator = preferences_t::const_iterator;
    using iterator = preferences_t::iterator;

    private:
        ProbabilityGenerator random_function_;
    public:
        preferences_t preferences_map;
        const_iterator cbegin() const { return preferences_map.cbegin(); }
        const_iterator cend() const { return preferences_map.cend(); }
        const_iterator begin() const { return preferences_map.cbegin(); }
        const_iterator end() const { return preferences_map.cend(); }

        void add_receiver(IPackageReceiver* receiver_ptr);
        void remove_receiver(IPackageReceiver* receiver_prt);
        IPackageReceiver* choose_receiver();
        ReceiverPreferences(ProbabilityGenerator random_function): random_function_(random_function), preferences_map({}){}
        ReceiverPreferences(ProbabilityGenerator random_function, std::vector<IPackageReceiver*> receivers_vector);
};


class PackageSender{
    private:
        std::optional<Package> sending_buffer = std::nullopt;
    public:
        ReceiverPreferences receiver_preferences_;
        PackageSender(ReceiverPreferences receiver_preferences): receiver_preferences_(receiver_preferences) {}
        void send_package();
        std::optional<Package> get_sending_buffer(){ return std::move(sending_buffer);}
    protected:
        void push_package(Package &&package){sending_buffer.emplace(std::move(package));};
};

class Ramp: public PackageSender{
    private:
        elementID id_;
        TimeOffset period_;
    public:
        Ramp(elementID id, TimeOffset period, ReceiverPreferences receiver_preferences):
            PackageSender(receiver_preferences), id_(id), period_(period){};
        void deliver_goods(Time time);      //TO DO
        TimeOffset get_delivery_interval(){ return period_;}
        elementID get_id() { return id_;};
};

class Worker: public IPackageReceiver, public PackageSender{
    private:
        elementID id_;
        std::unique_ptr<PackageQueue> package_queue_ptr_;
        ReceiverType receiver_type = ReceiverType::Worker;
        TimeOffset period_;
        Time start_time_ = 0;
    public:
        Worker(elementID id, std::unique_ptr<PackageQueue> package_queue_ptr, ReceiverPreferences receiver_preferences, TimeOffset period):
            PackageSender(receiver_preferences), id_(id), package_queue_ptr_(std::move(package_queue_ptr)), period_(period){};
        virtual void receive_package(Package &&package) override;      //TO DO
        virtual elementID get_id() override { return id_;}
        void do_work(Time time);
        virtual ReceiverType get_receiver_type() override { return receiver_type;}
        TimeOffset get_processing_duration(){ return period_;}
        Time get_package_processing_start_time(){ return start_time_;}
        virtual const_package_it cbegin() const override { return package_queue_ptr_->cbegin();}
        virtual const_package_it cend() const override { return package_queue_ptr_->cend();}
        virtual const_package_it begin() const override { return package_queue_ptr_->begin();}
        virtual const_package_it end() const override { return package_queue_ptr_->end();}
};
#endif //NETSIM_NODES_HPP
