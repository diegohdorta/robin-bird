set(CMAKE_NO_SYSTEM_FROM_IMPORTED ON)
set(PROJECT_NAME handwritten-digit)
set(FLAGS "-g3 -Ofast -std=c++11")
#set(FLAGS "-Wall -Wextra -g3 -Ofast -std=c++11")
project(${PROJECT_NAME})

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${FLAGS}")

include_directories(include)

file(COPY ${CMAKE_SOURCE_DIR}/robin/models/hwd-digits-train.rb
     DESTINATION ${CMAKE_CURRENT_BINARY_DIR})

file(COPY ${CMAKE_SOURCE_DIR}/robin/models/hwd-digits-test.rb
     DESTINATION ${CMAKE_CURRENT_BINARY_DIR})

include_directories("../../../lib/")

file(GLOB SOURCES "${PROJECT_SOURCE_DIR}/*.cpp" )

add_executable(${PROJECT_NAME} ${SOURCES})
#target_link_libraries(${PROJECT_NAME} ${ROBIN_COMMON_LIBS})
