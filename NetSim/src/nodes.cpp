//
// Created by PC on 02.01.2020.
//
#include "nodes.hpp"

//worker

void Worker::do_work(Time time){
    ;
}

//ramp

void Ramp::deliver_goods(Time time){
    ;
}

//PackageSender

void PackageSender::send_package(){
    ;
}

//ReceiverPreferences

void ReceiverPreferences::add_receiver(IpackageReceiver* receiver_ptr, ProbabilityGenerator random_function){
    double added_receiver_probability = random_function();
    double scaled_probability = added_receiver_probability/preferences_map.size();
    for(auto pair : preferences_map){
        pair.second() -= scaled_probability;
    }
    preferences_map[receiver_ptr] = added_receiver_probability;
}

void ReceiverPreferences::remove_receiver(IpackageReceiver* receiver_ptr){
    double removed_receiver_probability = preferences_map[receiver_ptr];
    for(auto it = preferences_map.begin; it != preferences_map.end();){
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

IpackageReceiver* ReceiverPreferences::choose_receiver(){
    for (const auto &pair : preferences_map)
        return pair.first()
}

ReceiverPreferences::ReceiverPreferences(ProbabilityGenerator random_function, std::vector<IpackageReceiver*> receivers_vector){
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