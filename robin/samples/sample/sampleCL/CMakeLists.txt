add_executable(sampleCL
	sampleCL.cpp
)

target_link_libraries(sampleCL
	${ROBIN_COMMON_LIBS}
	${ADDITIONAL_LIBRARIES}
)

install(TARGETS sampleCL
# In order to export target, uncomment next line
#   EXPORT ${PROJECT_EXPORT}
  RUNTIME DESTINATION bin
  DESTINATION "${ROBIN_BIN_INSTALL_DIR}" sampleCL)
