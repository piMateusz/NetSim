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
        std::list<Package>::const_iterator package_list_it;
        virtual bool empty() const= 0;
        virtual void push(Package &package) = 0;
        virtual std::size_t size() = 0;
        virtual ~IPackageStockpile(){}
        //typename std::list<Package>::const_iterator cbegin() const { return package_list_it.cbegin(); }
        //typename std::list<Package>::const_iterator cend() const { return package_list_it.cend(); }
        //typename std::list<T>::const_iterator begin() const { return package_list_it.cbegin(); }
        //typename std::list<T>::const_iterator end() const { return package_list_it.cend(); }
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
    PackageQueue(const PackageQueueType& queueType): queue_type(queueType){};
    virtual Package&& pop() override ;
    virtual PackageQueueType get_queue_type()const override{ return queue_type;}
    virtual bool empty()const override { return products.empty();}
    virtual void push(Package &package) override {products.push_back(package);} // zamienic na emplace_back oraz move
    virtual std::size_t size() override { return products.size();}
    ~PackageQueue(){};
};
#endif //NETSIM_STORAGE_TYPES_HPP