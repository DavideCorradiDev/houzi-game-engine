CMAKE_MINIMUM_REQUIRED(VERSION 3.3)
MESSAGE(STATUS "--- Configuring target ${LIB_GLAD} ---")

# Include directories
INCLUDE_DIRECTORIES(${LIB_GLAD_INCLUDE_DIR})

# Source files
SET(LIB_GLAD_SRC
  src/glad/glad.c
)
IF(WIN32)
SET(LIB_GLAD_SRC
  ${LIB_GLAD_SRC}
  src/glad/glad_wgl.c
)
ELSEIF(UNIX)
SET(LIB_GLAD_SRC
  ${LIB_GLAD_SRC}
  src/glad/glad_glx.c
)
ENDIF()

# Add targets
ADD_LIBRARY(${LIB_GLAD} SHARED ${LIB_GLAD_SRC})

# It is necessary to define the export symbols like this, or MSVC can't link.
TARGET_COMPILE_DEFINITIONS(${LIB_GLAD}
  PUBLIC GLAD_GLAPI_EXPORT
  PRIVATE GLAD_GLAPI_EXPORT_BUILD)

MESSAGE(STATUS "")
