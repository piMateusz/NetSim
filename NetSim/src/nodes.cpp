//
// Created by PC on 02.01.2020.
//
#include "nodes.hpp"

//PackageSender

void PackageSender::send_package(){

}

void Storehouse::receive_package(Package &&package) {

}

void Ramp::deliver_goods(Time time) {

}

// Worker

void Worker::do_work(Time time){
    int start = get_package_processing_start_time();
    int pd = get_processing_duration();
    if (time - pd == start){
        send_package();
        get_sending_buffer().reset();
    }
}
void Worker::receive_package(Package &&package){
    push_package(std::move(package));
}
//ReceiverPreferences

void ReceiverPreferences::add_receiver(IPackageReceiver* receiver_ptr, ProbabilityGenerator random_function){
    double added_receiver_probability = random_function();
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
    for (const auto &pair : preferences_map){
        if (pair.second >= random_probability)
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