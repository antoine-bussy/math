cmake_minimum_required(VERSION 3.8)
project(math)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

if(NOT CMAKE_COMPILER_IS_GNUCC OR CMAKE_CXX_COMPILER_VERSION VERSION_LESS 7.0)
    message(FATAL_ERROR "Require at least gcc-7.0")
endif()

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fconcepts" ) 

set(GCC_WARNING_FLAGS
    -Werror
    -Wall
    -Wextra
    -Wredundant-decls
    -Wcast-align
    -Wmissing-declarations
    -Wmissing-include-dirs
    -Wswitch-enum
    -Wswitch-default
    -Winvalid-pch
    -Wredundant-decls
    -Wformat=2
    -Wmissing-format-attribute
    -Wformat-nonliteral
    -flto
    -Wodr
)

# require hana library, may work with Boost >= 1.61, but was tested only with boost 1.64
find_package(Boost 1.64.0 REQUIRED)

enable_testing()

function(math_add_test module)
	string(REPLACE "/" "_" test_target ${module})
	set(test_target "test_${test_target}")
	add_executable(${test_target} ${module}.test.cpp)
	target_compile_options(${test_target} PRIVATE ${GCC_WARNING_FLAGS})
	add_test(${module} ${test_target})
endfunction()

math_add_test(group/geometric)
math_add_test(group/ordering)
math_add_test(algebra/geometric)
math_add_test(vector/addition)
math_add_test(geometry/slice)
math_add_test(geometry/rotation)
