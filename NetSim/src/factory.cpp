
// Created by Jean Jacob on 2020-01-18.


#include "factory.hpp"

enum color_enum{
    WHITE, YELLOW, GREEN
};

template<typename Node>
void Factory::remove_receiver(NodeCollection<Node>& collection, ElementID id) {

    if (collection.cbegin()->get_receiver_type() == ReceiverType::Worker) {
        auto it = find_worker_by_id(id);
        for(auto& worker: workers) {
            worker.receiver_preferences_.remove_receiver(&(*it));
        }
        for(auto& ramp: ramps) {
            ramp.receiver_preferences_.remove_receiver(&(*it));
        }
    }
    else if (collection.cbegin()->get_receiver_type() == ReceiverType::Storehouse) {
        auto it = find_storehouse_by_id(id);
        for(auto& worker: workers) {
            worker.receiver_preferences_.remove_receiver(&(*it));
        }
    }
}

bool sender_has_storehouse(PackageSender* sender, std::map<PackageSender*, color_enum> color_map){
    if (color_map[sender] == color_enum::GREEN){
        return true;
    }
    color_map[sender] = color_enum::YELLOW;

    if(sender->receiver_preferences_.get_preferences().empty()){
        throw std::logic_error("Niespójna");
    }

    bool sender_has_correct_receiver = false;
    for (auto& receiver : sender->receiver_preferences_.get_preferences()){
        if(receiver.first->get_receiver_type() == ReceiverType::Storehouse){
            sender_has_correct_receiver = true;
        }
        else if(receiver.first->get_receiver_type() == ReceiverType::Worker){
            IPackageReceiver* receiver_ptr = receiver.first;
            auto worker_ptr = dynamic_cast<Worker*>(receiver_ptr);
            auto sendrecv_ptr = dynamic_cast<PackageSender*>(worker_ptr);
            if (worker_ptr != sender) {
                sender_has_correct_receiver = true;
                if (color_map[sendrecv_ptr] == color_enum::WHITE) {
                    try {
                        sender_has_storehouse(sendrecv_ptr, color_map);
                    }
                    catch (std::logic_error &) {
                        throw std::logic_error("Niespójna");
                    }
                }
            }
        }
    }
    color_map[sender] = color_enum::YELLOW;

    if (sender_has_correct_receiver){
        return true;
    }
    else{
        throw std::logic_error("Niespójna");
    }
}


bool Factory::is_consistent(){
    std::map<PackageSender*, color_enum> color_map;
    for(auto &node : workers){
        color_map[&node] = color_enum::WHITE;
    }
    for(auto &node : ramps){
        color_map[&node] = color_enum::WHITE;
    }
    for(auto &it : ramps){
        try{
            sender_has_storehouse(&it, color_map);
        }
        catch (std::logic_error &) {
            return false;
        }
    }
    return true;
}

void Factory::do_deliveries(Time time) {
    for(auto& member : ramps){
        member.deliver_goods(time);
    }
}

void Factory::do_package_passing(){
    for(auto& member : workers ){
        member.send_package();
    }
    for(auto& member : ramps ){
        member.send_package();
    }
}
void Factory::do_work(Time time){
    for(auto& member : workers){
        member.do_work(time);
    }
}
