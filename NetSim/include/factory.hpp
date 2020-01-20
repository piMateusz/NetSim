//
// Created by pilecki on 11.12.2019.
//

#ifndef NETSIM_FACTORY_HPP
#define NETSIM_FACTORY_HPP

#include "storage_types.hpp"
#include "nodes.hpp"


template <typename Node>
class NodeCollection{
    public:
        using container_t = typename std::list<Node>;
        using iterator = typename container_t::iterator;
        using const_iterator = typename container_t::const_iterator;
    private:
        container_t collection;
    public:
        void add(Node&& node) { collection.emplace_back(std::move(node));};
        void remove_by_id(ElementID id_){ collection.erase(find_by_id(id_));};
        iterator find_by_id(ElementID id_) { return std::find_if(collection.begin(), collection.end(), [&id_](auto &elem) { return elem.get_id() == id_; });};
        const_iterator find_by_id(ElementID id_) const { return std::find_if(collection.begin(), collection.end(), [&id_](const auto &elem) { return elem.get_id() == id_; });};

        iterator begin() { return collection.begin();};
        iterator end(){ return collection.end(); };
        const_iterator cbegin(){ return collection.cbegin();};
        const_iterator cend(){ return collection.cend(); };
};

class Factory{
    private:
        //Kolekcje węzłów
        NodeCollection<Worker> workers;
        NodeCollection<Ramp> ramps;
        NodeCollection<Storehouse> storehouses;
        template<typename Node>
        void remove_receiver(NodeCollection<Node>& collection, ElementID id) {
                if(collection.find_by_id(id) == collection.end()) return;
                for(auto& elem: workers){
                        elem.receiver_preferences_.remove_receiver(&(*collection.find_by_id(id)));
                }
                for(auto& elem: ramps){
                        elem.receiver_preferences_.remove_receiver(&(*collection.find_by_id(id)));
                }

                collection.remove_by_id(id);
    }

    public:
        //Ramp
        void add_ramp(Ramp&& ramp){ ramps.add(std::move(ramp)); };
        void remove_ramp(ElementID id){ ramps.remove_by_id(id); };
        NodeCollection<Ramp>::iterator find_ramp_by_id(ElementID id){ return ramps.find_by_id(id); };
        NodeCollection<Ramp>::const_iterator find_ramp_by_id(ElementID id) const { return ramps.find_by_id(id); };

        //Worker
        void add_worker(Worker&& worker){ workers.add(std::move(worker));};
        //void remove_worker(ElementID id){ workers.remove_by_id(id); };
        void remove_worker(ElementID id){this->remove_receiver(workers,id);};
        NodeCollection<Worker>::iterator find_worker_by_id(ElementID id){ return workers.find_by_id(id);};
        NodeCollection<Worker>::const_iterator find_worker_by_id(ElementID id) const { return workers.find_by_id(id); };

        //Storehouse
        void add_storehouse(Storehouse&& storehouse){ storehouses.add(std::move(storehouse));};
        void remove_storehouse(ElementID id){ storehouses.remove_by_id(id); };
        NodeCollection<Storehouse>::iterator find_storehouse_by_id(ElementID id){ return storehouses.find_by_id(id); };
        NodeCollection<Storehouse>::const_iterator find_storehouse_by_id(ElementID id) const { return storehouses.find_by_id(id); };

        bool is_consistent();
        void do_deliveries(Time time);
        void do_package_passing();
        void do_work(Time time);
};




#endif //NETSIM_FACTORY_HPP
