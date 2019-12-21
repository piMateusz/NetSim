//
// Created by pilecki on 11.12.2019.
//

#ifndef NETSIM_PACKAGE_HPP
#define NETSIM_PACKAGE_HPP

#include "types.hpp"
#include <set>

class Package{
    private:
        static const elementID deleted_id = 0;
        static std::set<elementID> assigned_IDs;
        static std::set<elementID> freed_IDs;
        elementID id_number = deleted_id;
    public:
        Package();
        Package(Package &&package);
        Package& operator=(Package&& package);
        elementID get_id() const { return id_number;}
        ~Package();
};
#endif //NETSIM_PACKAGE_HPP
