file(COPY ${CMAKE_SOURCE_DIR}/media
     DESTINATION ${CMAKE_CURRENT_BINARY_DIR})

add_executable(hwd-digit-input
	handWrittenDigitInputCL.cpp
)

target_link_libraries(hwd-digit-input
	${ROBIN_COMMON_LIBS}
	${ADDITIONAL_LIBRARIES}
)

install(TARGETS hwd-digit-input
# In order to export target, uncomment next line
#   EXPORT ${PROJECT_EXPORT}
  RUNTIME DESTINATION bin
  DESTINATION "${ROBIN_BIN_INSTALL_DIR}" COMPONENT hwd-digit-input)
