//
// Created by pilecki on 11.12.2019.
//

#ifndef NETSIM_SIMULATION_HPP
#define NETSIM_SIMULATION_HPP
//function simulate();
#include "Factory.hpp"

void simulate(Factory factory, TimeOffset d, std::function<void(Factory&, Time)>);

#endif //NETSIM_SIMULATION_HPP
