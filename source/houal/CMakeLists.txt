CMAKE_MINIMUM_REQUIRED(VERSION 3.3)
MESSAGE(STATUS "--- Configuring target ${LIB_HOUAL} ---")



# Output dir
SET(LIB_HOUAL_OUTPUT_DIR ${CMAKE_BINARY_DIR})
MESSAGE(STATUS "Output dir: ${LIB_HOUAL_OUTPUT_DIR}")



# Definitions.
ADD_DEFINITIONS(-DHOU_AL_EXPORTS)
GET_PROPERTY(LIB_HOUAL_DEFINITIONS
  DIRECTORY ${CURRENT_SOURCE_DIR}
  PROPERTY COMPILE_DEFINITIONS
)
MESSAGE(STATUS "Definitions: ${LIB_HOUAL_DEFINITIONS}")



# Include directories.
INCLUDE_DIRECTORIES(
  ${LIB_OPENAL_INCLUDE_DIR}
  ${LIB_HOUCOR_INCLUDE_DIR}
  ${LIB_HOUMTH_INCLUDE_DIR}
  ${LIB_HOUAL_INCLUDE_DIR}
)



# Source files.
SET(LIB_HOUAL_SRC
  # src/hou/al/al_buffer_handle.cpp
  src/hou/al/al_context.cpp
  src/hou/al/al_context_exceptions.cpp
  src/hou/al/al_device.cpp
  src/hou/al/al_exceptions.cpp
  # src/hou/al/al_listener.cpp
  src/hou/al/al_object_handle.cpp
  # src/hou/al/al_invalid_context_handle.cpp
  src/hou/al/al_missing_context_error.cpp
  src/hou/al/al_module.cpp
  # src/hou/al/al_source_handle.cpp
  # src/hou/al/al_state.cpp
)



# Linked libraries.
SET(LIB_HOUAL_LIBS
  ${LIB_OPENAL}
)
IF(NOT HOU_CFG_BUILD_STATIC_LIBS)
  SET(LIB_HOUAL_LIBS
    ${LIB_HOUAL_LIBS}
    ${LIB_HOUMTH}
    ${LIB_HOUCOR}
  )
ENDIF()
MESSAGE(STATUS "Linked libs: ${LIB_HOUAL_LIBS}")



# Add targets.
IF(HOU_CFG_BUILD_STATIC_LIBS)
  ADD_LIBRARY(${LIB_HOUAL} STATIC ${LIB_HOUAL_SRC})
ELSE()
  ADD_LIBRARY(${LIB_HOUAL} SHARED ${LIB_HOUAL_SRC})
ENDIF()
SET_TARGET_PROPERTIES(${LIB_HOUAL} PROPERTIES
  COMPILE_FLAGS ${LIB_HOU_FLAGS}
  LINKER_LANGUAGE CXX
  ARCHIVE_OUTPUT_DIRECTORY ${LIB_HOUAL_OUTPUT_DIR}
  LIBRARY_OUTPUT_DIRECTORY ${LIB_HOUAL_OUTPUT_DIR}
  RUNTIME_OUTPUT_DIRECTORY ${LIB_HOUAL_OUTPUT_DIR}
)
TARGET_LINK_LIBRARIES(${LIB_HOUAL} ${LIB_HOUAL_LIBS})



MESSAGE(STATUS "")



IF(HOU_CFG_BUILD_TESTS)
  ADD_SUBDIRECTORY(${CMAKE_CURRENT_SOURCE_DIR}/test)
ENDIF()

