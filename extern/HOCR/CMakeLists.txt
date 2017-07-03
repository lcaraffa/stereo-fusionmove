cmake_minimum_required (VERSION 2.6)

project (hocr)
# src CMakeLists.txt
set (HOCR_SRC_DIR src)

find_package(QPBO)


#set(CMAKE_BUILD_TYPE Debug)
SET(INCLUDE_DIR ${hocr_SOURCE_DIR}/include)

IF(COMMAND cmake_policy)
  cmake_policy(SET CMP0003 NEW)
ENDIF(COMMAND cmake_policy)

## ------ Reconstruction 3D ---------
IF(QPBO_FOUND)
  #includes
  INCLUDE_DIRECTORIES(
    ${INCLUDE_DIR}
    ${QPBO_INCLUDE_DIR}
    )
  #Exec
  add_executable(test-hocr ${HOCR_SRC_DIR}/HOCRdemo.cpp)
  add_executable(test-hocr2 ${HOCR_SRC_DIR}/HOCRdemo2.cpp)
  add_executable(QPBO-stereo ${HOCR_SRC_DIR}/HOCRstereo.cpp)
  #Link library
  TARGET_LINK_LIBRARIES(test-hocr ${QPBO_LIBRARIES})
  TARGET_LINK_LIBRARIES(test-hocr2 ${QPBO_LIBRARIES})
  TARGET_LINK_LIBRARIES(QPBO-stereo ${QPBO_LIBRARIES})
  #Install
  install(TARGETS test-hocr DESTINATION  ${hocr_SOURCE_DIR}/bin/)
  install(TARGETS QPBO-stereo DESTINATION  ${hocr_SOURCE_DIR}/bin/)

  file(GLOB CMAKE_CONF
    "${hocr_SOURCE_DIR}/FindHOCR.cmake"
    )
ENDIF(QPBO_FOUND)

file(COPY ${CMAKE_CONF} DESTINATION /usr/share/cmake-2.8/Modules)



#TARGET_LINK_LIBRARIES(opt ${LIBRARIES_SOFTWARE} )
#INSTALL(CODE "MESSAGE(\"Installing headers...\")")
#INSTALL(FILES ${HOCR_SRC_DIR}/HOCR.h  DESTINATION ${INCLUDE_DIR})



