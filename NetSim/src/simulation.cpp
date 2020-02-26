//
// Created by Jean Jacob on 2020-01-19.
//
#include "simulation.hpp"

void simulate(Factory& f, TimeOffset d){
    for (Time time = 1; time <= d; time ++){
        try {
            f.do_deliveries(time);
            f.do_package_passing();
            f.do_work(time);
        }
        catch(std::logic_error &){
            throw std::logic_error(reinterpret_cast<const char *>('n'));
        }
    }
}


