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
  src/hou/gl/gl_buffer_handle.cpp
  src/hou/gl/gl_context.cpp
  src/hou/gl/gl_context_settings.cpp
  src/hou/gl/gl_check.cpp
  src/hou/gl/gl_error.cpp
  src/hou/gl/gl_framebuffer_handle.cpp
  src/hou/gl/gl_functions.cpp
  src/hou/gl/gl_object_handle.cpp
  src/hou/gl/gl_program_handle.cpp
  src/hou/gl/gl_shader_handle.cpp
  src/hou/gl/gl_texture_handle.cpp
  src/hou/gl/gl_version.cpp
  src/hou/gl/gl_vertex_array_handle.cpp
)

IF(WIN32)
  SET(LIB_HOUGL_SRC
    ${LIB_HOUGL_SRC}
    src/hou/gl/wgl/gl_context_impl_wgl.cpp
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

