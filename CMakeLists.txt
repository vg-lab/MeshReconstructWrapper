
cmake_minimum_required( VERSION 3.1 )
project(MeshReconstructWrapper VERSION 0.2.0 )
set( MeshReconstructWrapper_VERSION_ABI 1 )
# Disable in source building
if( "${PROJECT_SOURCE_DIR}" STREQUAL "${PROJECT_BINARY_DIR}" )
  message( FATAL "no in source building allowed." )
endif( )

if( NOT EXISTS ${CMAKE_SOURCE_DIR}/CMake/common/Common.cmake )
  message( FATAL_ERROR "CMake/common missing, run: git submodule update --init")
endif( )

list( APPEND CMAKE_MODULE_PATH
  ${PROJECT_SOURCE_DIR}/CMake
  ${CMAKE_SOURCE_DIR}/CMake/common
  )

# Default build type is Debug
if( NOT CMAKE_BUILD_TYPE )
  set( CMAKE_BUILD_TYPE Debug )
endif( NOT CMAKE_BUILD_TYPE )

if ( CMAKE_BUILD_TYPE MATCHES "Debug" )
  add_definitions( -DDEBUG )
endif( )

include( GitExternal )

set( MESHRECONSTRUCTWRAPPER_DESCRIPTION "MeshReconstructWrapper" )
set( COMMON_PROJECT_DOMAIN gmrv.es )

if( APPLE )
  set( CMAKE_CXX_FLAGS "-framework CoreFoundation" )
endif()

include( Common )

common_find_package(Boost COMPONENTS filesystem REQUIRED)
common_find_package(Qt5Core SYSTEM REQUIRED)

common_find_package_post( )

list( APPEND NEURONIZE_DEPENDENT_LIBRARIES
  Qt5::Core
  ${Boost_LIBRARIES}
  )


add_subdirectory( MeshReconstructWrapper )

set( DOXYGEN_MAINPAGE_MD README.md )
set( DOXYGEN_EXTRA_INPUT ${PROJECT_SOURCE_DIR}/README.md )
include( DoxygenRule )

include( CPackConfig )

#Copy content (this must be improved)

file(GLOB MY_CONTENT "Content/*")
file(COPY ${MY_CONTENT} DESTINATION "${CMAKE_BINARY_DIR}/bin")

file(GLOB MeshReconstruct "MeshReconstruct/src/*")
file(COPY ${MeshReconstruct} DESTINATION "${CMAKE_BINARY_DIR}/bin/src"  FILE_PERMISSIONS OWNER_READ OWNER_WRITE OWNER_EXECUTE)



