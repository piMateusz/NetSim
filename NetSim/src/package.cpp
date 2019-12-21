//
// Created by pilecki on 11.12.2019.
//

#include "package.hpp"
//Initializing static sets

std::set<elementID> Package::assigned_IDs = {0};
std::set<elementID> Package::freed_IDs;

Package& Package::operator=(Package&& package){
    if (id_number != deleted_id) {
        freed_IDs.insert(id_number);
        assigned_IDs.erase(id_number);
    }
    id_number = package.get_id();
    package.id_number = deleted_id;
    return (*this);
}

Package::Package(Package &&package){
    id_number = package.get_id();
    package.id_number = deleted_id;
}

Package::Package(){
    if (freed_IDs.empty()) {
        auto it = assigned_IDs.end();
        it--;
        id_number = *it + 1;
        assigned_IDs.insert(id_number);
        }
    else{
        auto value = *freed_IDs.begin();
        freed_IDs.erase(value);
        id_number = value;
    }
}

Package::~Package(){
    if(id_number != deleted_id){
        if (freed_IDs.find(id_number) == freed_IDs.end()){
            freed_IDs.insert(id_number);
        }
        if (assigned_IDs.find(id_number) != assigned_IDs.end()){
            assigned_IDs.erase(id_number);
        }
    }
}

