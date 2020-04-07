source_group(\\ FILES CMakeLists.txt)

set(MESHRECONSTRUCTWRAPPER_SOURCES
  MeshReconstruct.cpp
  )

set(MESHRECONSTRUCTWRAPPER_HEADERS
  MeshReconstruct.h
  )

set(MESHRECONSTRUCTWRAPPER_LINK_LIBRARIES
  ${Boost_LIBRARIES}
  Qt5::Core
  )

include_directories(${CMAKE_CURRENT_BINARY_DIR})
include_directories(${PROJECT_BINARY_DIR}/include ${PROJECT_BINARY_DIR}/src)


common_library(meshreconstructwrapper)


