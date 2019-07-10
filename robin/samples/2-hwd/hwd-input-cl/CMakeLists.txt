file(COPY ${CMAKE_SOURCE_DIR}/media
     DESTINATION ${CMAKE_CURRENT_BINARY_DIR})

add_executable(handwritten-digit-file
	handwritten-digit-file.cpp
)

target_link_libraries(handwritten-digit-file
	${ROBIN_COMMON_LIBS}
	${ADDITIONAL_LIBRARIES}
)
