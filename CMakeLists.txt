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

    add_test_executable(test_MaxFlowSolver tests/MaxFlowSolver.cpp)
    add_test_executable(test_kruskal tests/kruskal.cpp)
    add_test_executable(test_lineal_search tests/test_lineal_search.cpp)
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
# Si se necesita especificar explícitamente las librerías
# target_link_libraries(tests ${googletest_BINARY_DIR}/lib/libgtest.a ${googletest_BINARY_DIR}/lib/libgtest_main.a)
