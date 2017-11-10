cmake_minimum_required(VERSION 3.0)

project(DecisionTree VERSION 1.0)




add_subdirectory(src ${CMAKE_SOURCE_DIR}/lib/DecisionTree)
add_subdirectory(unitTests ${CMAKE_SOURCE_DIR}/buildUnitTest)