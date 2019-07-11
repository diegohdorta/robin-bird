file(COPY ${CMAKE_SOURCE_DIR}/media
     DESTINATION ${CMAKE_CURRENT_BINARY_DIR})

add_executable(handWrittenDigitInputCL
	handWrittenDigitInputCL.cpp
)

target_link_libraries(handWrittenDigitInputCL
	${ROBIN_COMMON_LIBS}
	${ADDITIONAL_LIBRARIES}
)
