file(COPY ${CMAKE_SOURCE_DIR}/robin/models/hwd-digits-train.rb
     DESTINATION ${CMAKE_CURRENT_BINARY_DIR})

file(COPY ${CMAKE_SOURCE_DIR}/robin/models/hwd-digits-test.rb
     DESTINATION ${CMAKE_CURRENT_BINARY_DIR})

add_executable(hwd-digit
	handWrittenDigitTraining.cpp
)

target_link_libraries(hwd-digit
	${ROBIN_COMMON_LIBS}
	${ADDITIONAL_LIBRARIES}
)

install(TARGETS hwd-digit
# In order to export target, uncomment next line
#   EXPORT ${PROJECT_EXPORT}
  RUNTIME DESTINATION bin
  DESTINATION "${ROBIN_BIN_INSTALL_DIR}" COMPONENT hwd-digit)
