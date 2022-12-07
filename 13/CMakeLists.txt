cmake_minimum_required(VERSION 3.2)



project(ProjestWithGTest)



# Lookup for pre-built gtest
find_package(GTest)

# Main target
add_executable(
    containers
    src/main.cpp
    src/lst.h
    src/lst_src.h
    src/posl_c.h
    src/posl_c_src.h
)

# Test target
add_executable(
    conteiner_test
    test/test_lst.cpp
    test/test_posl.cpp
    test/pch.h

)

# Add src to the include directories for the test target
target_include_directories(
    conteiner_test PRIVATE
    "${CMAKE_CURRENT_SOURCE_DIR}/src"
)
# Add googletest to the include directories for the test target
target_include_directories(
    conteiner_test PRIVATE
    ${GTEST_INCLUDE_DIRS}
)

# Link test target against gtest libraries
target_link_libraries(
    conteiner_test PRIVATE
    ${GTEST_BOTH_LIBRARIES}
)

if (MSVC)
    target_compile_options(
        containers PRIVATE
        /W4
    )
    target_compile_options(
        conteiner_test PRIVATE
        /W4
    )
else ()
    target_compile_options(
        containers PRIVATE
        -Wall -Wextra -pedantic -Werror
    )
    target_compile_options(
        conteiner_test PRIVATE
        -Wall -Wextra -pedantic -Werror
    )
endif()