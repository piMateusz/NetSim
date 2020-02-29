//
// Created by pilecki on 11.12.2019.
//

#ifndef NETSIM_REPORTS_HPP
#define NETSIM_REPORTS_HPP

#include "factory.hpp"

class IReportNotifier{
    virtual bool should_generate_report(Time time) = 0;
};

class SpecificTurnsReportNotifier: public IReportNotifier{
public:
    SpecificTurnsReportNotifier(std::set<Time> turns_number): turns_number_(turns_number){};
    virtual bool should_generate_report(Time time){ return std::find(truns_number_.begin(), turns_number_.end(), time) != turns_number_.end()};
private:
    std::set<Time> turns_number_
};

class IntervalReportNotifier: public IReportNotifier{
public:
    IntervalReportNotifier(TimeOffset time_interval): time_interval_(time_interval){};
    virtual bool should_generate_report(Time time){ return time%time_interval_ == 1;};
private:
    TimeOffset time_interval_
};

//TO DO
function generate_structure_report(Factory& factory, std::ostream& os);
function generate_simulation_turn_report(Factory& factory, std::ostream& os, Time time);
#endif //NETSIM_REPORTS_HPP
