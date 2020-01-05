//
// Created by PC on 02.01.2020.
//
#include "nodes.hpp"

//PackageSender

void PackageSender::send_package(){
    IPackageReceiver* receiver_ptr = receiver_preferences_.choose_receiver();
    receiver_ptr->receive_package(*get_sending_buffer());
    get_sending_buffer().reset();
}

//Storehouse

void Storehouse::receive_package(Package &&package) {
    stockpile_queue_ptr->push(package);
}

void Ramp::deliver_goods(Time time) {
    if ( (time-1) % get_delivery_interval() == 0){
        auto package = Package();
        IPackageReceiver* receiver_ptr = receiver_preferences_.choose_receiver();
        receiver_ptr->receive_package(std::move(package));
    }
}

// Worker

void Worker::do_work(Time time){
    TimeOffset pd = get_processing_duration();
    if ((time - 1) % pd == 0 ){
        send_package();
        get_sending_buffer().reset();
    }
}
void Worker::receive_package(Package &&package){
    if (get_sending_buffer()){
        package_queue_ptr_->push(package);
    }
    else{
        push_package(std::move(package));
    }
}

//ReceiverPreferences

void ReceiverPreferences::add_receiver(IPackageReceiver* receiver_ptr){
    double added_receiver_probability = random_function_();
    double scaled_probability = added_receiver_probability/preferences_map.size();
    for(auto pair : preferences_map){
        pair.second -= scaled_probability;
    }
    preferences_map[receiver_ptr] = added_receiver_probability;
}

void ReceiverPreferences::remove_receiver(IPackageReceiver* receiver_ptr){
    double removed_receiver_probability = preferences_map[receiver_ptr];
    for(auto it = preferences_map.begin(); it != preferences_map.end();){
        if (it->first == receiver_ptr){
            it = preferences_map.erase(it);
            break;
        }
    }
    for(auto pair : preferences_map){
        double scaled_probability = removed_receiver_probability/preferences_map.size();
        pair.second += scaled_probability;
    }
}

IPackageReceiver* ReceiverPreferences::choose_receiver(){
    double random_probability = random_function_();
    double sum = 0;
    for (const auto &pair : preferences_map){
        sum += pair.second;
        if (sum >= random_probability)
            return pair.first;
    }
    return nullptr;
}

ReceiverPreferences::ReceiverPreferences(ProbabilityGenerator random_function, std::vector<IPackageReceiver*> receivers_vector){
    random_function_ = random_function;
    double probability_sum = 0;
    for (const auto &receiver : receivers_vector) {
        if (receiver == *(receivers_vector.end() - 1))
            preferences_map[receiver] = 1 - probability_sum;
        else{
            preferences_map[receiver] = random_function();
            probability_sum += preferences_map[receiver];
        }
    }
}
