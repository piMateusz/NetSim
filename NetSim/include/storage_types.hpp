//
// Created by pilecki on 11.12.2019.
//

#ifndef NETSIM_STORAGE_TYPES_HPP
#define NETSIM_STORAGE_TYPES_HPP

#include "package.hpp"
#include "types.hpp"
#include <list>

enum class PackageQueueType{
    LIFO, FIFO
};

class IPackageStockpile{
    public:
        virtual bool empty() const= 0;
        virtual void push(Package &package) = 0;
        virtual std::size_t size() const = 0;
        virtual ~IPackageStockpile(){}
};

class IPackageQueue: public IPackageStockpile{
    public:
        virtual Package&& pop() = 0;
        virtual PackageQueueType get_queue_type()const= 0;
        virtual ~IPackageQueue(){};
};

class PackageQueue: public IPackageQueue{
private:
    std::list<Package> products;
    PackageQueueType queue_type;
public:
    using package_list_it = std::list<Package>::const_iterator;
    package_list_it cbegin() const { return products.cbegin(); }
    package_list_it cend() const { return products.cend(); }
    package_list_it begin() const { return products.cbegin(); }
    package_list_it end() const { return products.cend(); }
    PackageQueue(const PackageQueueType& queueType): queue_type(queueType){};
    virtual Package&& pop() override ;
    virtual PackageQueueType get_queue_type()const override{ return queue_type;}
    virtual bool empty()const override { return products.empty();}
    virtual void push(Package &package) override {products.emplace_back(std::move(package));}
    virtual std::size_t size()const override { return products.size();}
    ~PackageQueue(){};
};
#endif //NETSIM_STORAGE_TYPES_HPP