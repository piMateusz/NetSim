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
private:
    std::list<Package> products;
    PackageQueueType queue_type;
public:
    PackageQueue(const PackageQueueType& queueType): queue_type(queueType){};
    virtual Package&& pop() override ;
    virtual PackageQueueType get_queue_type() override{ return queue_type;}
    virtual bool empty() override { return products.empty();}
    virtual void push(Package &package) override {products.push_back(package);} // zamienic na emplace_back oraz move
    virtual size_t size() override { return products.size();}
    ~PackageQueue();

};
#endif //NETSIM_STORAGE_TYPES_HPP