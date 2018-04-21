CMAKE_MINIMUM_REQUIRED(VERSION 3.3)
MESSAGE(STATUS "--- Configuring target ${LIB_HOUSYS} ---")



# Output dir
SET(LIB_HOUSYS_OUTPUT_DIR ${CMAKE_BINARY_DIR})
MESSAGE(STATUS "Output dir: ${LIB_HOUSYS_OUTPUT_DIR}")



# Definitions.
ADD_DEFINITIONS(-DHOU_SYS_EXPORTS)
GET_PROPERTY(LIB_HOUSYS_DEFINITIONS
  DIRECTORY ${CURRENT_SOURCE_DIR}
  PROPERTY COMPILE_DEFINITIONS
)
MESSAGE(STATUS "Definitions: ${LIB_HOUSYS_DEFINITIONS}")



# Include directories.
INCLUDE_DIRECTORIES(
  ${LIB_SOIL_INCLUDE_DIR}
  ${LIB_HOUCOR_INCLUDE_DIR}
  ${LIB_HOUMTH_INCLUDE_DIR}
  ${LIB_HOUSYS_INCLUDE_DIR}
)



# Source files.
SET(LIB_HOUSYS_SRC
  src/hou/sys/BinaryFileIn.cpp
  src/hou/sys/BinaryFileOut.cpp
  src/hou/sys/Color.cpp
  src/hou/sys/File.cpp
  src/hou/sys/FileHandle.cpp
  src/hou/sys/FileOpenMode.cpp
  src/hou/sys/FileType.cpp
  src/hou/sys/Image.cpp
  src/hou/sys/Keyboard.cpp
  src/hou/sys/ModifierKeys.cpp
  src/hou/sys/MouseButton.cpp
  src/hou/sys/MouseWheel.cpp
  src/hou/sys/KeyCode.cpp
  src/hou/sys/Pixel.cpp
  src/hou/sys/PixelFormat.cpp
  src/hou/sys/ScanCode.cpp
  src/hou/sys/SysError.cpp
  src/hou/sys/SystemWindow.cpp
  src/hou/sys/TextFileIn.cpp
  src/hou/sys/TextFileOut.cpp
  src/hou/sys/TextStream.cpp
  src/hou/sys/VideoMode.cpp
  src/hou/sys/Window.cpp
  src/hou/sys/WindowEvent.cpp
  src/hou/sys/WindowEventType.cpp
  src/hou/sys/WindowImpl.cpp
  src/hou/sys/WindowStyle.cpp
)

IF(WIN32)
  SET(LIB_HOUSYS_SRC
    ${LIB_HOUSYS_SRC}
    src/hou/sys/win/FileHandleWin.cpp
    src/hou/sys/win/KeyboardWin.cpp
    src/hou/sys/win/MouseWin.cpp
    src/hou/sys/win/VideoModeWin.cpp
    src/hou/sys/win/WinError.cpp
    src/hou/sys/win/WindowImplWin.cpp
  )
ENDIF()



# Linked libraries.
IF(HOU_CFG_SHARED_LIBS)
  SET(LIB_HOUSYS_LIB
    ${LIB_HOUMTH}
    ${LIB_HOUCOR}
  )
ELSE()
  SET(LIB_HOUSYS_LIB)
ENDIF()
# SOIL is always built as a static lib and linked.
# In this way it will be incorporated into housys.
# SOIL is completely encapsulated so there is no need to expose it.
SET(LIB_HOUSYS_LIB
  ${LIB_HOUSYS_LIB}
  ${LIB_SOIL}
)
MESSAGE(STATUS "Linked libs: ${LIB_HOUSYS_LIB}")



# Add targets.
IF(HOU_CFG_SHARED_LIBS)
  ADD_LIBRARY(${LIB_HOUSYS} SHARED ${LIB_HOUSYS_SRC})
ELSE()
  ADD_LIBRARY(${LIB_HOUSYS} STATIC ${LIB_HOUSYS_SRC})
ENDIF()
SET_TARGET_PROPERTIES(${LIB_HOUSYS} PROPERTIES
  COMPILE_FLAGS ${LIB_HOU_FLAGS}
  LINKER_LANGUAGE CXX
  ARCHIVE_OUTPUT_DIRECTORY ${LIB_HOUSYS_OUTPUT_DIR}
  LIBRARY_OUTPUT_DIRECTORY ${LIB_HOUSYS_OUTPUT_DIR}
  RUNTIME_OUTPUT_DIRECTORY ${LIB_HOUSYS_OUTPUT_DIR}
)
TARGET_LINK_LIBRARIES(${LIB_HOUSYS} ${LIB_HOUSYS_LIB})



MESSAGE(STATUS "")



IF(HOU_CFG_BUILD_SYS_TESTS)
  ADD_SUBDIRECTORY(${CMAKE_CURRENT_SOURCE_DIR}/test)
ENDIF()

