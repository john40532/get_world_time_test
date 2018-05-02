cmake_minimum_required(VERSION 2.8.3)
project(get_world_time_test)

find_package(catkin REQUIRED COMPONENTS
  roscpp
  gazebo_ros
  std_srvs
)

find_package(gazebo REQUIRED)

catkin_package(
)

include_directories(${Boost_INCLUDE_DIR} ${catkin_INCLUDE_DIRS} ${GAZEBO_INCLUDE_DIRS})

link_directories(${GAZEBO_LIBRARY_DIRS})
list(APPEND CMAKE_CXX_FLAGS "${GAZEBO_CXX_FLAGS}")
add_executable(ros_get_world_time ros_get_world_time.cpp)
target_link_libraries(ros_get_world_time
    ${catkin_LIBRARIES}
    ${GAZEBO_LIBRARIES}
)
