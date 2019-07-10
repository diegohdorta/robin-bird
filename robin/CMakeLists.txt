if (ROBIN_BIRD)
    add_subdirectory(lib)
endif ()
#add_subdirectory(scripts)
#add_subdirectory(tools)

if (SAMPLES)
	add_subdirectory(samples)
endif ()
