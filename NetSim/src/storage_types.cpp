//
// Created by pilecki on 11.12.2019.
//

#include "storage_types.hpp"

PackageQueue::PackageQueue(const PackageQueueType& Type){
    queueType = Type;
}
PackageQueue::get_queue_type () const {
    return queueType;
}
PackageQueue::pop() const {
    switch (queueType)
    {
        case FIFO:
            auto popped = std::move(products.front())
            return popped;
        case LIFO;
            auto popped = std::move(products.back())
            return popped;
    }
}
