project( stereo-qpbo )

# ----- CMAKE stuffs -----
cmake_minimum_required(VERSION 2.6.2)


# ----- Add /Defines depts -----
SET(INCLUDE_DIR ${stereo-qpbo_SOURCE_DIR}/include/)
SET(EXTERN_DIR ${stereo-qpbo_SOURCE_DIR}/extern/)
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${stereo-qpbo_SOURCE_DIR}/lib)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${stereo-qpbo_SOURCE_DIR}/lib)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)


# ----- Includes / libs  contrib -----
INCLUDE(${stereo-qpbo_SOURCE_DIR}/cmake/FindQPBO.cmake)
INCLUDE(${stereo-qpbo_SOURCE_DIR}/cmake/FindHOCR.cmake)
INCLUDE(${stereo-qpbo_SOURCE_DIR}/cmake/FindCIMG.cmake)


set(STEREO-QPBO_EXE_LIB_DEP
  ${QPBO_LIBRARIES} 
  ${HOCR_LIBRARIES}
  ${CIMG_LIBRARIES}
)


# ----- Defin global flags and versions -----
set(CMAKE_CXX_FLAGS_DEBUG "-w -g -fPIC -pthread -std=gnu++11")
set(CMAKE_CXX_FLAGS_RELEASE "-w  -DNDEBUG -pthread  -fPIC -std=gnu++11")
set(CIMG_LIB -L/usr/X11R6/lib -lm -lpthread -lX11)


# ----- Add subprojects -----
add_subdirectory (${stereo-qpbo_SOURCE_DIR}/src/exe/)



