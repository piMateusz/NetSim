//
// Created by pilecki on 11.12.2019.
//

#include "storage_types.hpp"
Package&& PackageQueue::pop() {
    if (PackageQueue::get_queue_type() == PackageQueueType::LIFO){
        auto package_copy = Package(std::move(*products.rbegin()));
        products.pop_back();
        return std::move(package_copy);
    }
    else {
        auto package_copy = Package(std::move(*products.begin())) ;
        products.pop_front();
        return std::move(package_copy);
    }
}
