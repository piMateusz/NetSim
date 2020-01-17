//
// Created by pilecki on 11.12.2019.
//

#ifndef NETSIM_FACTORY_HPP
#define NETSIM_FACTORY_HPP
//template class NodeCollectio


class Factory{
    public:
    void add_ramp(Ramp&& ramp);
    void remove_ramp(ElementID id);
    NodeCollection<Ramp>::iterator find_ramp_by_id(Element ID id);
    NodeCollection<Ramp>::const_iterator find_ramp_by_id(ElementID id);
    NodeCollection<Ramp>::const_iterator ramp_cbegin();
    NodeCollection<Ramp>::const_iterator ramp_cend();

    bool is_consistent();
    void do_deliveries(Time);
    void do_package_passing();
    void do_work(Time);
};

class NodeCollection{
    public:
        void add(Node& node);
        void remove_by_id(ElementID id_);
        NodeCollection<Node>::iterator find_by_id(ElementID id_);
        NodeCollection<Node>::const_iterator find_by_id(ElementID id_);
};

#endif //NETSIM_FACTORY_HPP
