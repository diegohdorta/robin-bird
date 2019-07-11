project(robin)
cmake_minimum_required(VERSION 3.9)
set(PROJECT_DESCRIPTION "experimental, small and flexible C++ machine learning library")
message(STATUS "Running CMake for ${PROJECT_NAME} (${PROJECT_DESCRIPTION})")

set(CMAKE_NO_SYSTEM_FROM_IMPORTED ON)

include(FindPkgConfig)
include(GNUInstallDirs)

set(ROBIN_COMMON_LIBS -Wl,-force_load robin-static)
set(ROBIN_COMMON_LIBS -Wl,-whole-archive robin-static -Wl,-no-whole-archive)
include_directories(robin/lib)

if (INSTURMENT_FOR_FUZZING)
	add_subdirectory(fuzz)
endif ()

find_program(CCACHE ccache)
if (CCACHE)
       message(STATUS "Using ccache from ${CCACHE}")
       set_property(GLOBAL PROPERTY RULE_LAUNCH_COMPILE ${CCACHE})
       set_property(GLOBAL PROPERTY RULE_LAUNCH_LINK ${CCACHE})
endif ()

include (FindPkgConfig)
if (NOT PKG_CONFIG_FOUND)
    message (FATAL_ERROR "pkg-config not found")
endif ()

pkg_check_modules (LIBPNG libpng16 REQUIRED)
if (NOT LIBPNG_FOUND)
    message(FATAL_ERROR "You don't seem to have libpng16 development libraries installed")
else ()
    include_directories (${LIBPNG_INCLUDE_DIRS})
    link_directories (${LIBPNG_LIBRARY_DIRS})
    link_libraries (${LIBPNG_LIBRARIES})
endif ()

set(PKG_CONFIG_REQUIRES "")
set(PKG_CONFIG_LIBDIR "\${prefix}/lib")
set(PKG_CONFIG_INCLUDEDIR "\${prefix}/include/robin")

string (REPLACE ";" " " ADDITIONAL_LIBRARIES_STR "${ADDITIONAL_LIBRARIES}")
set(PKG_CONFIG_LIBS "-L\${libdir} -lrobin ${ADDITIONAL_LIBRARIES_STR}")
unset(ADDITIONAL_LIBRARIES_STR)
set(PKG_CONFIG_CFLAGS "-I\${includedir}")

execute_process(
	COMMAND git log -1 --format=%h
	WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}
	OUTPUT_VARIABLE PROJECT_VERSION
	OUTPUT_STRIP_TRAILING_WHITESPACE
)
configure_file(
	"${CMAKE_CURRENT_SOURCE_DIR}/robin/cmake/robin.pc.cmake"
	"${CMAKE_CURRENT_BINARY_DIR}/${PROJECT_NAME}.pc"
)
install(FILES "${CMAKE_BINARY_DIR}/${PROJECT_NAME}.pc" DESTINATION lib/pkgconfig)
add_subdirectory(robin)
