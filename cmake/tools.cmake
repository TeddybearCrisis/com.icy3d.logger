# this macro inits and updates all submodules in the repo at configure time
# please make sure the submodule was added with:
# git submodule add --depth 1 [repo-url]'
# otherwise jenkins will fail
macro(initAllGitSubmodules)
    find_package(Git QUIET)
    if (GIT_FOUND AND EXISTS "${PROJECT_SOURCE_DIR}/.git")
        # Update submodules as needed
        option(GIT_SUBMODULE "Check submodules during build" ON)
        if (GIT_SUBMODULE)
            message(STATUS "Submodule update")
            execute_process(COMMAND ${GIT_EXECUTABLE} submodule update --depth 1 --init --recursive
                            WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
                            RESULT_VARIABLE GIT_SUBMOD_RESULT)
            if (NOT GIT_SUBMOD_RESULT EQUAL "0")
                message(FATAL_ERROR "git submodule update --init failed with ${GIT_SUBMOD_RESULT},
                please checkout submodules")
            endif ()
        endif ()
    endif ()

endmacro(initAllGitSubmodules)

macro(initGitSubmodule PATH VERSION)
    find_package(Git QUIET)
    if (GIT_FOUND AND EXISTS "${PROJECT_SOURCE_DIR}/.git")

        # this condition is a clion hack as debug and release configurations are run simultaniously
        # without this condition clion tries to download it 2 times at the same time causing errors
        string(TOLOWER ${CMAKE_BUILD_TYPE} BUILD_TYPE_LOWER)
        set(ABSOLUTE_PATH "${PROJECT_SOURCE_DIR}/${PATH}")
        if (BUILD_TYPE_LOWER STREQUAL "debug")

            # Update submodules as needed
            option(GIT_SUBMODULE "Check submodules during build" ON)
            if (GIT_SUBMODULE)
                # Update submodules as needed
                message(STATUS "${PATH} Submodule update")
                execute_process(COMMAND ${GIT_EXECUTABLE} submodule update --depth 1 --init
                                WORKING_DIRECTORY ${ABSOLUTE_PATH}
                                RESULT_VARIABLE GIT_SUBMOD_RESULT
                                )
                #OUTPUT_QUIET
                if (NOT GIT_SUBMOD_RESULT EQUAL "0")
                    message(FATAL_ERROR "git submodule update --depth 1 --init in ${ABSOLUTE_PATH}
                    failed with ${GIT_SUBMOD_RESULT}, please checkout submodules")
                endif ()

                # fetch the specific version
                message(STATUS "${PATH} checking out version: ${VERSION}")

#                execute_process(COMMAND ${GIT_EXECUTABLE} checkout ${VERSION}
#                                WORKING_DIRECTORY ${ABSOLUTE_PATH}
#                                RESULT_VARIABLE GIT_SUBMOD_CHECKOUT_RESULT
#                                )
                #-q  OUTPUT_QUIET
                execute_process(COMMAND ${GIT_EXECUTABLE} -C "${ABSOLUTE_PATH}" checkout ${VERSION}
                                RESULT_VARIABLE GIT_SUBMOD_CHECKOUT_RESULT
                                )

                if (NOT GIT_SUBMOD_CHECKOUT_RESULT EQUAL "0")
                    message(FATAL_ERROR "git checkout ${VERSION} in ${ABSOLUTE_PATH}
                    failed with ${GIT_SUBMOD_CHECKOUT_RESULT}, please checkout submodules")
                endif ()
            endif ()
        else ()
            message(STATUS "ignoring submodule update. please make sure debug cmake script has run before
            ${CMAKE_BUILD_TYPE}")
        endif ()
    endif ()
endmacro(initGitSubmodule)

macro(forceMsvcStaticBuild)
    # force static runtime libraries for msvc builds
    if (MSVC)

        add_definitions(
                -DCMAKE_WINDOWS_EXPORT_ALL_SYMBOLS=TRUE
                -DBUILD_SHARED_LIBS=TRUE
        )

        set(variables
            CMAKE_CXX_FLAGS_DEBUG
            CMAKE_CXX_FLAGS_RELEASE
            )
        foreach (variable ${variables})
            if (${variable} MATCHES "/MD")
                string(REGEX REPLACE "/MD" "/MT" ${variable} "${${variable}}")
            endif ()
        endforeach ()
    endif ()
endmacro(forceMsvcStaticBuild)
