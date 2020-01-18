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
    public:
        using container_t = typename std::list<Node>;
        using iterator = typename container_t::iterator;
        using const_iterator = typename container_t::const_iterator;

        //void add(Node& node);
        void remove_by_id(ElementID id_){};
        NodeCollection<Node>::iterator find_by_id(ElementID id_){};
        NodeCollection<Node>::const_iterator find_by_id(ElementID id_){};
};

class Factory{
    private:
        NodeCollection<Worker> workers;
        NodeCollection<Ramp> ramps;

    public:
        void add_ramp(Ramp&& ramp){};
        void remove_ramp(ElementID id){};
        NodeCollection<Ramp>::iterator find_ramp_by_id(ElementID id){};
        NodeCollection<Ramp>::const_iterator find_ramp_by_id(ElementID id){};
        NodeCollection<Ramp>::const_iterator ramp_cbegin();;
        NodeCollection<Ramp>::const_iterator ramp_cend(){};

        void add_worker(Worker&& worker){};
        void remove_worker(ElementID id){};
        NodeCollection<Worker>::iterator find_worker_by_id(ElementID id){};
        NodeCollection<Worker>::const_iterator find_worker_by_id(ElementID id){};
        NodeCollection<Worker>::const_iterator worker_cbegin(){};
        NodeCollection<Worker>::const_iterator worker_cend(){};

        void add_storehouse(Storehouse&& storehouse){};
        void remove_storehouse(ElementID id){};
        NodeCollection<Storehouse>::iterator find_storehouse_by_id(ElementID id){};
        NodeCollection<Storehouse>::const_iterator find_storehouse_by_id(ElementID id){};
        NodeCollection<Storehouse>::const_iterator storehouse_cbegin(){};
        NodeCollection<Storehouse>::const_iterator storehouse_cend(){};

        bool is_consistent();
        void do_deliveries(Time);
        void do_package_passing(){};
        void do_work(Time){};
};




#endif //NETSIM_FACTORY_HPP
