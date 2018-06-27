CMAKE_MINIMUM_REQUIRED(VERSION 3.3)

SET(EXE_HOUAL_TEST "${LIB_HOUAL}-test")
MESSAGE(STATUS "--- Configuring target ${EXE_HOUAL_TEST} ---")

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
  hou/al/houal_test_main.cpp
  hou/al/test_al_base.cpp
  hou/al/test_al_buffer_handle.cpp
  hou/al/test_al_context.cpp
  hou/al/test_al_context_exceptions.cpp
  hou/al/test_al_device.cpp
  hou/al/test_al_exceptions.cpp
  hou/al/test_al_listener.cpp
  hou/al/test_al_missing_context_error.cpp
  hou/al/test_al_source_handle.cpp
  hou/al/test_al_state.cpp
)

# Linked libraries.
SET(EXE_HOUAL_TEST_LIBS
  ${LIB_HOUAL}
  ${LIB_HOUMTH}
  ${LIB_HOUCOR}
  ${LIB_GOOGLE_TEST}
)
MESSAGE(STATUS "Linked libs: ${EXE_HOUAL_TEST_LIBS}")

# Add target.
ADD_EXECUTABLE(${EXE_HOUAL_TEST} ${EXE_HOUAL_TEST_SRC})
SET_TARGET_PROPERTIES(${EXE_HOUAL_TEST} PROPERTIES
  COMPILE_FLAGS ${EXE_HOU_TEST_FLAGS}
  LINKER_LANGUAGE CXX
)
TARGET_LINK_LIBRARIES(${EXE_HOUAL_TEST} ${EXE_HOUAL_TEST_LIBS})

# Create test files directory.
ADD_CUSTOM_COMMAND(
  TARGET ${EXE_HOUAL_TEST} POST_BUILD
  COMMAND ${CMAKE_COMMAND} -E make_directory
  ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/source/houal/test/output
  COMMENT "Creating test output directory"
)

# Copy test files.
ADD_CUSTOM_COMMAND(
  TARGET ${EXE_HOUAL_TEST} POST_BUILD
  COMMAND ${CMAKE_COMMAND} -E copy_directory
  ${CMAKE_CURRENT_SOURCE_DIR}/data
  ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/source/houal/test/data
  COMMENT "Copying test data directory to build folder"
)

MESSAGE(STATUS "")
