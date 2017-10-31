cmake_minimum_required(VERSION 2.8.3)
project(rti_ros)

MESSAGE("BUILDING LIBRARIES IN:")
MESSAGE(${CMAKE_CURRENT_SOURCE_DIR})

include_directories(
    ${CMAKE_CURRENT_SOURCE_DIR}/lib/boilerplate/ActuateStatus
)

file(GLOB SOURCE_ActuateStatus
    ${CMAKE_CURRENT_SOURCE_DIR}/lib/boilerplate/ActuateStatus/ActuateStatus.cxx
    ${CMAKE_CURRENT_SOURCE_DIR}/lib/boilerplate/ActuateStatus/*Plugin.cxx
    ${CMAKE_CURRENT_SOURCE_DIR}/lib/boilerplate/ActuateStatus/*Support.cxx
    ${CMAKE_CURRENT_SOURCE_DIR}/lib/boilerplate/ActuateStatus/*Boilerplate.cpp
)

