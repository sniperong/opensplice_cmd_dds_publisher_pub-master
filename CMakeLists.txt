cmake_minimum_required(VERSION 2.8.3)
project(cmd_dds_publisher)

find_package(catkin REQUIRED COMPONENTS 
  tf
  geometry_msgs
)

# Make CMake aware of the cmake folder for local FindXXX scripts.
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH}
                      ${CMAKE_CURRENT_SOURCE_DIR}/cmake)

find_package(RTI REQUIRED)

catkin_package(
  INCLUDE_DIRS include src
  LIBRARIES dds_lib
  DEPENDS nddsc nddscpp nddscore 
)

set(NDDSHOME $ENV{NDDSHOME})

include_directories(
  ${catkin_INCLUDE_DIRS}
  ${NDDSHOME}/include
  ${NDDSHOME}/include/ndds
  include
  src
)

add_definitions(-DRTI_UNIX)

link_directories(
  ${NDDSHOME}/lib/x64Linux3gcc4.8.2
  ${NDDSHOME}/lib/armv6vfphLinux3.xgcc4.7.2
)

add_library(dds_lib
  src/Velocities.cxx
  src/VelocitiesPlugin.cxx
  src/VelocitiesSupport.cxx
)

target_link_libraries(dds_lib
  nddsc
  nddscpp
  nddscore
  ${CMAKE_DL_LIBS}
)

add_executable(Velocities_publisher
  src/Velocities_publisher.cxx
)

target_link_libraries(Velocities_publisher
  ${catkin_LIBRARIES}
  dds_lib
)

add_executable(Velocities_subscriber
  src/Velocities_subscriber.cxx
)

target_link_libraries(Velocities_subscriber
  ${catkin_LIBRARIES}
  dds_lib
)