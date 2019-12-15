//
// Created by pilecki on 11.12.2019.
//

#ifndef NETSIM_PACKAGE_HPP
#define NETSIM_PACKAGE_HPP

#include "types.hpp"
#include <set>

class Package{
    private:
        static std::set<elementID> assigned_IDs;
        static std::set<elementID> freed_IDs;
        elementID id_number;
    public:
        Package();
        Package(elementID id_num): id_number(id_num){}
        Package& operator=(const Package& package);
        elementID get_id() const { return id_number;}
};
#endif //NETSIM_PACKAGE_HPP
