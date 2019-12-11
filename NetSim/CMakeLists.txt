cmake_minimum_required(VERSION 3.15)
project(NetSim)

set(CMAKE_CXX_STANDARD 14)

add_executable(NetSim main.cpp include/package.hpp include/types.hpp include/storage_types.hpp src/package.cpp src/storage_types.cpp include/factory.hpp include/helpers.hpp include/nodes.hpp include/reports.hpp include/simulation.hpp)