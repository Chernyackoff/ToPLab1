cmake_minimum_required(VERSION 3.22)
project(Lab1)

set(CMAKE_CXX_STANDARD 20)

add_executable(Lab1 main.cpp Person.hpp Person.cpp Vector.cpp FamilyMember.cpp FamilyMember.hpp
        Exceptions.hpp Exceptions.cpp FamilyTree.hpp FamilyTree.cpp UI.hpp UI.cpp
        )
