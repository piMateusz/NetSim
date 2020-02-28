//
// Created by PC on 02.01.2020.
//
#include <iostream>
#include "nodes.hpp"

//PackageSender

void PackageSender::send_package(){
    if(get_sending_buffer()){
        IPackageReceiver* receiver_ptr = receiver_preferences_.choose_receiver();
        receiver_ptr->receive_package(std::move(*get_sending_buffer()));
        get_sending_buffer().reset();
    }
}

//Storehouse

void Storehouse::receive_package(Package &&package) {
    stockpile_queue_ptr->push(std::move(package));
}

//Ramp

void Ramp::deliver_goods(const Time time) {
    if ( (time-1) % get_delivery_interval() == 0){
        auto package = Package();
        push_package(std::move(package));

    }
}

void Ramp::send_package(){
    if(Ramp::get_sending_buffer().has_value()) {
        IPackageReceiver *receiver_ptr = receiver_preferences_.choose_receiver();
        receiver_ptr->receive_package(std::move(*get_sending_buffer()));
        get_sending_buffer().reset();
    }
}

// Worker

void Worker::send_package(){
    if(start_time_ == 0 && Worker::get_sending_buffer().has_value()){
        IPackageReceiver* receiver_ptr = receiver_preferences_.choose_receiver();
        receiver_ptr->receive_package(std::move(*get_sending_buffer()));
        get_sending_buffer().reset();

    }

}

void Worker::do_work(const Time time){
    if (!get_sending_buffer()){
        if(!package_queue_ptr_->empty()){
            push_package(package_queue_ptr_->pop());
        }
    }
    if (start_time_ == 0){
        start_time_ = time;
    }
    if(start_time_ == time - get_processing_duration())
        start_time_ = 0;

}


void Worker::receive_package(Package &&package){
    if (get_sending_buffer()){
        package_queue_ptr_->push(std::move(package));
    }
    else{
        push_package(std::move(package));
    }

}

//ReceiverPreferences

void ReceiverPreferences::add_receiver(IPackageReceiver* receiver_ptr){
/*    if (preferences_map.empty()){
        preferences_map[receiver_ptr] = 1.0;
    }
    else{
        double added_receiver_probability = random_function_();
        double scaled_probability = added_receiver_probability/preferences_map.size();
        for(auto &pair : preferences_map){
            pair.second -= scaled_probability;
        }
        preferences_map[receiver_ptr] = added_receiver_probability;
    }*/
    preferences_map[receiver_ptr] = 1;
    if(preferences_map.empty()) return;
    int length = preferences_map.size();
    for(auto& elem : preferences_map) elem.second = 1.0/length;
}

void ReceiverPreferences::remove_receiver(IPackageReceiver* receiver_ptr){
/*    double removed_receiver_probability = preferences_map[receiver_ptr];
    for(auto it = preferences_map.begin(); it != preferences_map.end();){
        if (it->first == receiver_ptr){
            it = preferences_map.erase(it);
            break;
        }
    }
    double scaled_probability = removed_receiver_probability/preferences_map.size();
    for(auto &pair : preferences_map){
        pair.second += scaled_probability;
    }*/
    preferences_map.erase(receiver_ptr);
    if(preferences_map.empty()) return;
    int length = preferences_map.size();
    for(auto& elem : preferences_map) elem.second = 1.0/length;
}

IPackageReceiver* ReceiverPreferences::choose_receiver(){
    double random_probability = random_function_();
    double sum = 0;
    for (auto &pair : preferences_map){
        if(*preferences_map.cbegin() == pair){
            if (0 <= random_probability and random_probability <= pair.second)
                return pair.first;
            else{
                sum += pair.second;
            }
        }
        else{
            if (sum < random_probability and random_probability < sum + pair.second){
                return pair.first;
            }
            else{
                sum += pair.second;
            }
        }
    }
    return nullptr;
}