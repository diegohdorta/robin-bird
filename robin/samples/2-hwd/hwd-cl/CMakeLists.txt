file(COPY ${CMAKE_SOURCE_DIR}/robin/models/hwd-digits-train.rb
     DESTINATION ${CMAKE_CURRENT_BINARY_DIR})

file(COPY ${CMAKE_SOURCE_DIR}/robin/models/hwd-digits-test.rb
     DESTINATION ${CMAKE_CURRENT_BINARY_DIR})

add_executable(handwritten-digit
	handwritten-digit.cpp
)

target_link_libraries(handwritten-digit
	${ROBIN_COMMON_LIBS}
	${ADDITIONAL_LIBRARIES}
)
