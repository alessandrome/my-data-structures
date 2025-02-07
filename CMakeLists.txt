cmake_minimum_required(VERSION 3.30)
#project(my_data_structures)

set(CMAKE_CXX_STANDARD 17)

#include_directories(basic)
#include_directories(templated)
#include_directories(templated/AVLTree)
#include_directories(templated/Linear)
#include_directories(tests)
#
## Lista dei test da compilare separatamente
#set(TEST_SOURCES
#        tests/stack_tests.cpp
#        tests/templated_bstree_tests.cpp
#        tests/templated_deque_tests.cpp
#        tests/templated_list_tests.cpp
#        tests/templated_queue_tests.cpp
#        tests/templated_stack_tests.cpp
#)
#
## Creare un eseguibile separato per ogni test
#foreach(TEST_SRC ${TEST_SOURCES})
#    get_filename_component(TEST_NAME ${TEST_SRC} NAME_WE)
#    add_executable(${TEST_NAME} ${TEST_SRC})
#    target_link_libraries(${TEST_NAME} my_data_structures)
#    add_test(NAME ${TEST_NAME} COMMAND ${TEST_NAME})
#endforeach()

#add_executable(my_data_structures
#        basic/List.cpp
#        basic/List.h
#        basic/Stack.cpp
#        basic/Stack.h
#        templated/AVLTree/AVLTree.h
#        templated/AVLTree/AVLTree.tpp
#        templated/AVLTree/AVLTreeNode.h
#        templated/AVLTree/AVLTreeNode.tpp
#        templated/Linear/Deque.h
#        templated/Linear/Deque.tpp
#        templated/Linear/DoubleLinkedList.h
#        templated/Linear/DoubleLinkedList.tpp
#        templated/Linear/List.h
#        templated/Linear/List.tpp
#        templated/Linear/Queue.h
#        templated/Linear/Queue.tpp
#        templated/Linear/Stack.h
#        templated/Linear/Stack.tpp
#        templated/BSTree.h
#        templated/BSTree.tpp
#        templated/BSTreeNode.h
#        templated/BSTreeNode.tpp
#        tests/stack_tests.cpp
#        tests/templated_bstree_tests.cpp
#        tests/templated_deque_tests.cpp
#        tests/templated_list_tests.cpp
#        tests/templated_queue_tests.cpp
#        tests/templated_stack_tests.cpp)


project(my_data_structures)

# Abilita il supporto ai test in CMake
enable_testing()

# Aggiungi una libreria per le strutture dati
add_library(my_data_structures
        basic/List.cpp
        basic/Stack.cpp
)

# Lista dei test da compilare separatamente
set(TEST_SOURCES
        tests/stack_tests.cpp
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
    target_link_libraries(${TEST_NAME} my_data_structures)
    add_test(NAME ${TEST_NAME} COMMAND ${TEST_NAME})
endforeach()
