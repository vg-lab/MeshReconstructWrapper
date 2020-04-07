source_group(\\ FILES CMakeLists.txt)

set(WRAPPERTEST_SOURCES
  main.cpp
  )

set(WRAPPERTEST_HEADERS

  )

set(WRAPPERTEST_LINK_LIBRARIES
  meshreconstructwrapper
  )

include_directories(${CMAKE_CURRENT_BINARY_DIR})
include_directories(${PROJECT_BINARY_DIR}/include ${PROJECT_BINARY_DIR}/src)


common_application(wrapperTest)