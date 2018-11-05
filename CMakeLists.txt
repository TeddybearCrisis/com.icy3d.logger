cmake_minimum_required(VERSION 3.4.1)
project(com.icy3d.logger CXX)

set(CMAKE_INSTALL_PREFIX "${PROJECT_SOURCE_DIR}/install")
set(CMAKE_DEBUG_POSTFIX "d" CACHE STRING "Set debug library postfix")

include(cmake/tools.cmake)
initGitSubmodule(test/googletest tags/release-1.8.0)
#forceMsvcStaticBuild()

include_directories(inc)
set(LIB_DIR "${PROJECT_SOURCE_DIR}/lib")
set(LIBS optimized "${LIB_DIR}/cppfs.lib" debug "${LIB_DIR}/cppfsd.lib")

add_subdirectory(src)
set(PUB_HEADERS
    "src/Log.h"
    "src/Formatter.h"
    )


# static lib
add_library(objLib OBJECT  ${SOURCES})
# shared libraries need PIC
set_property(TARGET ${objlib} PROPERTY POSITION_INDEPENDENT_CODE 1)
#target_link_libraries(objLib ${LIBS})


add_library(${PROJECT_NAME} SHARED $<TARGET_OBJECTS:objLib>)
set_target_properties(${PROJECT_NAME} PROPERTIES PUBLIC_HEADER "${PUB_HEADERS}")
target_link_libraries(${PROJECT_NAME} ${LIBS})

#add_subdirectory(test)

install(TARGETS ${PROJECT_NAME}
        ARCHIVE DESTINATION "${CMAKE_INSTALL_PREFIX}/lib/" #that's the lib file
        LIBRARY DESTINATION "${CMAKE_INSTALL_PREFIX}/lib/"
        RUNTIME DESTINATION "${CMAKE_INSTALL_PREFIX}/bin"
        PUBLIC_HEADER DESTINATION "${CMAKE_INSTALL_PREFIX}/include/${PROJECT_NAME}")

#shared - generating the dll
#add_library(${PROJECT_NAME}_shared SHARED $<TARGET_OBJECTS:objLib>)
#target_link_libraries(${PROJECT_NAME}_shared ${LIBS})
#set_target_properties(${PROJECT_NAME}_shared PROPERTIES OUTPUT_NAME ${PROJECT_NAME})
#
#install(TARGETS ${PROJECT_NAME}_shared
#        ARCHIVE DESTINATION "${CMAKE_INSTALL_PREFIX}/lib/" #that's the lib file
#        LIBRARY DESTINATION "${CMAKE_INSTALL_PREFIX}/lib/"
#        RUNTIME DESTINATION "${CMAKE_INSTALL_PREFIX}/bin"
#        PUBLIC_HEADER DESTINATION "${CMAKE_INSTALL_PREFIX}/include/${PROJECT_NAME}")