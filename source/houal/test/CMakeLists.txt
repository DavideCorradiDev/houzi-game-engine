CMAKE_MINIMUM_REQUIRED(VERSION 3.3)



SET(EXE_HOUAL_TEST "${LIB_HOUAL}-test")
MESSAGE(STATUS "--- Configuring target ${EXE_HOUAL_TEST} ---")




# Output dir
SET(EXE_HOUAL_TEST_OUTPUT_DIR ${CMAKE_BINARY_DIR})
MESSAGE(STATUS "Output dir: ${EXE_HOUAL_TEST_OUTPUT_DIR}")



# Definitions
REMOVE_DEFINITIONS(-DHOU_AL_EXPORTS)
GET_PROPERTY(EXE_HOUAL_TEST_DEFINITIONS
  DIRECTORY ${CURRENT_SOURCE_DIR}
  PROPERTY COMPILE_DEFINITIONS
)
MESSAGE(STATUS "Definitions: ${EXE_HOUAL_TEST_DEFINITIONS}")



# Include directories.
INCLUDE_DIRECTORIES(
  ${LIB_GOOGLE_TEST_INCLUDE_DIR}
  ${LIB_HOUTEST_INCLUDE_DIR}
  ${CMAKE_CURRENT_SOURCE_DIR}
)



# Source files.
SET(EXE_HOUAL_TEST_SRC
  ${LIB_HOUTEST_SOURCE_DIR}/src/test_main.cpp
  hou/al/test_al_base.cpp
  hou/al/test_al_buffer_handle.cpp
  hou/al/test_al_check.cpp
  hou/al/test_al_context.cpp
  hou/al/test_al_device.cpp
  hou/al/test_al_listener.cpp
  hou/al/test_al_source_handle.cpp
  hou/al/test_al_state.cpp
)



# Linked libraries.
SET(EXE_HOUAL_TEST_LIB
  ${LIB_HOUAL}
  ${LIB_OPENAL}
  ${LIB_HOUMTH}
  ${LIB_HOUCOR}
  ${LIB_GOOGLE_TEST}
)
MESSAGE(STATUS "Linked libs: ${EXE_HOUAL_TEST_LIB}")



# Add target.
ADD_EXECUTABLE(${EXE_HOUAL_TEST} ${EXE_HOUAL_TEST_SRC})
SET_TARGET_PROPERTIES(${EXE_HOUAL_TEST} PROPERTIES
  COMPILE_FLAGS ${EXE_HOU_TEST_FLAGS}
  LINKER_LANGUAGE CXX
  RUNTIME_OUTPUT_DIRECTORY ${EXE_HOUAL_TEST_OUTPUT_DIR}
)
TARGET_LINK_LIBRARIES(${EXE_HOUAL_TEST} ${EXE_HOUAL_TEST_LIB})



# Create test files directory.
ADD_CUSTOM_COMMAND(
  TARGET ${EXE_HOUAL_TEST} POST_BUILD
  COMMAND ${CMAKE_COMMAND} -E make_directory
  ${EXE_HOUAL_TEST_OUTPUT_DIR}/source/houal/test/output
  COMMENT "Creating test output directory"
)



# Copy test files.
ADD_CUSTOM_COMMAND(
  TARGET ${EXE_HOUAL_TEST} POST_BUILD
  COMMAND ${CMAKE_COMMAND} -E copy_directory
  ${CMAKE_CURRENT_SOURCE_DIR}/data
  ${EXE_HOUAL_TEST_OUTPUT_DIR}/source/houal/test/data
  COMMENT "Copying test data directory to build folder"
)



MESSAGE(STATUS "")

