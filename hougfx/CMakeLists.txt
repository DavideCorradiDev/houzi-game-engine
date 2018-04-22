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
  src/hou/gfx/Font.cpp
  src/hou/gfx/GfxError.cpp
  src/hou/gfx/Glyph.cpp
  src/hou/gfx/GlyphMetrics.cpp
  src/hou/gfx/GlType.cpp
  src/hou/gfx/FormattedText.cpp
  src/hou/gfx/FrameBuffer.cpp
  src/hou/gfx/FrameBufferBlitFilter.cpp
  src/hou/gfx/Mesh.cpp
  src/hou/gfx/Mesh2ShaderProgram.cpp
  src/hou/gfx/MeshDrawMode.cpp
  src/hou/gfx/MeshFillMode.cpp
  src/hou/gfx/GraphicContext.cpp
  src/hou/gfx/RenderFont.cpp
  src/hou/gfx/RenderCanvas.cpp
  src/hou/gfx/RenderSurface.cpp
  src/hou/gfx/RenderWindow.cpp
  src/hou/gfx/Shader.cpp
  src/hou/gfx/ShaderProgram.cpp
  src/hou/gfx/ShaderType.cpp
  src/hou/gfx/TextShaderProgram.cpp
  src/hou/gfx/TextVertex.cpp
  src/hou/gfx/Texture.cpp
  src/hou/gfx/TextureChannel.cpp
  src/hou/gfx/TextureChannelMapping.cpp
  src/hou/gfx/TextureFilter.cpp
  src/hou/gfx/TextureFormat.cpp
  src/hou/gfx/TextureType.cpp
  src/hou/gfx/TextureWrapMode.cpp
  src/hou/gfx/VertexArray.cpp
  src/hou/gfx/VertexAttribFormat.cpp
  src/hou/gfx/VertexBuffer.cpp
  src/hou/gfx/VertexBufferTarget.cpp
  src/hou/gfx/VertexFormat.cpp
  src/hou/gfx/Vertex2.cpp
)



# Linked libraries.
IF(HOU_CFG_SHARED_LIBS)
  SET(LIB_HOUGFX_LIB
    ${LIB_HOUGL}
    ${LIB_GLAD}
    ${LIB_HOUSYS}
    ${LIB_HOUMTH}
    ${LIB_HOUCOR}
  )
  IF(WIN32)
    SET(LIB_HOUGL_LIB
      ${LIB_HOUGL_LIB}
      gdi32
      opengl32
    )
  ENDIF()
ELSE()
  SET(LIB_HOUGFX_LIB)
ENDIF()
# Freetype is always built as a static lib and linked.
# In this way it will be incorporated into hougfx.
# Freetype is completely encapsulated so there is no need to expose it.
SET(LIB_HOUGFX_LIB
  ${LIB_HOUGFX_LIB}
  ${LIB_FREETYPE}
)
MESSAGE(STATUS "Linked libs: ${LIB_HOUGFX_LIB}")



# Add targets.
IF(HOU_CFG_SHARED_LIBS)
  ADD_LIBRARY(${LIB_HOUGFX} SHARED ${LIB_HOUGFX_SRC})
ELSE()
  ADD_LIBRARY(${LIB_HOUGFX} STATIC ${LIB_HOUGFX_SRC})
ENDIF()
SET_TARGET_PROPERTIES(${LIB_HOUGFX} PROPERTIES
  COMPILE_FLAGS ${LIB_HOU_FLAGS}
  LINKER_LANGUAGE CXX
  ARCHIVE_OUTPUT_DIRECTORY ${LIB_HOUGFX_OUTPUT_DIR}
  LIBRARY_OUTPUT_DIRECTORY ${LIB_HOUGFX_OUTPUT_DIR}
  RUNTIME_OUTPUT_DIRECTORY ${LIB_HOUGFX_OUTPUT_DIR}
)
TARGET_LINK_LIBRARIES(${LIB_HOUGFX} ${LIB_HOUGFX_LIB})



MESSAGE(STATUS "")



IF(HOU_CFG_BUILD_GFX_TESTS)
  ADD_SUBDIRECTORY(${CMAKE_CURRENT_SOURCE_DIR}/test)
ENDIF()

