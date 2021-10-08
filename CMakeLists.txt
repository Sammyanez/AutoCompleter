cmake_minimum_required(VERSION 3.20)
project(AutoCompleter)

set(CMAKE_CXX_STANDARD 14)

add_executable(AutoCompleter main.cpp autocompleter.h autocompleter.cpp words2.txt)
