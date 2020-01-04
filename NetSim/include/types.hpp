//
// Created by pilecki on 11.12.2019.
//

#ifndef NETSIM_TYPES_HPP
#define NETSIM_TYPES_HPP

#include "functional"

using elementID = int;
using Time = int;
using TimeOffset = int;
using ProbabilityGenerator = std::function<double()>;

#endif //NETSIM_TYPES_HPP
