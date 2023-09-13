cmake_minimum_required(VERSION 3.10)


project(iptest )




add_executable(iptest ip_filter.cpp)


set_target_properties(iptest PROPERTIES
    CXX_STANDARD 14
    CXX_STANDARD_REQUIRED ON
)
target_include_directories(iptest
    PRIVATE "${CMAKE_BINARY_DIR}"
)





if (MSVC)
    target_compile_options(iptest PRIVATE
        /W4
    )
    
else ()
    target_compile_options(iptest PRIVATE
        -Wall -Wextra -pedantic -Werror
    )
    
endif()




