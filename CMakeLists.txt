cmake_minimum_required(VERSION 3.4.1)
project(com.icy3d.logger CXX)

include_directories(inc)
set(STATIC_LIBS lib/cppfs/cppfs)

add_subdirectory(src)
add_library(${PROJECT_NAME} ${SOURCES})
target_link_libraries(${PROJECT_NAME} STATIC ${STATIC_LIBS})

