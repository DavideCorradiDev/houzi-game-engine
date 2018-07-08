CMAKE_MINIMUM_REQUIRED(VERSION 3.3)

SET(EXE_HOUGL_TEST "${LIB_HOUGL}-test")
MESSAGE(STATUS "--- Configuring target ${EXE_HOUGL_TEST} ---")

# Definitions
REMOVE_DEFINITIONS(-DHOU_GL_EXPORTS)
GET_PROPERTY(EXE_HOUGL_TEST_DEFINITIONS
  DIRECTORY ${CURRENT_SOURCE_DIR}
  PROPERTY COMPILE_DEFINITIONS
)
MESSAGE(STATUS "Definitions: ${EXE_HOUGL_TEST_DEFINITIONS}")

# Include directories.
INCLUDE_DIRECTORIES(
  ${LIB_GOOGLE_TEST_INCLUDE_DIR}
  ${LIB_GOOGLE_MOCK_INCLUDE_DIR}
  ${LIB_HOUTEST_INCLUDE_DIR}
  ${CMAKE_CURRENT_SOURCE_DIR}
)

# Source files.
SET(EXE_HOUGL_TEST_SRC
  hou/gl/hougl_test_main.cpp
  hou/gl/test_gl_base.cpp
  hou/gl/test_gl_multiple_contexts.cpp
  hou/gl/test_gl_single_context.cpp
  hou/gl/test_gl_buffer_handle.cpp
  hou/gl/test_gl_context.cpp
  hou/gl/test_gl_context_exceptions.cpp
  hou/gl/test_gl_context_settings.cpp
  hou/gl/test_gl_color_format.cpp
  hou/gl/test_gl_exceptions.cpp
  hou/gl/test_gl_framebuffer_handle.cpp
  hou/gl/test_gl_functions.cpp
  hou/gl/test_gl_invalid_context_error.cpp
  hou/gl/test_gl_object_handle.cpp
  hou/gl/test_gl_missing_context_error.cpp
  hou/gl/test_gl_program_handle.cpp
  hou/gl/test_gl_shader_handle.cpp
  hou/gl/test_gl_shader_sources.cpp
  hou/gl/test_gl_texture_handle.cpp
  hou/gl/test_gl_version.cpp
  hou/gl/test_gl_vsync_mode.cpp
  hou/gl/test_gl_vertex_array_handle.cpp
)

# Linked libraries.
SET(EXE_HOUGL_TEST_LIBS
  ${LIB_HOUGL}
  ${LIB_HOUMTH}
  ${LIB_HOUSYS}
  ${LIB_HOUCOR}
  ${LIB_GLAD}
  ${LIB_SDL2}
  ${LIB_GOOGLE_TEST}
  ${LIB_GOOGLE_MOCK}
)
MESSAGE(STATUS "Linked libs: ${EXE_HOUGL_TEST_LIBS}")

# Tests for different context profiles.
SET(EXE_HOUGL_TEST_CORE "${EXE_HOUGL_TEST}-core")
SET(EXE_HOUGL_TEST_ES "${EXE_HOUGL_TEST}-es")

# Add targets.
ADD_EXECUTABLE(${EXE_HOUGL_TEST_CORE} ${EXE_HOUGL_TEST_SRC})
SET_TARGET_PROPERTIES(${EXE_HOUGL_TEST_CORE} PROPERTIES
  COMPILE_FLAGS "${EXE_HOU_FLAGS} -DHOU_GL_CONTEXT_PROFILE=1"
  LINKER_LANGUAGE CXX
)
TARGET_LINK_LIBRARIES(${EXE_HOUGL_TEST_CORE} ${EXE_HOUGL_TEST_LIBS})

ADD_EXECUTABLE(${EXE_HOUGL_TEST_ES} ${EXE_HOUGL_TEST_SRC})
SET_TARGET_PROPERTIES(${EXE_HOUGL_TEST_ES} PROPERTIES
  COMPILE_FLAGS "${EXE_HOU_FLAGS} -DHOU_GL_CONTEXT_PROFILE=2"
  LINKER_LANGUAGE CXX
)
TARGET_LINK_LIBRARIES(${EXE_HOUGL_TEST_ES} ${EXE_HOUGL_TEST_LIBS})

# Create test files directory.
ADD_CUSTOM_COMMAND(
  TARGET ${EXE_HOUGL_TEST_CORE} POST_BUILD
  COMMAND ${CMAKE_COMMAND} -E make_directory
  ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/source/hougl/test/output
  COMMENT "Creating test output directory"
)

# Copy test files.
ADD_CUSTOM_COMMAND(
  TARGET ${EXE_HOUGL_TEST_CORE} POST_BUILD
  COMMAND ${CMAKE_COMMAND} -E copy_directory
  ${CMAKE_CURRENT_SOURCE_DIR}/data
  ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/source/hougl/test/data
  COMMENT "Copying test data directory to build folder"
)

MESSAGE(STATUS "")
