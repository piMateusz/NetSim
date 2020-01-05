//
// Created by pilecki on 11.12.2019.
//

#ifndef NETSIM_HELPERS_HPP
#define NETSIM_HELPERS_HPP
#include <iostream>
#include <random>
std::random_device rd;
std::mt19937 rng(rd());

double probability_generator_1() {
    return std::generate_canonical<double, 10>(rng);
}
#endif //NETSIM_HELPERS_HPP
