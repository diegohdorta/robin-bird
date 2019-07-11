add_executable(sampleCL
	sampleCL.cpp
)

target_link_libraries(sampleCL
	${ROBIN_COMMON_LIBS}
	${ADDITIONAL_LIBRARIES}
)
