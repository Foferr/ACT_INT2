cmake_minimum_required(VERSION 3.30)
project(unit_test)

set(CMAKE_CXX_STANDARD 17)

# Enable code coverage if requested
option(ENABLE_COVERAGE "Enable coverage reporting" ON)
if (ENABLE_COVERAGE)
    message(STATUS "Enabling coverage flags for GCC/Clang")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} --coverage -fprofile-arcs -ftest-coverage")
    set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} --coverage")
endif()

# Source files , prueba para sonarqube
set(SOURCES
        src/main.cpp
        src/MaxFlowSolver.h
        src/Kruskal.h
        src/linear_search.h
        src/traveling_salesman.h
)

# Definir el ejecutable principal
add_executable(unit_test ${SOURCES})

# Enable testing
option(ENABLE_TESTING "Enable a Unit Testing build." ON)

# Especifica las rutas para las pruebas
include_directories(${CMAKE_SOURCE_DIR}/src)
include_directories(${CMAKE_SOURCE_DIR}/tests)

# Download and use GoogleTest
include(FetchContent)
FetchContent_Declare(
    googletest
    GIT_REPOSITORY https://github.com/google/googletest.git
    GIT_TAG release-1.11.0
)
FetchContent_MakeAvailable(googletest)

# Add unit tests
if(ENABLE_TESTING)
    enable_testing()

    function(add_test_executable name source)
        add_executable(${name} ${source})
        target_link_libraries(${name} PRIVATE gtest gtest_main)
        if (ENABLE_COVERAGE)
            target_link_libraries(${name} PRIVATE gcov)
            target_compile_options(${name} PRIVATE --coverage -fprofile-arcs -ftest-coverage)
            target_link_options(${name} PRIVATE --coverage)
        endif()
        add_test(NAME ${name} COMMAND ${name})
    endfunction()

    # Añadir los ejecutables de prueba
    add_test_executable(test_MaxFlowSolver tests/MaxFlowSolver.cpp)
    add_test_executable(test_kruskal tests/kruskal.cpp)
    add_test_executable(test_linear_search tests/test_linear_search.cpp)
    add_test_executable(test_tsp tests/tsp.cpp)

    # Generate coverage reports
    if (ENABLE_COVERAGE)
        find_program(LCOV lcov)
        if (LCOV)
            add_custom_target(coverage
                COMMAND lcov --capture --directory . --output-file build/coverage.info
                COMMAND genhtml build/coverage.info --output-directory build/coverage_html
                COMMENT "Generating code coverage report"
                VERBATIM
            )
        else()
            message(WARNING "LCOV not found, coverage reporting will not be available")
        endif()
    endif()
endif()
