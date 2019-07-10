add_subdirectory(lib)
#add_subdirectory(scripts)
#add_subdirectory(tools)

if (NOT INSTURMENT_FOR_FUZZING)
	add_subdirectory(samples)
endif ()
