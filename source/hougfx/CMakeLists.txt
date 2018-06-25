CMAKE_MINIMUM_REQUIRED(VERSION 3.3)
MESSAGE(STATUS "--- Configuring target ${LIB_HOUGFX} ---")



# Output dir
SET(LIB_HOUGFX_OUTPUT_DIR ${CMAKE_BINARY_DIR})
MESSAGE(STATUS "Output dir: ${LIB_HOUGFX_OUTPUT_DIR}")



# Definitions.
ADD_DEFINITIONS(-DHOU_GFX_EXPORTS)
GET_PROPERTY(LIB_HOUGFX_DEFINITIONS
  DIRECTORY ${CURRENT_SOURCE_DIR}
  PROPERTY COMPILE_DEFINITIONS
)
MESSAGE(STATUS "Definitions: ${LIB_HOUGFX_DEFINITIONS}")



# Include directories.
INCLUDE_DIRECTORIES(
  ${LIB_GLAD_INCLUDE_DIR}
  ${LIB_FREETYPE_INCLUDE_DIR}
  ${LIB_HOUCOR_INCLUDE_DIR}
  ${LIB_HOUMTH_INCLUDE_DIR}
  ${LIB_HOUSYS_INCLUDE_DIR}
  ${LIB_HOUGL_INCLUDE_DIR}
  ${LIB_HOUGFX_INCLUDE_DIR}
)



# Source files.
SET(LIB_HOUGFX_SRC
  src/hou/gfx/font.cpp
  src/hou/gfx/gfx_exceptions.cpp
  src/hou/gfx/glyph.cpp
  src/hou/gfx/glyph_metrics.cpp
  src/hou/gfx/gl_type.cpp
  src/hou/gfx/formatted_text.cpp
  src/hou/gfx/framebuffer.cpp
  src/hou/gfx/framebuffer_blit_filter.cpp
  src/hou/gfx/gfx_module.cpp
  src/hou/gfx/graphic_context.cpp
  src/hou/gfx/mesh.cpp
  src/hou/gfx/mesh2.cpp
  src/hou/gfx/mesh2_shader_program.cpp
  src/hou/gfx/mesh_draw_mode.cpp
  src/hou/gfx/mesh_fill_mode.cpp
  src/hou/gfx/render_surface.cpp
  src/hou/gfx/shader.cpp
  src/hou/gfx/shader_program.cpp
  src/hou/gfx/shader_type.cpp
  src/hou/gfx/text_box_formatting_params.cpp
  src/hou/gfx/text_flow.cpp
  src/hou/gfx/text_shader_program.cpp
  src/hou/gfx/text_vertex.cpp
  src/hou/gfx/texture.cpp
  src/hou/gfx/texture_channel.cpp
  src/hou/gfx/texture_channel_mapping.cpp
  src/hou/gfx/texture_filter.cpp
  src/hou/gfx/texture_format.cpp
  src/hou/gfx/texture_type.cpp
  src/hou/gfx/texture_wrap_mode.cpp
  src/hou/gfx/vertex_array.cpp
  src/hou/gfx/vertex_attrib_format.cpp
  src/hou/gfx/vertex_buffer.cpp
  src/hou/gfx/vertex_buffer_target.cpp
  src/hou/gfx/vertex_format.cpp
  src/hou/gfx/vertex2.cpp
)



# Linked libraries.
SET(LIB_HOUGFX_LIBS
  ${LIB_FREETYPE}
)
IF(NOT HOU_CFG_BUILD_STATIC_LIBS)
  SET(LIB_HOUGFX_LIBS
    ${LIB_HOUGFX_LIBS}
    ${LIB_HOUGL}
    ${LIB_HOUSYS}
    ${LIB_HOUMTH}
    ${LIB_HOUCOR}
  )
ENDIF()
MESSAGE(STATUS "Linked libs: ${LIB_HOUGFX_LIBS}")



# Add targets.
IF(HOU_CFG_BUILD_STATIC_LIBS)
  ADD_LIBRARY(${LIB_HOUGFX} STATIC ${LIB_HOUGFX_SRC})
ELSE()
  ADD_LIBRARY(${LIB_HOUGFX} SHARED ${LIB_HOUGFX_SRC})
ENDIF()
SET_TARGET_PROPERTIES(${LIB_HOUGFX} PROPERTIES
  COMPILE_FLAGS ${LIB_HOU_FLAGS}
  LINKER_LANGUAGE CXX
  ARCHIVE_OUTPUT_DIRECTORY ${LIB_HOUGFX_OUTPUT_DIR}
  LIBRARY_OUTPUT_DIRECTORY ${LIB_HOUGFX_OUTPUT_DIR}
  RUNTIME_OUTPUT_DIRECTORY ${LIB_HOUGFX_OUTPUT_DIR}
)
TARGET_LINK_LIBRARIES(${LIB_HOUGFX} ${LIB_HOUGFX_LIBS})



MESSAGE(STATUS "")



IF(HOU_CFG_BUILD_TESTS)
  ADD_SUBDIRECTORY(${CMAKE_CURRENT_SOURCE_DIR}/test)
ENDIF()
