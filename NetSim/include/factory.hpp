//
// Created by pilecki on 11.12.2019.
//

#ifndef NETSIM_FACTORY_HPP
#define NETSIM_FACTORY_HPP

#include "storage_types.hpp"
#include "nodes.hpp"
#include "types.hpp"
#include "package.hpp"

template <class Node>
class NodeCollection{
    using container_t = typename std::list<Node>;
    using iterator = typename container_t::iterator;
    using const_iterator = typename container_t::const_iterator;
    private:
        container_t collection;
    public:
        void add(Node& node) { collection.push_back(std::move(node)); };
        //void remove_by_id(ElementID id_){};
        //NodeCollection<Node>::iterator find_by_id(ElementID id_)
        //NodeCollection<Node>::const_iterator find_by_id(ElementID id_){};

        NodeCollection<Node>::iterator begin() { return collection.begin();};
        NodeCollection<Node>::iterator end(){ return collection.end(); };
        NodeCollection<Node>::iterator cbegin() { return collection.cbegin();};
        NodeCollection<Node>::iterator cend(){ return collection.cend(); };
};

class Factory{
    private:
        NodeCollection<Worker> workers;
        NodeCollection<Ramp> ramps;
        NodeCollection<Storehouse> storehouses;

    public:
        void add_ramp(Ramp&& ramp){ ramps.add(ramp);};
//        void remove_ramp(ElementID id){};
//        NodeCollection<Ramp>::iterator find_ramp_by_id(ElementID id){};
//        NodeCollection<Ramp>::const_iterator find_ramp_by_id(ElementID id){};

//
//        void add_worker(Worker&& worker){ workers.add(worker);};
//        void remove_worker(ElementID id){};
//        NodeCollection<Worker>::iterator find_worker_by_id(ElementID id){};
//        NodeCollection<Worker>::const_iterator find_worker_by_id(ElementID id){};

//
//        void add_storehouse(Storehouse&& storehouse){ storehouses.add(storehouse);};
//        void remove_storehouse(ElementID id){};
//        NodeCollection<Storehouse>::iterator find_storehouse_by_id(ElementID id){};
//        NodeCollection<Storehouse>::const_iterator find_storehouse_by_id(ElementID id){};


        bool is_consistent();
        //void do_deliveries(Time time);
        //void do_package_passing(){};
        //void do_work(Time time){};
};




#endif //NETSIM_FACTORY_HPP
