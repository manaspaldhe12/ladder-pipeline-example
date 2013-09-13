cmake_minimum_required(VERSION 2.6)
project(hubo-ladder-pipeline-example)

# install path variables
set(EXECUTABLE_OUTPUT_PATH ${PROJECT_SOURCE_DIR})
set(LIBRARY_OUTPUT_PATH ${PROJECT_SOURCE_DIR})
set(LIBRARY_INSTALL_PATH /usr/lib/)
set(BINARY_INSTALL_PATH /usr/local/bin/)

set(CMAKE_C_FLAGS "-std=gnu99")

#find_package(ach)

set( CMAKE_VERBOSE_MAKEFILE true )

file(GLOB ladderTest_source "ladder-pipeline-example.cpp")
file(GLOB pipeline-trajectory-follower_source "pipeline-trajectory-follower.cpp")

add_executable(ladderTest ${ladderTest_source})
target_link_libraries(ladderTest m rt ach huboparams )

add_executable(trajectory-follower ${pipeline-trajectory-follower_source})
target_link_libraries(trajectory-follower m rt ach huboparams )


