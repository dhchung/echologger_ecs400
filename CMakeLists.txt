cmake_minimum_required(VERSION 3.0.2)
project(echologger_ecs400)

add_compile_options(-std=c++11)

find_package(catkin REQUIRED COMPONENTS
  roscpp
  sensor_msgs
  std_msgs
)

find_package(Boost REQUIRED COMPONENTS system)

file(GLOB SOURCES ${PROJECT_SOURCE_DIR}/classes/*.cpp)

catkin_package(
 INCLUDE_DIRS include
#  LIBRARIES echologger_ecs400
 CATKIN_DEPENDS roscpp sensor_msgs std_msgs
#  DEPENDS system_lib
)
include_directories(
include
  ${catkin_INCLUDE_DIRS}
  ${Boost_INCLUDE_DIRS}
)

link_libraries(${Boost_LIBRARIES})

add_executable(${PROJECT_NAME}_node src/main.cpp
${SOURCES})

target_link_libraries(${PROJECT_NAME}_node
  ${catkin_LIBRARIES}
  ${Boost_LIBRARIES}
)
