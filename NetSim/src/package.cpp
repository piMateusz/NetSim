//
// Created by pilecki on 11.12.2019.
//

#include "package.hpp"

//Initializing empty sets

std::set<elementID> Package::assigned_IDs;
std::set<elementID> Package::freed_IDs;

Package& Package::operator=(Package&& package){
    id_number = std::move(package.get_id());
    package.id_number = 0;
    return (*this);
}

Package::Package(Package &&package){
    id_number = std::move(package.get_id());
    package.id_number = 0;
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


