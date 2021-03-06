CMAKE_MINIMUM_REQUIRED(VERSION 3.3)
MESSAGE(STATUS "--- Configuring target ${LIB_HOUSYS} ---")

# Definitions.
ADD_DEFINITIONS(-DHOU_SYS_EXPORTS)
ADD_DEFINITIONS(-DSDL_DEFAULT_ASSERT_LEVEL=0)
GET_PROPERTY(LIB_HOUSYS_DEFINITIONS
  DIRECTORY ${CURRENT_SOURCE_DIR}
  PROPERTY COMPILE_DEFINITIONS
)
MESSAGE(STATUS "Definitions: ${LIB_HOUSYS_DEFINITIONS}")

# Include directories.
INCLUDE_DIRECTORIES(
  ${LIB_SOIL_INCLUDE_DIR}
  ${LIB_SDL2_INCLUDE_DIR}
  ${LIB_HOUCOR_INCLUDE_DIR}
  ${LIB_HOUMTH_INCLUDE_DIR}
  ${LIB_HOUSYS_INCLUDE_DIR}
)

# Source files.
SET(LIB_HOUSYS_SRC
  src/hou/sys/binary_file_in.cpp
  src/hou/sys/binary_file_out.cpp
  src/hou/sys/color.cpp
  src/hou/sys/display_mode.cpp
  src/hou/sys/display_format.cpp
  src/hou/sys/display_format_mask.cpp
  src/hou/sys/event.cpp
  src/hou/sys/file.cpp
  src/hou/sys/file_handle.cpp
  src/hou/sys/file_open_mode.cpp
  src/hou/sys/file_type.cpp
  src/hou/sys/image.cpp
  src/hou/sys/image_file.cpp
  src/hou/sys/key_code.cpp
  src/hou/sys/keyboard.cpp
  src/hou/sys/modifier_keys.cpp
  src/hou/sys/display.cpp
  src/hou/sys/mouse.cpp
  src/hou/sys/mouse_button.cpp
  src/hou/sys/mouse_buttons_state.cpp
  src/hou/sys/pixel.cpp
  src/hou/sys/pixel_format.cpp
  src/hou/sys/scan_code.cpp
  src/hou/sys/sys_exceptions.cpp
  src/hou/sys/sys_module.cpp
  src/hou/sys/text_input.cpp
  src/hou/sys/text_file_in.cpp
  src/hou/sys/text_file_out.cpp
  src/hou/sys/text_stream.cpp
  src/hou/sys/window.cpp
  src/hou/sys/window_mode.cpp
)

IF(WIN32)
  SET(LIB_HOUSYS_SRC
    ${LIB_HOUSYS_SRC}
    src/hou/sys/win/file_handle_win.cpp
  )
ELSEIF(UNIX)
  SET(LIB_HOUSYS_SRC
    ${LIB_HOUSYS_SRC}
    src/hou/sys/unix/file_handle_unix.cpp
  )
ENDIF()

# Linked libraries.
SET(LIB_HOUSYS_LIBS
  ${LIB_SOIL}
)
IF(NOT HOU_CFG_BUILD_STATIC_LIBS)
  SET(LIB_HOUSYS_LIBS
    ${LIB_HOUSYS_LIBS}
    ${LIB_HOUMTH}
    ${LIB_HOUCOR}
    ${LIB_SDL2}
  )
ENDIF()
MESSAGE(STATUS "Linked libs: ${LIB_HOUSYS_LIBS}")

# Add targets.
IF(HOU_CFG_BUILD_STATIC_LIBS)
  ADD_LIBRARY(${LIB_HOUSYS} STATIC ${LIB_HOUSYS_SRC})
ELSE()
  ADD_LIBRARY(${LIB_HOUSYS} SHARED ${LIB_HOUSYS_SRC})
ENDIF()
SET_TARGET_PROPERTIES(${LIB_HOUSYS} PROPERTIES
  COMPILE_FLAGS ${LIB_HOU_FLAGS}
  LINKER_LANGUAGE CXX
)
TARGET_LINK_LIBRARIES(${LIB_HOUSYS} ${LIB_HOUSYS_LIBS})

MESSAGE(STATUS "")

IF(HOU_CFG_BUILD_TESTS)
  ADD_SUBDIRECTORY(${CMAKE_CURRENT_SOURCE_DIR}/test)
ENDIF()
