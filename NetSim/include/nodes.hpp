//
// Created by pilecki on 11.12.2019.
//

#ifndef NETSIM_NODES_HPP
#define NETSIM_NODES_HPP

#include "storage_types.hpp"
#include <memory>
#include <map>
#include "helpers.hpp"

enum class ReceiverType{
    Worker, Storehouse
};
//---------------------------------------------------------------------------------------------------------------------
class IPackageReceiver{
public:
    using const_package_it = std::list<Package>::const_iterator;
    virtual void receive_package(Package &&package) = 0;
    virtual ElementID get_id() const = 0;
    virtual ReceiverType get_receiver_type() = 0;           //nie odkomentowywac!!!!!
    virtual ~IPackageReceiver(){}
    virtual const_package_it cbegin() const = 0;
    virtual const_package_it cend() const = 0;
    virtual const_package_it begin() const = 0;
    virtual const_package_it end() const = 0;
};

//---------------------------------------------------------------------------------------------------------------------

class ReceiverPreferences{
public:
    using preferences_t = std::map<IPackageReceiver*, double>;
    using const_iterator = preferences_t::const_iterator;
    using iterator = preferences_t::iterator;
    preferences_t preferences_map;
    ProbabilityGenerator random_function_ = [](){ return (double)rand() / RAND_MAX; };
    const preferences_t& get_preferences()const { return preferences_map;}
    const_iterator cbegin() const { return preferences_map.cbegin(); }
    const_iterator cend() const { return preferences_map.cend(); }
    const_iterator begin() const { return preferences_map.cbegin(); }
    const_iterator end() const { return preferences_map.cend(); }

    void add_receiver(IPackageReceiver* receiver_ptr);
    void remove_receiver(IPackageReceiver* receiver_prt);
    IPackageReceiver* choose_receiver();
    ReceiverPreferences(ProbabilityGenerator random_function = probability_generator): preferences_map({}), random_function_(random_function){}
};

//---------------------------------------------------------------------------------------------------------------------

class PackageSender{
public:
    std::optional<Package> sending_buffer = std::nullopt;
    ReceiverPreferences receiver_preferences_;
    virtual void send_package();
    std::optional<Package>& get_sending_buffer(){ return sending_buffer;}
    PackageSender() = default;
protected:
    void push_package(Package &&package){sending_buffer.emplace(std::move(package));};
};

//---------------------------------------------------------------------------------------------------------------------

class Storehouse: public IPackageReceiver{
private:
    ElementID id_;
    ReceiverType receiver_type = ReceiverType::Storehouse;
public:
    std::unique_ptr<IPackageStockpile> stockpile_queue_ptr;
    //Storehouse(ElementID id): id_(id){};
    Storehouse(ElementID id, std::unique_ptr<IPackageStockpile> stockpile_queue_ptr_ = std::make_unique<PackageQueue>(PackageQueue(PackageQueueType::LIFO))): id_(id), stockpile_queue_ptr(std::move(stockpile_queue_ptr_)) {};
    virtual void receive_package(Package &&package) override;
    virtual ReceiverType get_receiver_type() override { return receiver_type;}
    virtual ElementID get_id() const override { return id_;}
    virtual const_package_it cbegin() const override { return stockpile_queue_ptr->cbegin();}
    virtual const_package_it cend() const override { return stockpile_queue_ptr->cend();}
    virtual const_package_it begin() const override { return stockpile_queue_ptr->begin();}
    virtual const_package_it end() const override { return stockpile_queue_ptr->end();}
};

//---------------------------------------------------------------------------------------------------------------------

class Ramp: public PackageSender{
private:
    ElementID id_;
    TimeOffset period_;
public:
    virtual void send_package() override;
    Ramp(ElementID id, TimeOffset period):
            id_(id), period_(period){};
    void deliver_goods(const Time time);
    TimeOffset get_delivery_interval()const { return period_;}
    ElementID get_id() const { return id_;};
};

//---------------------------------------------------------------------------------------------------------------------

class Worker: public IPackageReceiver, public PackageSender{
private:
    ElementID id_;
    ReceiverType receiver_type = ReceiverType::Worker;
    TimeOffset period_;
    Time start_time_ = 0;
public:
    virtual void send_package() override;
    std::unique_ptr<PackageQueue> package_queue_ptr_;
    Worker(ElementID id, TimeOffset period, std::unique_ptr<PackageQueue> package_queue_ptr):
            id_(id), period_(period), package_queue_ptr_(std::move(package_queue_ptr)){};
    virtual void receive_package(Package &&package) override;
    virtual ElementID get_id() const override { return id_;}
    void do_work(const Time time);
    virtual ReceiverType get_receiver_type() override { return receiver_type;}
    TimeOffset get_processing_duration()const { return period_;}
    Time get_package_processing_start_time()const { return start_time_;}
    virtual const_package_it cbegin() const override { return package_queue_ptr_->cbegin();}
    virtual const_package_it cend() const override { return package_queue_ptr_->cend();}
    virtual const_package_it begin() const override { return package_queue_ptr_->begin();}
    virtual const_package_it end() const override { return package_queue_ptr_->end();}
};
#endif //NETSIM_NODES_HPP