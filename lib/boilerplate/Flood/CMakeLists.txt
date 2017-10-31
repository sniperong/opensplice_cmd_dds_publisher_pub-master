cmake_minimum_required(VERSION 2.8.3)
project(rti_ros)

MESSAGE("BUILDING LIBRARIES IN:")
MESSAGE(${CMAKE_CURRENT_SOURCE_DIR})

include_directories(
    ${CMAKE_CURRENT_SOURCE_DIR}/lib/boilerplate/Flood
)

file(GLOB SOURCE_Flood
    ${CMAKE_CURRENT_SOURCE_DIR}/lib/boilerplate/Flood/Flood.cxx
    ${CMAKE_CURRENT_SOURCE_DIR}/lib/boilerplate/Flood/*Plugin.cxx
    ${CMAKE_CURRENT_SOURCE_DIR}/lib/boilerplate/Flood/*Support.cxx
    ${CMAKE_CURRENT_SOURCE_DIR}/lib/boilerplate/Flood/*Boilerplate.cpp
)

