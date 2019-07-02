cmake_minimum_required(VERSION 3.9)
project(robin-bird VERSION 1.0.0 DESCRIPTION "Robin Bird")

# Compile the Robin Bird library
add_subdirectory(robin)

# Compile all the examples
add_subdirectory(examples)

