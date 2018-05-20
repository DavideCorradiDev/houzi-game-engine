CMAKE_MINIMUM_REQUIRED(VERSION 3.3)



SET(EXE_HOUGL_TEST "${LIB_HOUGL}-test")
MESSAGE(STATUS "--- Configuring target ${EXE_HOUGL_TEST} ---")




# Output dir
SET(EXE_HOUGL_TEST_OUTPUT_DIR ${CMAKE_BINARY_DIR})
MESSAGE(STATUS "Output dir: ${EXE_HOUGL_TEST_OUTPUT_DIR}")



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
  ${LIB_HOUTEST_INCLUDE_DIR}
  ${CMAKE_CURRENT_SOURCE_DIR}
)



# Source files.
SET(EXE_HOUGL_TEST_SRC
  ${LIB_HOUTEST_SOURCE_DIR}/src/test_main.cpp
  hou/gl/test_gl_base.cpp
  hou/gl/test_gl_multiple_contexts.cpp
  hou/gl/test_gl_single_context.cpp
  hou/gl/test_gl_buffer_handle.cpp
  hou/gl/test_gl_context.cpp
  hou/gl/test_gl_context_settings.cpp
  hou/gl/test_gl_exceptions.cpp
  hou/gl/test_gl_framebuffer_handle.cpp
  hou/gl/test_gl_functions.cpp
  hou/gl/test_gl_object_handle.cpp
  hou/gl/test_gl_program_handle.cpp
  hou/gl/test_gl_shader_handle.cpp
  hou/gl/test_gl_shader_sources.cpp
  hou/gl/test_gl_texture_handle.cpp
  hou/gl/test_gl_version.cpp
  hou/gl/test_gl_vertex_array_handle.cpp
)



# Linked libraries.
SET(EXE_HOUGL_TEST_LIB
  ${LIB_HOUGL}
  ${LIB_GLAD}
  ${LIB_HOUMTH}
  ${LIB_HOUSYS}
  ${LIB_HOUCOR}
  ${LIB_GOOGLE_TEST}
)
IF(WIN32)
  SET(LIB_HOUGL_LIB
    ${LIB_HOUGL_LIB}
    gdi32
    opengl32
  )
ENDIF()
MESSAGE(STATUS "Linked libs: ${EXE_HOUGL_TEST_LIB}")



# Add target.
ADD_EXECUTABLE(${EXE_HOUGL_TEST} ${EXE_HOUGL_TEST_SRC})
SET_TARGET_PROPERTIES(${EXE_HOUGL_TEST} PROPERTIES
  COMPILE_FLAGS ${EXE_HOU_TEST_FLAGS}
  LINKER_LANGUAGE CXX
  RUNTIME_OUTPUT_DIRECTORY ${EXE_HOUGL_TEST_OUTPUT_DIR}
)
TARGET_LINK_LIBRARIES(${EXE_HOUGL_TEST} ${EXE_HOUGL_TEST_LIB})



# Create test files directory.
ADD_CUSTOM_COMMAND(
  TARGET ${EXE_HOUGL_TEST} POST_BUILD
  COMMAND ${CMAKE_COMMAND} -E make_directory
  ${EXE_HOUGL_TEST_OUTPUT_DIR}/source/hougl/test/output
  COMMENT "Creating test output directory"
)



# Copy test files.
ADD_CUSTOM_COMMAND(
  TARGET ${EXE_HOUGL_TEST} POST_BUILD
  COMMAND ${CMAKE_COMMAND} -E copy_directory
  ${CMAKE_CURRENT_SOURCE_DIR}/data
  ${EXE_HOUGL_TEST_OUTPUT_DIR}/source/hougl/test/data
  COMMENT "Copying test data directory to build folder"
)



MESSAGE(STATUS "")
