cmake_minimum_required(VERSION 2.8.3)
project(rti_ros)

MESSAGE("BUILDING LIBRARIES IN:")
MESSAGE(${CMAKE_CURRENT_SOURCE_DIR})

include_directories(
    ${CMAKE_CURRENT_SOURCE_DIR}/lib/boilerplate/Environmental
)

file(GLOB SOURCE_Environmental
    ${CMAKE_CURRENT_SOURCE_DIR}/lib/boilerplate/Environmental/Environmental.cxx
    ${CMAKE_CURRENT_SOURCE_DIR}/lib/boilerplate/Environmental/*Plugin.cxx
    ${CMAKE_CURRENT_SOURCE_DIR}/lib/boilerplate/Environmental/*Support.cxx
    ${CMAKE_CURRENT_SOURCE_DIR}/lib/boilerplate/Environmental/*Boilerplate.cpp
)

