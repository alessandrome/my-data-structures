cmake_minimum_required(VERSION 3.28)
#project(my_data_structures)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

project(my_data_structures)

# Abilita il supporto ai test in CMake
enable_testing()

# Find Google Testing & Benchmarks packages
find_package(GTest CONFIG REQUIRED)
find_package(benchmark CONFIG REQUIRED)

# Definisci la directory che contiene i tuoi header template
#set(INCLUDE_DIRECTORIES basic)

# Aggiungi la directory degli include a tutte le target
#include_directories(${INCLUDE_DIRECTORIES})

# Lista dei test da compilare separatamente
set(TEST_SOURCES
        tests/templated_deque_tests.cpp
        tests/templated_list_tests.cpp
        tests/templated_vector_tests.cpp
        tests/templated_queue_tests.cpp
        tests/templated_stack_tests.cpp
        tests/templated_bstree_tests.cpp
        tests/templated_avltree_tests.cpp
)

# Creare un eseguibile separato per ogni test
foreach(TEST_SRC ${TEST_SOURCES})
    get_filename_component(TEST_NAME ${TEST_SRC} NAME_WE)
    add_executable(${TEST_NAME} ${TEST_SRC})
    target_link_libraries(${TEST_NAME} GTest::gtest GTest::gtest_main)
    add_test(NAME ${TEST_NAME} COMMAND ${TEST_NAME})
endforeach()

# List of benchmarks to compile and run independently
set(BENCHMARK_SOURCES
        benchmarks/templated_vector_benchmarks.cpp
)

# Create an executable for each benchmark file
foreach(BENCHMARK_SRC ${BENCHMARK_SOURCES})
    get_filename_component(BENCHMARK_NAME ${BENCHMARK_SRC} NAME_WE)
    add_executable(${BENCHMARK_NAME} ${BENCHMARK_SRC})
    target_link_libraries(${BENCHMARK_NAME} benchmark::benchmark)
endforeach()