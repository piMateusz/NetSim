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

class IpackageReceiver{
    virtual void receive_package(Package &&package) = 0;
    virtual elementID get_id() = 0;
};

class Storehouse: public IpackageReceiver{
    Storehouse(elementID id, std::unique_ptr<IPackageStockpile>);
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

        void add_receiver(IpackageReceiver* receiver_ptr, ProbabilityGenerator random_function);
        void remove_receiver(IpackageReceiver* receiver_prt);
        IpackageReceiver* choose_receiver();
        ReceiverPreferences(ProbabilityGenerator random_function, std::vector<IpackageReceiver*> receivers_vector);
};

// prawie skonczone

class PackageSender{
    private:
        std::optional<Package> sending_buffer = std::nullopt;

    public:
        ReceiverPreferences receiver_preferences_;
        void send_package();        // faktyczne przekazanie odbywa się w etapie symulacji “Przekazanie półproduktów do odbiorców”,
        std::optional<Package> get_sending_buffer(){ return sending_buffer;}

    protected:
        void push_package(Package &&package){sending_buffer.emplace(package);};
};

class Ramp: public PackageSender{
    public:
        Ramp(elementID id, TimeOffset period);
        void deliver_goods(Time time);
        TimeOffset get_delivery_interval();
        elementID get_id();
};

class Worker: public IpackageReceiver, PackageSender{
    public:
        Worker(elementID id, TimeOffset period, std::unique_ptr<PackageQueue>);
        void do_work(Time time);
        TimeOffset get_processing_duration();
        Time get_package_processing_start_time();
};
#endif //NETSIM_NODES_HPP
