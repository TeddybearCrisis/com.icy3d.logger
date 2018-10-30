cmake_minimum_required(VERSION 3.4.1)
project(com.icy3d.logger CXX)

set(CMAKE_INSTALL_PREFIX "${CMAKE_BINARY_DIR}/install")

include_directories(inc)
link_directories(lib/cppfs)
set(LIBS optimized cppfs debug cppfsd)

# force static runtime libraries for msvc builds
if(MSVC)
    set(variables
        CMAKE_CXX_FLAGS_DEBUG
        CMAKE_CXX_FLAGS_RELEASE
        )
    foreach(variable ${variables})
        if(${variable} MATCHES "/MD")
            string(REGEX REPLACE "/MD" "/MT" ${variable} "${${variable}}")
        endif()
    endforeach()
endif()

add_subdirectory(src)
add_library(${PROJECT_NAME} STATIC ${SOURCES})
target_link_libraries(${PROJECT_NAME} ${LIBS})

add_subdirectory(test)

install(TARGETS ${PROJECT_NAME} DESTINATION "${CMAKE_INSTALL_PREFIX}")

