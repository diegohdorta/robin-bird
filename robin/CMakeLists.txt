cmake_minimum_required(VERSION 3.9)
project(robin-bird VERSION 1.0.0 DESCRIPTION "Robin Bird")

# Find source files
file(GLOB SOURCES "${PROJECT_SOURCE_DIR}/robin-core/*.cpp")
file(GLOB SOURCES "${PROJECT_SOURCE_DIR}/robin-nn/*.cpp")

# Create shared library
add_library(${PROJECT_NAME} SHARED ${SOURCES})

# Install library
install(TARGETS ${PROJECT_NAME} DESTINATION lib/${PROJECT_NAME})

# Install library headers
file(GLOB HEADERS "${PROJECT_SOURCE_DIR}/robin-nn/*.h")
file(GLOB HEADERS "${PROJECT_SOURCE_DIR}/robin-core/*.h")

include(GNUInstallDirs)

install(FILES ${HEADERS} DESTINATION include/${PROJECT_NAME})

