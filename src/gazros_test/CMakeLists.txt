cmake_minimum_required(VERSION 2.8.3)
project(gazros_test)

find_package(catkin REQUIRED COMPONENTS
  roscpp
  tf
  geometry_msgs
  sensor_msgs
  gazebo_ros
  gazebo_plugins
)

find_package(gazebo REQUIRED)
catkin_package(
     INCLUDE_DIRS include
#  LIBRARIES gazros_test
     DEPENDS roscpp gazebo_ros
     CATKIN_DEPENDS gazebo_plugins gazebo_ros roscpp
)

set(CMAKE_CXX_FLAGS "-std=c++11 ${CMAKE_CXX_FLAGS}")

link_directories(${GAZEBO_LIBRARY_DIRS})
include_directories(include)
include_directories(
  ${Boost_INCLUDE_DIR}
  ${catkin_INCLUDE_DIRS}
  ${GAZEBO_INCLUDE_DIRS}
  ${OGRE_INCLUDE_DIRS}/Paging # workaround for: "OgrePagedWorldSection.h: No such file or directory"
)

add_library(light_sensor_gazebo src/light_sensor_plugin.cpp)

add_executable(tf_broadcaster src/tf_broadcaster.cpp)
add_executable(tf_listener src/tf_listener.cpp)
add_executable(timid_robot src/Timid.cpp)
add_executable(line_follower src/LineFollower.cpp)
# add_executable(infrared_listener src/IRListener.cpp)

target_link_libraries(tf_broadcaster ${catkin_LIBRARIES})
target_link_libraries(tf_listener ${catkin_LIBRARIES})
target_link_libraries(timid_robot ${catkin_LIBRARIES})
target_link_libraries(line_follower ${catkin_LIBRARIES})
target_link_libraries(light_sensor_gazebo ${catkin_LIBRARIES} ${GAZEBO_LIBRARIES} CameraPlugin)
# target_link_libraries(infrared_listener ${catkin_LIBRARIES})

add_dependencies(infrared_listener sensor_msgs_generate_messages_cpp)
