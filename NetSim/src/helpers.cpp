//
// Created by PC on 02.01.2020.
//
#include <iostream>
#include <random>
#include "helpers.hpp"
std::random_device rd;
std::mt19937 rng(rd());

double probability_generator_1() {
    return std::generate_canonical<double, 10>(rng);
}
