set(CMAKE_NO_SYSTEM_FROM_IMPORTED ON)
set(PROJECT_NAME sample-cl)
set(FLAGS "-g3 -Ofast -std=c++11")

project(${PROJECT_NAME})
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${FLAGS}")

file(GLOB SOURCES "${PROJECT_SOURCE_DIR}/*.cpp")
include_directories("../../../lib/")

add_executable(${PROJECT_NAME} ${SOURCES})
