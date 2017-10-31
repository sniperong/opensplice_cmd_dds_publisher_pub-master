cmake_minimum_required(VERSION 2.8.3)
project(rti_ros)

MESSAGE("BUILDING LIBRARIES IN:")
MESSAGE(${CMAKE_CURRENT_SOURCE_DIR})

include_directories(
    ${CMAKE_CURRENT_SOURCE_DIR}/lib/boilerplate/ActuateControl
)

file(GLOB SOURCE_ActuateControl
    ${CMAKE_CURRENT_SOURCE_DIR}/lib/boilerplate/ActuateControl/ActuateControl.cxx
    ${CMAKE_CURRENT_SOURCE_DIR}/lib/boilerplate/ActuateControl/*Plugin.cxx
    ${CMAKE_CURRENT_SOURCE_DIR}/lib/boilerplate/ActuateControl/*Support.cxx
    ${CMAKE_CURRENT_SOURCE_DIR}/lib/boilerplate/ActuateControl/*Boilerplate.cpp
)

