set(ROBIN_BIRD_LIBRARY_SRC
    math.cpp
    math.h
    robin-nn.cpp
    robin-nn.h
)

add_library(robin-static STATIC ${ROBIN_BIRD_LIBRARY_SRC})

set_target_properties(robin-static PROPERTIES
   OUTPUT_NAME robin CLEAN_DIRECT_OUTPUT 1)
   
set_target_properties(robin-static PROPERTIES COMPILE_FLAGS "-Wall -fPIC")
