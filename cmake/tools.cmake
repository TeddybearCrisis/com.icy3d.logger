
macro(forceMsvcStaticBuild)
    # force static runtime libraries for msvc builds
    if (MSVC)
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
