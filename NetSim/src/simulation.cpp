//
// Created by Jean Jacob on 2020-01-19.
//
#include "simulation.hpp"

void simulation(Factory factory, TimeOffset d, std::function<void(Factory&, Time)>){
    for (Time time = 1; time <= d; time ++){
        try {
            factory.do_deliveries(time);
            factory.do_package_passing();
            factory.do_work(time);
        }
        catch(std::logic_error &){
            throw std::logic_error(reinterpret_cast<const char *>('n'));
        }
    }
}


