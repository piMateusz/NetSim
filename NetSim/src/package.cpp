/*
//
// Created by pilecki on 11.12.2019.
//

#include "package.hpp"
//Initializing static sets

std::set<ElementID> Package::assigned_IDs = {0};
std::set<ElementID> Package::freed_IDs;

Package& Package::operator=(Package&& package){
    if (id_number != deleted_id) {
        freed_IDs.insert(id_number);
        assigned_IDs.erase(id_number);
    }
    id_number = package.get_id();
    package.id_number = deleted_id;
    return (*this);
}

Package::Package(Package &&package) noexcept {
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

*/


#include "package.hpp"

#include <stdexcept>

void insert_if_not_exists(std::set<ElementID>& s, ElementID e) {
    if (s.find(e) == s.end()) {
        s.insert(e);
    }
}

void erase_if_exists(std::set<ElementID>& s, ElementID e) {
    if (s.find(e) != s.end()) {
        s.erase(e);
    }
}

Package::Package() {
    if (freed_ids_.empty()) {
        // Przypisz najmniejszy dotychczas nieużyty identyfikator.
        id_ = (*assigned_ids_.rbegin()) + 1;
    } else {
        // Metoda set::extract() nie jest dostępna we wszystkich implementacjach kompilatora C++.
//            id_ = freed_ids_.extract(freed_ids_.begin());
        id_ = *freed_ids_.begin();
        freed_ids_.erase(id_);
    }
    assigned_ids_.insert(id_);
}

Package::Package(ElementID id) {
    if (assigned_ids_.find(id) != assigned_ids_.end()) {
        throw std::invalid_argument("The ID of " + std::to_string(id) + " is already assigned!");
    }

    id_ = id;
    assigned_ids_.insert(id_);
    erase_if_exists(freed_ids_, id);
}

Package::Package(Package&& other) noexcept {
    id_ = other.id_;
    other.id_ = BLANK_ID;
}

Package& Package::operator=(Package&& other) noexcept {
    /*
     * Przypisanie odbywa się do już istniejącego obiektu, zatem należy zadbać,
     * aby przydzielone temu obiektowi ID wróciło do puli dostępnych ID.
     * W przeciwnym razie m.in. każda operacja typu
     *   Product p0;
     *   Product p = p0;
     * prowadziłaby do "wycieku identyfikatorów" - gdyż po jej wykonaniu ID p0
     * wynosiłoby BLANK_ID, p otrzymałoby dotychczasowy ID p0, natomiast
     * dotychczasowy ID p pozostałby w puli przydzielonych ID.
     */
    if (id_ != BLANK_ID) {
        freed_ids_.insert(id_);
        assigned_ids_.erase(id_);
    }

    id_ = other.id_;
    other.id_ = BLANK_ID;

    return *this;
}


Package::~Package() {
    if (id_ != BLANK_ID) {
        insert_if_not_exists(freed_ids_, id_);
        erase_if_exists(assigned_ids_, id_);
    }
}
