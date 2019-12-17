//
// Created by pilecki on 11.12.2019.
//

#include "storage_types.hpp"

Package&& PackageQueue::pop(){
    switch (PackageQueue::get_queue_type())
    {
        case PackageQueueType::FIFO:
            auto popped_fifo = Package(std::move(products.front()))
            return popped_fifo;
        case PackageQueueType ::LIFO:
            auto popped_lifo = Package(std::move(products.back()))
            return popped_lifo;
    }
}
