cmake_minimum_required (VERSION 2.6)

# --------- Includes -----------
include_directories(${INCLUDE_DIR})
include_directories(${QPBO_INCLUDE_DIR})
include_directories(${HOCR_INCLUDE_DIR})


set(stereo-fusion_SOURCES
  main-stereo-fusion.cpp
  )
add_executable(stereo-fusion-exe ${stereo-fusion_SOURCES})
set_property(TARGET stereo-fusion-exe PROPERTY CXX_STANDARD 11)
target_link_libraries(stereo-fusion-exe
  ${STEREO-QPBO_EXE_LIB_DEP}
  )

 
if(CMAKE_VERBOSITY GREATER 0)
message(STATUS "Added target stereo-fusion (exe)")
endif(CMAKE_VERBOSITY GREATER 0)
