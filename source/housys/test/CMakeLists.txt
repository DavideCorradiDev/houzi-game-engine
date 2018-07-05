CMAKE_MINIMUM_REQUIRED(VERSION 3.3)

SET(EXE_HOUSYS_TEST "${LIB_HOUSYS}-test")
MESSAGE(STATUS "--- Configuring target ${EXE_HOUSYS_TEST} ---")

# Definitions
REMOVE_DEFINITIONS(-DHOU_SYS_EXPORTS)
GET_PROPERTY(EXE_HOUSYS_TEST_DEFINITIONS
  DIRECTORY ${CURRENT_SOURCE_DIR}
  PROPERTY COMPILE_DEFINITIONS
)
MESSAGE(STATUS "Definitions: ${EXE_HOUSYS_TEST_DEFINITIONS}")

# Include directories.
INCLUDE_DIRECTORIES(
  ${LIB_GOOGLE_TEST_INCLUDE_DIR}
  ${LIB_GOOGLE_MOCK_INCLUDE_DIR}
  ${LIB_HOUTEST_INCLUDE_DIR}
  ${CMAKE_CURRENT_SOURCE_DIR}
)

# Source files.
SET(EXE_HOUSYS_TEST_SRC
  hou/sys/housys_test_main.cpp
  hou/sys/test_binary_file_in.cpp
  hou/sys/test_binary_file_out.cpp
  hou/sys/test_color.cpp
  hou/sys/test_data.cpp
  hou/sys/test_display_mode.cpp
  hou/sys/test_display_format.cpp
  hou/sys/test_display_format_mask.cpp
  hou/sys/test_event.cpp
  hou/sys/test_file.cpp
  hou/sys/test_file_handle.cpp
  hou/sys/test_image.cpp
  hou/sys/test_image_file.cpp
  hou/sys/test_keyboard.cpp
  hou/sys/test_keys.cpp
  hou/sys/test_mouse.cpp
  hou/sys/test_mouse_buttons_state.cpp
  hou/sys/test_pixel.cpp
  hou/sys/test_pixel_format.cpp
  hou/sys/test_display.cpp
  hou/sys/test_sys_exceptions.cpp
  hou/sys/test_window.cpp
  hou/sys/test_text_file_in.cpp
  hou/sys/test_text_file_out.cpp
)

# Linked libraries.
SET(EXE_HOUSYS_TEST_LIBS
  ${LIB_HOUSYS}
  ${LIB_HOUMTH}
  ${LIB_HOUCOR}
  ${LIB_SDL2}
  ${LIB_GOOGLE_TEST}
  ${LIB_GOOGLE_MOCK}
)
MESSAGE(STATUS "Linked libs: ${EXE_HOUSYS_TEST_LIBS}")

# Embed files in emscripten.
IF(EMSCRIPTEN)
  SET(HOU_EMBEDDING_PATHS "--embed-file ${CMAKE_SOURCE_DIR}/source/housys/test/data@source/housys/test/data")
  SET(HOU_EMBEDDING_PATHS "${HOU_EMBEDDING_PATHS} --embed-file ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/source/housys/test/output@source/housys/test/output")
  SET(EXE_HOU_FLAGS "${EXE_HOU_FLAGS} ${HOU_EMBEDDING_PATHS}")
  SET(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} ${HOU_EMBEDDING_PATHS}")
ENDIF()

# Add target.
ADD_EXECUTABLE(${EXE_HOUSYS_TEST} ${EXE_HOUSYS_TEST_SRC})
SET_TARGET_PROPERTIES(${EXE_HOUSYS_TEST} PROPERTIES
  COMPILE_FLAGS ${EXE_HOU_FLAGS}
  LINKER_LANGUAGE CXX
)
TARGET_LINK_LIBRARIES(${EXE_HOUSYS_TEST} ${EXE_HOUSYS_TEST_LIBS})

# Create test files directory.
ADD_CUSTOM_COMMAND(
  TARGET ${EXE_HOUSYS_TEST} POST_BUILD
  COMMAND ${CMAKE_COMMAND} -E make_directory
  ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/source/housys/test/output
  COMMENT "Creating test output directory"
)

# Copy test files.
ADD_CUSTOM_COMMAND(
  TARGET ${EXE_HOUSYS_TEST} POST_BUILD
  COMMAND ${CMAKE_COMMAND} -E copy_directory
  ${CMAKE_CURRENT_SOURCE_DIR}/data
  ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/source/housys/test/data
  COMMENT "Copying test data directory to build folder"
)

MESSAGE(STATUS "")
