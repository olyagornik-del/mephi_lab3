cmake_minimum_required(VERSION 4.0)
project(lab3)

set(CMAKE_CXX_STANDARD 11)

add_executable(lab3
        main.cpp
        my_except.h
        core/DynamicArray.h
        core/LinkedList.h
        core/Sequences/Sequence.h
        core/Sequences/MutableArraySequence.h
        core/Sequences/MutableListSequence.h
        core/Sequences/ImmutableArraySequence.h
        core/Sequences/ImmutableListSequence.h
        core/Sequences/BitSequence.h
        scanValues.h
        menu.h
        SequenceOperations.h
        core/Sequences/ICollection.h)

add_executable(lab3_tests
        tests/test.cpp
        tests/testDynamicArray.cpp
        tests/testLinkedList.cpp
        tests/testArraySequence.cpp
        tests/testListSequence.cpp
        tests/testMutable.cpp
        tests/testImmutable.cpp
        core/Sequences/BitSequence.h
        tests/testBitSequence.cpp
        my_except.h
        core/DynamicArray.h
        core/LinkedList.h
        core/Sequences/Sequence.h
        core/Sequences/MutableArraySequence.h
        core/Sequences/MutableListSequence.h
        core/Sequences/ImmutableArraySequence.h
        core/Sequences/ImmutableListSequence.h
)
