CMAKE_MINIMUM_REQUIRED(VERSION 3.3)



SET(EXE_HOUSYS_TEST "${LIB_HOUSYS}-test")
MESSAGE(STATUS "--- Configuring target ${EXE_HOUSYS_TEST} ---")




# Output dir
SET(EXE_HOUSYS_TEST_OUTPUT_DIR ${CMAKE_BINARY_DIR})
MESSAGE(STATUS "Output dir: ${EXE_HOUSYS_TEST_OUTPUT_DIR}")



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
  ${LIB_HOUTEST_INCLUDE_DIR}
  ${CMAKE_CURRENT_SOURCE_DIR}
)



# Source files.
SET(EXE_HOUSYS_TEST_SRC
  ${LIB_HOUTEST_SOURCE_DIR}/src/test_main.cpp
  hou/sys/test_binary_file_in.cpp
  hou/sys/test_binary_file_out.cpp
  hou/sys/test_color.cpp
  hou/sys/test_data.cpp
  hou/sys/test_file.cpp
  hou/sys/test_file_handle.cpp
  hou/sys/test_image.cpp
  hou/sys/test_image_file.cpp
  hou/sys/test_pixel.cpp
  hou/sys/test_monitor.cpp
  hou/sys/test_sys_base.cpp
  hou/sys/test_sys_exceptions.cpp
  hou/sys/test_sys_module.cpp
  # hou/sys/test_system_window.cpp
  hou/sys/test_text_file_in.cpp
  hou/sys/test_text_file_out.cpp
  hou/sys/test_video_mode.cpp
  # hou/sys/test_window_event.cpp
)



# Linked libraries.
SET(EXE_HOUSYS_TEST_LIBS
  ${LIB_HOUSYS}
  ${LIB_HOUMTH}
  ${LIB_HOUCOR}
  ${LIB_GOOGLE_TEST}
)
MESSAGE(STATUS "Linked libs: ${EXE_HOUSYS_TEST_LIBS}")



# Add target.
ADD_EXECUTABLE(${EXE_HOUSYS_TEST} ${EXE_HOUSYS_TEST_SRC})
SET_TARGET_PROPERTIES(${EXE_HOUSYS_TEST} PROPERTIES
  COMPILE_FLAGS ${EXE_HOU_TEST_FLAGS}
  LINKER_LANGUAGE CXX
  RUNTIME_OUTPUT_DIRECTORY ${EXE_HOUSYS_TEST_OUTPUT_DIR}
)
TARGET_LINK_LIBRARIES(${EXE_HOUSYS_TEST} ${EXE_HOUSYS_TEST_LIBS})



# Create test files directory.
ADD_CUSTOM_COMMAND(
  TARGET ${EXE_HOUSYS_TEST} POST_BUILD
  COMMAND ${CMAKE_COMMAND} -E make_directory
  ${EXE_HOUSYS_TEST_OUTPUT_DIR}/source/housys/test/output
  COMMENT "Creating test output directory"
)



# Copy test files.
ADD_CUSTOM_COMMAND(
  TARGET ${EXE_HOUSYS_TEST} POST_BUILD
  COMMAND ${CMAKE_COMMAND} -E copy_directory
  ${CMAKE_CURRENT_SOURCE_DIR}/data
  ${EXE_HOUSYS_TEST_OUTPUT_DIR}/source/housys/test/data
  COMMENT "Copying test data directory to build folder"
)



MESSAGE(STATUS "")

