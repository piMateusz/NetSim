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
        //const ??
        elementID id_number;
    public:
        Package();
        Package(Package &&package);
        Package& operator=(Package&& package);
        elementID get_id() const { return id_number;}
        ~Package(){freed_IDs.insert(id_number);};
};
#endif //NETSIM_PACKAGE_HPP
