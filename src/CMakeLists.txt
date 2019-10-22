cmake_minimum_required(VERSION 3.0)
project(NIB C)

set(CMAKE_C_STANDARD 11)

add_executable(NIB main.c nib.c nib.h)