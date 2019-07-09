set(ROBIN_BIRD_LIBRARY_SRC
    robin-nn.cpp
    robin-image.cpp
    math.h
    hwd.cpp
)

#add_library(robin SHARED ${ROBIN_BIRD_LIBRARY_SRC})

#set_target_properties(robin PROPERTIES
#   OUTPUT_NAME robin CLEAN_DIRECT_OUTPUT 1)
   
#set_target_properties(robin PROPERTIES COMPILE_FLAGS "-Wall -Wextra")

#file(GLOB HEADERS *.h)
#install(FILES ${HEADERS} DESTINATION include/${PROJECT_NAME})
#install(TARGETS  DESTINATION lib)


add_library(robin-static STATIC ${ROBIN_BIRD_LIBRARY_SRC})
set_target_properties(robin-static PROPERTIES OUTPUT_NAME robin CLEAN_DIRECT_OUTPUT 1)
set_target_properties(robin-static PROPERTIES COMPILE_FLAGS "-fPIC -fvisibility=default")

# Can't call add_library() without source files. Create an empty .c file,
# then link with the static library just recently built.
file(WRITE "${CMAKE_BINARY_DIR}/empty.c" "")
add_library(robin-shared SHARED "${CMAKE_BINARY_DIR}/empty.c")

target_link_libraries(robin-shared ${ROBIN_COMMON_LIBS}	${ADDITIONAL_LIBRARIES})

set_target_properties(robin-shared PROPERTIES OUTPUT_NAME robin CLEAN_DIRECT_OUTPUT 1)

#target_link_libraries(robin-shared -Wl,--version-script=${CMAKE_CURRENT_SOURCE_DIR}/librobin.sym)


include_directories(${CMAKE_CURRENT_SOURCE_DIR}/robin/lib)

install(
	TARGETS robin-static robin-shared
	DESTINATION ${CMAKE_INSTALL_FULL_LIBDIR}
)

install(FILES
	robin-nn.h
	math.h
	robin-image.h
	hwd.h
DESTINATION "${CMAKE_INSTALL_FULL_INCLUDEDIR}/robin")


