//
// Created by pilecki on 11.12.2019.
//

#include "storage_types.hpp"

Package&& PackageQueue::pop() {
    if (PackageQueue::get_queue_type() == PackageQueueType::FIFO) {
        return std::move(products.front());
    }
    else {
        return std::move(products.back());
    }
}
