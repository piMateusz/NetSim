//
// Created by pilecki on 11.12.2019.
//

#ifndef NETSIM_STORAGE_TYPES_HPP
#define NETSIM_STORAGE_TYPES_HPP

#include "package.hpp"
#include "types.hpp"

enum class PackageQueueType{
    LIFO, FIFO
};

class IPackageStockpile{
    private:
    public:
        virtual bool empty() = 0;
        virtual void push(Package &package) = 0;
        virtual size_t size() = 0;
        virtual ~IPackageStockpile(){}
};

class IPackageQueue: public IPackageStockpile{
    public:
        virtual Package pop() = 0;
        virtual PackageQueueType get_queue_type() = 0;
        virtual ~IPackageQueue(){};
};

class PackageQueue: public IPackageQueue{
};
#endif //NETSIM_STORAGE_TYPES_HPP
