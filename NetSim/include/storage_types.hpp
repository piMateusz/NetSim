//
// Created by pilecki on 11.12.2019.
//

#ifndef NETSIM_STORAGE_TYPES_HPP
#define NETSIM_STORAGE_TYPES_HPP

#include "package.hpp"
#include "types.hpp"
#include <crtdbg.h>
#include <list>

enum class PackageQueueType{
    LIFO, FIFO
};

class IPackageStockpile{
    public:
        using package_list_it = std::list<Package>::const_iterator;
        virtual bool empty() const= 0;
        virtual void push(Package &&package) = 0;
        virtual std::size_t size() const = 0;
        virtual ~IPackageStockpile(){}
        virtual package_list_it cbegin() const = 0;
        virtual package_list_it cend() const = 0;
        virtual package_list_it begin() const = 0;
        virtual package_list_it end() const = 0;
};

class IPackageQueue: public IPackageStockpile{
    public:
        virtual Package&& pop() = 0;
        virtual PackageQueueType get_queue_type()const= 0;
        virtual ~IPackageQueue(){};
};

class PackageQueue: public IPackageQueue{
private:
    PackageQueueType queue_type;
    std::list<Package> products;
public:
    virtual package_list_it cbegin() const override { return products.cbegin(); }
    virtual package_list_it cend() const override { return products.cend(); }
    virtual package_list_it begin() const override { return products.cbegin(); }
    virtual package_list_it end() const override { return products.cend(); }
    PackageQueue(const PackageQueueType& queueType): queue_type(queueType){};
    virtual Package&& pop() override ;
    virtual PackageQueueType get_queue_type()const override{ return queue_type;}
    virtual bool empty()const override { return products.empty();}
    virtual void push(Package &&package) override {products.emplace_back(std::move(package));}
    virtual std::size_t size()const override { return products.size();}
    ~PackageQueue(){};
};
#endif //NETSIM_STORAGE_TYPES_HPP