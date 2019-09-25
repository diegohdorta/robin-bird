find_package(PkgConfig REQUIRED)

pkg_check_modules(GTKMM REQUIRED IMPORTED_TARGET gtkmm-3.0)
pkg_check_modules(CAIROMM REQUIRED IMPORTED_TARGET cairomm-1.0)
pkg_check_modules(OPENCV REQUIRED IMPORTED_TARGET opencv)

add_executable(handWrittenDigitInputUI
        handWrittenDigitInputUI.cpp main_window.cpp results.cpp main.cpp
)

target_link_libraries(handWrittenDigitInputUI
		${ROBIN_COMMON_LIBS}
        PkgConfig::GTKMM
        PkgConfig::CAIROMM
        PkgConfig::OPENCV
)

install(TARGETS handWrittenDigitInputUI
# In order to export target, uncomment next line
#   EXPORT ${PROJECT_EXPORT}
  RUNTIME DESTINATION bin
  DESTINATION "${ROBIN_BIN_INSTALL_DIR}" COMPONENT handWrittenDigitInputUI)
