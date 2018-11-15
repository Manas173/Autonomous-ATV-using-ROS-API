cmake_minimum_required(VERSION 2.8.3)
project(beginner_tutorials)

## Find catkin and any catkin packages
find_package(catkin REQUIRED COMPONENTS roscpp tf rospy std_msgs genmsg pcl_ros laser_geometry)
## Declare ROS messages and services
#add_message_files(FILES Num.msg)
#add_service_files(FILES AddTwoInts.srv)

## Generate added messages and services
generate_messages(DEPENDENCIES std_msgs)

## Declare a catkin package
catkin_package()

## Build talker and listener
include_directories(include ${catkin_INCLUDE_DIRS})

#add_executable(talker src/talker.cpp)
#target_link_libraries(talker ${catkin_LIBRARIES})
#add_dependencies(talker beginner_tutorials_generate_messages_cpp)

#add_executable(nnode src/nnode.cpp)
#target_link_libraries(nnode ${catkin_LIBRARIES})
#add_dependencies(nnode beginner_tutorials_generate_messages_cpp)

#add_executable(listener src/listener.cpp)
#target_link_libraries(listener ${catkin_LIBRARIES})
#add_dependencies(listener beginner_tutorials_generate_messages_cpp)

#add_executable(code src/scan.cpp)
#target_link_libraries(code ${catkin_LIBRARIES})
#add_dependencies(code beginner_tutorials_generate_messages_cpp)

#add_executable(try src/try.cpp)
#target_link_libraries(try ${catkin_LIBRARIES})
#add_dependencies(try beginner_tutorials_generate_messages_cpp)

#add_executable(pc src/pc.cpp)
#target_link_libraries(pc ${catkin_LIBRARIES})
#add_dependencies(pc beginner_tutorials_generate_messages_cpp)

#add_executable(tf src/tf.cpp)
#target_link_libraries(tf ${catkin_LIBRARIES})
#add_dependencies(tf beginner_tutorials_generate_messages_cpp)

#add_executable(scan1 src/scan1.cpp)
#target_link_libraries(scan1 ${catkin_LIBRARIES})
#add_dependencies(scan1 beginner_tutorials_generate_messages_cpp)

#add_executable(scan2 src/scan2.cpp)
#target_link_libraries(scan2 ${catkin_LIBRARIES})
#add_dependencies(scan2 beginner_tutorials_generate_messages_cpp)

#add_executable(test1 src/test1.cpp)
#target_link_libraries(test1 ${catkin_LIBRARIES})
#add_dependencies(test1 beginner_tutorials_generate_messages_cpp)

add_executable(scan3 src/scan3.cpp)
target_link_libraries(scan3 ${catkin_LIBRARIES})
add_dependencies(scan3 beginner_tutorials_generate_messages_cpp)

add_executable(hidud src/hidude.cpp)
target_link_libraries(hidud ${catkin_LIBRARIES})
add_dependencies(hidud beginner_tutorials_generate_messages_cpp)

add_executable(marker src/marker.cpp)
target_link_libraries(marker ${catkin_LIBRARIES})
add_dependencies(marker beginner_tutorials_generate_messages_cpp)

#add_executable(cloud src/cloud.cpp)
#target_link_libraries(cloud ${catkin_LIBRARIES})
#add_dependencies(cloud beginner_tutorials_generate_messages_cpp)

add_executable(tf_broad src/tf_broad.cpp)
target_link_libraries(tf_broad ${catkin_LIBRARIES})
add_dependencies(tf_broad beginner_tutorials_generate_messages_cpp)

add_executable(servo src/servo.cpp)
target_link_libraries(servo ${catkin_LIBRARIES})
add_dependencies(servo beginner_tutorials_generate_messages_cpp)

add_executable(servo_tf src/servo_tf.cpp)
target_link_libraries(servo_tf ${catkin_LIBRARIES})
add_dependencies(servo_tf beginner_tutorials_generate_messages_cpp)

add_executable(trans src/trans.cpp)
target_link_libraries(trans ${catkin_LIBRARIES})
add_dependencies(trans beginner_tutorials_generate_messages_cpp)

add_executable(servo1 src/servo1.cpp)
target_link_libraries(servo1 ${catkin_LIBRARIES})
add_dependencies(servo1 beginner_tutorials_generate_messages_cpp)

add_executable(my src/my.cpp)
target_link_libraries(my ${catkin_LIBRARIES})
add_dependencies(my beginner_tutorials_generate_messages_cpp)

add_executable(servo2 src/servo2.cpp)
target_link_libraries(servo2 ${catkin_LIBRARIES})
add_dependencies(servo2 beginner_tutorials_generate_messages_cpp)


