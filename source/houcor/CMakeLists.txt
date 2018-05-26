CMAKE_MINIMUM_REQUIRED(VERSION 3.3)
MESSAGE(STATUS "--- Configuring target ${LIB_HOUCOR} ---")



# Generate a header with the correct version number.
CONFIGURE_FILE(
  "${CMAKE_CURRENT_SOURCE_DIR}/include/hou/config.hpp.in"
  "${CMAKE_CURRENT_SOURCE_DIR}/include/hou/config.hpp"
)


# Output dir
SET(LIB_HOUCOR_OUTPUT_DIR ${CMAKE_BINARY_DIR})
MESSAGE(STATUS "Output dir: ${LIB_HOUCOR_OUTPUT_DIR}")



# Definitions.
ADD_DEFINITIONS(-DHOU_COR_EXPORTS)
GET_PROPERTY(LIB_HOUCOR_DEFINITIONS
  DIRECTORY ${CURRENT_SOURCE_DIR}
  PROPERTY COMPILE_DEFINITIONS
)
MESSAGE(STATUS "Definitions: ${LIB_HOUCOR_DEFINITIONS}")



# Include directories.
INCLUDE_DIRECTORIES(
  ${LIB_HOUCOR_INCLUDE_DIR}
)



# Source files.
SET(LIB_HOUCOR_SRC
  src/hou/cor/assertions.cpp
  src/hou/cor/character_encodings.cpp
  src/hou/cor/clock.cpp
  src/hou/cor/cor_exceptions.cpp
  src/hou/cor/core_functions.cpp
  src/hou/cor/exception.cpp
  src/hou/cor/std_string.cpp
  src/hou/cor/stopwatch.cpp
  src/hou/cor/uid_generator.cpp
)



# Linked libraries.
SET(LIB_HOUCOR_LIBS)
MESSAGE(STATUS "Linked libs: ${LIB_HOUCOR_LIBS}")



# Add targets.
IF(HOU_CFG_BUILD_STATIC_LIBS)
  ADD_LIBRARY(${LIB_HOUCOR} STATIC ${LIB_HOUCOR_SRC})
ELSE()
  ADD_LIBRARY(${LIB_HOUCOR} SHARED ${LIB_HOUCOR_SRC})
ENDIF()
SET_TARGET_PROPERTIES(${LIB_HOUCOR} PROPERTIES
  COMPILE_FLAGS ${LIB_HOU_FLAGS}
  LINKER_LANGUAGE CXX
  ARCHIVE_OUTPUT_DIRECTORY ${LIB_HOUCOR_OUTPUT_DIR}
  LIBRARY_OUTPUT_DIRECTORY ${LIB_HOUCOR_OUTPUT_DIR}
  RUNTIME_OUTPUT_DIRECTORY ${LIB_HOUCOR_OUTPUT_DIR}
)
TARGET_LINK_LIBRARIES(${LIB_HOUCOR} ${LIB_HOUCOR_LIBS})



MESSAGE(STATUS "")



IF(HOU_CFG_BUILD_TESTS)
  ADD_SUBDIRECTORY(${CMAKE_CURRENT_SOURCE_DIR}/test)
ENDIF()

