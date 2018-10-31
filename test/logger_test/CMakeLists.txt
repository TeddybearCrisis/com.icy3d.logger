#-------------------
# Test
#-------------------

enable_testing()

include_directories(${PROJECT_SOURCE_DIR}/src)
#link_directories(${PROJECT_SOURCE_DIR}/lib/cppfs)

file(GLOB TEST_SRC_FILES *.cpp)

#add_executable(logger_test_exe LogTest.cpp)
#target_link_libraries(logger_test_exe gtest gtest_main ${LIBS} ${PROJECT_NAME})
#add_test(logger_test_exe Log_test)

# from list of files we'll create tests test_name.cpp -> test_name
foreach(_test_file ${TEST_SRC_FILES})
    get_filename_component(_test_name ${_test_file} NAME_WE)
    add_executable(${_test_name} ${_test_file})
    target_link_libraries(${_test_name} gtest gtest_main ${LIBS} ${PROJECT_NAME})
    add_test(${_test_name} ${_test_name})
    set_tests_properties(${_test_name} PROPERTIES TIMEOUT 5)
endforeach()