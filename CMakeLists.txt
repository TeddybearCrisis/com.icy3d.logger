cmake_minimum_required(VERSION 3.4.1)
project(com.icy3d.logger CXX)



set(CMAKE_INSTALL_PREFIX "${CMAKE_BINARY_DIR}/install")
set(CMAKE_DEBUG_POSTFIX "d" CACHE STRING "Set debug library postfix")

include(cmake/tools.cmake)
initGitSubmodule(test/googletest tags/release-1.8.0)
forceMsvcStaticBuild()

include_directories(inc)
set(LIB_DIR "${PROJECT_SOURCE_DIR}/lib/cppfs")
set(LIBS optimized "${LIB_DIR}/cppfs.lib" debug "${LIB_DIR}/cppfsd.lib")

add_subdirectory(src)

# static lib
add_library(${PROJECT_NAME} ${SOURCES}) #static
set_target_properties(${PROJECT_NAME} PROPERTIES PUBLIC_HEADER "src/Log.h")
target_link_libraries(${PROJECT_NAME} ${LIBS})

add_subdirectory(test)

install(TARGETS ${PROJECT_NAME}
        ARCHIVE DESTINATION "${CMAKE_INSTALL_PREFIX}/lib" #that's the lib file
        LIBRARY DESTINATION "${CMAKE_INSTALL_PREFIX}/lib"
        RUNTIME DESTINATION "${CMAKE_INSTALL_PREFIX}/bin"
        PUBLIC_HEADER DESTINATION "${CMAKE_INSTALL_PREFIX}/include")

#shared - generating the dll
add_library(${PROJECT_NAME}_shared SHARED ${SOURCES})
target_link_libraries(${PROJECT_NAME}_shared ${LIBS})
set_target_properties(${PROJECT_NAME}_shared PROPERTIES OUTPUT_NAME ${PROJECT_NAME})

install(TARGETS ${PROJECT_NAME}_shared
        ARCHIVE DESTINATION "${CMAKE_INSTALL_PREFIX}/lib" #that's the lib file
        LIBRARY DESTINATION "${CMAKE_INSTALL_PREFIX}/lib"
        RUNTIME DESTINATION "${CMAKE_INSTALL_PREFIX}/bin"
        PUBLIC_HEADER DESTINATION "${CMAKE_INSTALL_PREFIX}/include")