CMAKE_MINIMUM_REQUIRED(VERSION 3.3)



SET(EXE_HOUGFX_TEST "${LIB_HOUGFX}-test")
MESSAGE(STATUS "--- Configuring target ${EXE_HOUGFX_TEST} ---")




# Output dir
SET(EXE_HOUGFX_TEST_OUTPUT_DIR ${CMAKE_BINARY_DIR})
MESSAGE(STATUS "Output dir: ${EXE_HOUGFX_TEST_OUTPUT_DIR}")



# Definitions
REMOVE_DEFINITIONS(-DHOU_GFX_EXPORTS)
GET_PROPERTY(EXE_HOUGFX_TEST_DEFINITIONS
  DIRECTORY ${CURRENT_SOURCE_DIR}
  PROPERTY COMPILE_DEFINITIONS
)
MESSAGE(STATUS "Definitions: ${EXE_HOUGFX_TEST_DEFINITIONS}")



# Include directories.
INCLUDE_DIRECTORIES(
  ${LIB_GOOGLE_TEST_INCLUDE_DIR}
  ${LIB_HOUTEST_INCLUDE_DIR}
  ${CMAKE_CURRENT_SOURCE_DIR}
)



# Source files.
SET(EXE_HOUGFX_TEST_SRC
  hou/gfx/hougfx_test_main.cpp
  hou/gfx/test_data.cpp
  hou/gfx/test_font.cpp
  hou/gfx/test_formatted_text.cpp
  hou/gfx/test_framebuffer.cpp
  hou/gfx/test_gfx_base.cpp
  hou/gfx/test_gfx_exceptions.cpp
  hou/gfx/test_glyph.cpp
  hou/gfx/test_glyph_metrics.cpp
  hou/gfx/test_mesh.cpp
  hou/gfx/test_mesh2.cpp
  hou/gfx/test_mesh2_shader_program.cpp
  hou/gfx/test_graphic_context.cpp
  hou/gfx/test_render_canvas.cpp
  hou/gfx/test_render_window.cpp
  hou/gfx/test_shader.cpp
  hou/gfx/test_shader_program.cpp
  hou/gfx/test_text_box_formatting_params.cpp
  hou/gfx/test_text_vertex.cpp
  hou/gfx/test_texture.cpp
  hou/gfx/test_texture_channel_mapping.cpp
  hou/gfx/test_vertex_array.cpp
  hou/gfx/test_vertex_attrib_format.cpp
  hou/gfx/test_vertex_buffer.cpp
  hou/gfx/test_vertex_format.cpp
  hou/gfx/test_vertex2.cpp
)



# Linked libraries.
SET(EXE_HOUGFX_TEST_LIBS
  ${LIB_HOUGFX}
  ${LIB_HOUGL}
  ${LIB_HOUSYS}
  ${LIB_HOUMTH}
  ${LIB_HOUCOR}
  ${LIB_GOOGLE_TEST}
)
MESSAGE(STATUS "Linked libs: ${EXE_HOUGFX_TEST_LIBS}")



# Add target.
ADD_EXECUTABLE(${EXE_HOUGFX_TEST} ${EXE_HOUGFX_TEST_SRC})
SET_TARGET_PROPERTIES(${EXE_HOUGFX_TEST} PROPERTIES
  COMPILE_FLAGS ${EXE_HOU_TEST_FLAGS}
  LINKER_LANGUAGE CXX
  RUNTIME_OUTPUT_DIRECTORY ${EXE_HOUGFX_TEST_OUTPUT_DIR}
)
TARGET_LINK_LIBRARIES(${EXE_HOUGFX_TEST} ${EXE_HOUGFX_TEST_LIBS})



# Create test files directory.
ADD_CUSTOM_COMMAND(
  TARGET ${EXE_HOUGFX_TEST} POST_BUILD
  COMMAND ${CMAKE_COMMAND} -E make_directory
  ${EXE_HOUGFX_TEST_OUTPUT_DIR}/source/hougfx/test/output
  COMMENT "Creating test output directory"
)



# Copy test files.
ADD_CUSTOM_COMMAND(
  TARGET ${EXE_HOUGFX_TEST} POST_BUILD
  COMMAND ${CMAKE_COMMAND} -E copy_directory
  ${CMAKE_CURRENT_SOURCE_DIR}/data
  ${EXE_HOUGFX_TEST_OUTPUT_DIR}/source/hougfx/test/data
  COMMENT "Copying test data directory to build folder"
)



MESSAGE(STATUS "")

