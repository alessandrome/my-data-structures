cmake_minimum_required(VERSION 3.30)
#project(my_data_structures)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

project(my_data_structures)

# Abilita il supporto ai test in CMake
enable_testing()

# Find Google Testing package
find_package(GTest CONFIG REQUIRED)

# Definisci la directory che contiene i tuoi header template
#set(INCLUDE_DIRECTORIES basic)

# Aggiungi la directory degli include a tutte le target
#include_directories(${INCLUDE_DIRECTORIES})

# Lista dei test da compilare separatamente
set(TEST_SOURCES
        tests/templated_deque_tests.cpp
        tests/templated_list_tests.cpp
        tests/templated_queue_tests.cpp
        tests/templated_stack_tests.cpp
        tests/templated_bstree_tests.cpp
        tests/templated_avltree_tests.cpp
)

# Creare un eseguibile separato per ogni test
foreach(TEST_SRC ${TEST_SOURCES})
    get_filename_component(TEST_NAME ${TEST_SRC} NAME_WE)
    add_executable(${TEST_NAME} ${TEST_SRC})
    target_link_libraries(${TEST_NAME} GTest::gtest GTest::gtest_main GTest::gmock GTest::gmock_main)
    add_test(NAME ${TEST_NAME} COMMAND ${TEST_NAME})
endforeach()
