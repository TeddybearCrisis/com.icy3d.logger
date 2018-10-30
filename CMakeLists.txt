cmake_minimum_required(VERSION 3.4.1)
project(com.icy3d.logger CXX)

include_directories(inc)

add_subdirectory(src)
add_library(${PROJECT_NAME} ${SOURCES})

