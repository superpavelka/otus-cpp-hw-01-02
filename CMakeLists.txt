cmake_minimum_required(VERSION 3.5)

project(ip_filter)

add_executable(ip_filter ip_filter.cpp)

set_target_properties(
        ip_filter PROPERTIES
        CXX_STANDARD 14
        CXX_STANDARD_REQUIRED ON
		)      

if (MSVC)
    target_compile_options(ip_filter PRIVATE
        /W4
    )
else ()
    target_compile_options(ip_filter PRIVATE
        -Wall -Wextra -pedantic -Werror
    )
endif()