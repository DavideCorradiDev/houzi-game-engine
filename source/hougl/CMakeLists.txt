CMAKE_MINIMUM_REQUIRED(VERSION 3.3)
MESSAGE(STATUS "--- Configuring target ${LIB_HOUGL} ---")



# Output dir
SET(LIB_HOUGL_OUTPUT_DIR ${CMAKE_BINARY_DIR})
MESSAGE(STATUS "Output dir: ${LIB_HOUGL_OUTPUT_DIR}")



# Definitions.
ADD_DEFINITIONS(-DHOU_GL_EXPORTS)
GET_PROPERTY(LIB_HOUGL_DEFINITIONS
  DIRECTORY ${CURRENT_SOURCE_DIR}
  PROPERTY COMPILE_DEFINITIONS
)
MESSAGE(STATUS "Definitions: ${LIB_HOUGL_DEFINITIONS}")



# Include directories.
INCLUDE_DIRECTORIES(
  ${LIB_GLAD_INCLUDE_DIR}
  ${LIB_HOUCOR_INCLUDE_DIR}
  ${LIB_HOUMTH_INCLUDE_DIR}
  ${LIB_HOUSYS_INCLUDE_DIR}
  ${LIB_HOUGL_INCLUDE_DIR}
)



# Source files.
SET(LIB_HOUGL_SRC
  src/hou/gl/GlBufferHandle.cpp
  src/hou/gl/GlContext.cpp
  src/hou/gl/GlContextSettings.cpp
  src/hou/gl/GlCheck.cpp
  src/hou/gl/GlError.cpp
  src/hou/gl/GlFramebufferHandle.cpp
  src/hou/gl/GlFunctions.cpp
  src/hou/gl/GlObjectHandle.cpp
  src/hou/gl/GlProgramHandle.cpp
  src/hou/gl/GlShaderHandle.cpp
  src/hou/gl/GlTextureHandle.cpp
  src/hou/gl/GlVersion.cpp
  src/hou/gl/GlVertexArrayHandle.cpp
)

IF(WIN32)
  SET(LIB_HOUGL_SRC
    ${LIB_HOUGL_SRC}
    src/hou/gl/wgl/GlContextImplWgl.cpp
  )
ENDIF()



# Linked libraries.
IF(HOU_CFG_STATIC_LIBS)
  SET(LIB_HOUGL_LIB)
ELSE()
  SET(LIB_HOUGL_LIB
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
ENDIF()
MESSAGE(STATUS "Linked libs: ${LIB_HOUGL_LIB}")



# Add targets.
IF(HOU_CFG_STATIC_LIBS)
  ADD_LIBRARY(${LIB_HOUGL} STATIC ${LIB_HOUGL_SRC})
ELSE()
  ADD_LIBRARY(${LIB_HOUGL} SHARED ${LIB_HOUGL_SRC})
ENDIF()
SET_TARGET_PROPERTIES(${LIB_HOUGL} PROPERTIES
  COMPILE_FLAGS ${LIB_HOU_FLAGS}
  LINKER_LANGUAGE CXX
  ARCHIVE_OUTPUT_DIRECTORY ${LIB_HOUGL_OUTPUT_DIR}
  LIBRARY_OUTPUT_DIRECTORY ${LIB_HOUGL_OUTPUT_DIR}
  RUNTIME_OUTPUT_DIRECTORY ${LIB_HOUGL_OUTPUT_DIR}
)
TARGET_LINK_LIBRARIES(${LIB_HOUGL} ${LIB_HOUGL_LIB})



MESSAGE(STATUS "")



IF(HOU_CFG_BUILD_GL_TESTS)
  ADD_SUBDIRECTORY(${CMAKE_CURRENT_SOURCE_DIR}/test)
ENDIF()

