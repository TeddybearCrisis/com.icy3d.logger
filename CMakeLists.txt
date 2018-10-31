cmake_minimum_required(VERSION 3.4.1)
include(cmake/tools.cmake)

project(com.icy3d.logger CXX)

set(CMAKE_INSTALL_PREFIX "${CMAKE_BINARY_DIR}/install")

initGitSubmodule()
forceMsvcStaticBuild()

include_directories(inc)
link_directories(lib/cppfs)
set(ICY_LOGGER_LIBS optimized cppfs debug cppfsd)



add_subdirectory(src)
add_library(${PROJECT_NAME} STATIC ${SOURCES})
target_link_libraries(${PROJECT_NAME} ${ICY_LOGGER_LIBS})




add_subdirectory(test)

install(TARGETS ${PROJECT_NAME} DESTINATION "${CMAKE_INSTALL_PREFIX}")