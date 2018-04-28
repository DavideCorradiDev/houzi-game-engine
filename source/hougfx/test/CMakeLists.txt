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
  ${LIB_HOUTEST_SOURCE_DIR}/src/TestMain.cpp
  hou/gfx/TestData.cpp
  hou/gfx/TestFont.cpp
  hou/gfx/TestFormattedText.cpp
  hou/gfx/TestFramebuffer.cpp
  hou/gfx/TestGfxBase.cpp
  hou/gfx/TestGlyph.cpp
  hou/gfx/TestGlyphMetrics.cpp
  hou/gfx/TestMesh.cpp
  hou/gfx/TestMesh2ShaderProgram.cpp
  hou/gfx/TestGraphicContext.cpp
  hou/gfx/TestRenderCanvas.cpp
  hou/gfx/TestRenderWindow.cpp
  hou/gfx/TestShader.cpp
  hou/gfx/TestShaderProgram.cpp
  hou/gfx/TestTextBoxFormattingParams.cpp
  hou/gfx/TestTextVertex.cpp
  hou/gfx/TestTexture.cpp
  hou/gfx/TestTextureChannelMapping.cpp
  hou/gfx/TestVertex2.cpp
  hou/gfx/TestVertexArray.cpp
  hou/gfx/TestVertexAttribFormat.cpp
  hou/gfx/TestVertexBuffer.cpp
  hou/gfx/TestVertexFormat.cpp
)



# Linked libraries.
SET(EXE_HOUGFX_TEST_LIB
  ${LIB_HOUGFX}
  ${LIB_HOUGL}
  ${LIB_GLAD}
  ${LIB_HOUSYS}
  ${LIB_HOUMTH}
  ${LIB_HOUCOR}
  ${LIB_GOOGLE_TEST}
)
IF(WIN32)
  SET(EXE_HOU_GFX_TEST_LIB
    ${EXE_HOU_GFX_TEST_LIB}
    gdi32
    opengl32
  )
ENDIF()
MESSAGE(STATUS "Linked libs: ${EXE_HOUGFX_TEST_LIB}")



# Add target.
ADD_EXECUTABLE(${EXE_HOUGFX_TEST} ${EXE_HOUGFX_TEST_SRC})
SET_TARGET_PROPERTIES(${EXE_HOUGFX_TEST} PROPERTIES
  COMPILE_FLAGS ${EXE_HOU_TEST_FLAGS}
  LINKER_LANGUAGE CXX
  RUNTIME_OUTPUT_DIRECTORY ${EXE_HOUGFX_TEST_OUTPUT_DIR}
)
TARGET_LINK_LIBRARIES(${EXE_HOUGFX_TEST} ${EXE_HOUGFX_TEST_LIB})



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

