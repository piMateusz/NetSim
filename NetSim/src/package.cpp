//
// Created by pilecki on 11.12.2019.
//

#include "package.hpp"

//Initializing empty sets

std::set<elementID> Package::assigned_IDs;
std::set<elementID> Package::freed_IDs;

Package& Package::operator=(const Package& package){
    id_number = package.get_id();
    return (*this);
}

Package::Package(){
    if (freed_IDs.empty()) {
        if (assigned_IDs.empty()){
            id_number = 1;
            assigned_IDs.insert(1);
        }
        else{
            auto it = assigned_IDs.end();
            it--;
            id_number = *it + 1;
            assigned_IDs.insert(*it + 1);
        }
    }
    else{
        auto value = *freed_IDs.begin();
        freed_IDs.erase(value);
        id_number = value;
    }
}


