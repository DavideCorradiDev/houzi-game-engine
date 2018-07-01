CMAKE_MINIMUM_REQUIRED(VERSION 3.3)

# Include directories
INCLUDE_DIRECTORIES(${LIB_SOIL_INCLUDE_DIR}/soil)

# Source files
SET(LIB_SOIL_SRC
  src/soil/image_DXT.c
  src/soil/image_helper.c
  src/soil/stb_image_aug.c
  src/soil/SOIL.c
)

# Linked libraries
SET(LIB_SOIL_LIB
  ${OPENGL_LIBRARIES}
)
MESSAGE(STATUS "Linked libs: ${LIB_SOIL_LIB}")

# Add targets
ADD_LIBRARY(${LIB_SOIL} STATIC ${LIB_SOIL_SRC})
TARGET_LINK_LIBRARIES(${LIB_SOIL} ${LIB_SOIL_LIB})
