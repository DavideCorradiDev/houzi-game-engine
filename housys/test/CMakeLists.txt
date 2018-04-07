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
  ${LIB_HOUTEST_SOURCE_DIR}/src/TestMain.cpp
  hou/sys/TestBinaryFileIn.cpp
  hou/sys/TestBinaryFileOut.cpp
  hou/sys/TestColor.cpp
  hou/sys/TestData.cpp
  hou/sys/TestFile.cpp
  hou/sys/TestFileHandle.cpp
  hou/sys/TestImage.cpp
  hou/sys/TestPixel.cpp
  hou/sys/TestTextFileIn.cpp
  hou/sys/TestTextFileOut.cpp
  hou/sys/TestVideoMode.cpp
  hou/sys/TestWindow.cpp
  hou/sys/TestWindowEvent.cpp
)



# Linked libraries.
SET(EXE_HOUSYS_TEST_LIB
  ${LIB_HOUSYS}
  ${LIB_HOUMTH}
  ${LIB_HOUCOR}
  ${LIB_GOOGLE_TEST}
)
MESSAGE(STATUS "Linked libs: ${EXE_HOUSYS_TEST_LIB}")



# Add target.
ADD_EXECUTABLE(${EXE_HOUSYS_TEST} ${EXE_HOUSYS_TEST_SRC})
SET_TARGET_PROPERTIES(${EXE_HOUSYS_TEST} PROPERTIES
  COMPILE_FLAGS ${EXE_HOU_TEST_FLAGS}
  LINKER_LANGUAGE CXX
  RUNTIME_OUTPUT_DIRECTORY ${EXE_HOUSYS_TEST_OUTPUT_DIR}
)
TARGET_LINK_LIBRARIES(${EXE_HOUSYS_TEST} ${EXE_HOUSYS_TEST_LIB})



# Create test files directory.
ADD_CUSTOM_COMMAND(
  TARGET ${EXE_HOUSYS_TEST} POST_BUILD
  COMMAND ${CMAKE_COMMAND} -E make_directory
  ${EXE_HOUSYS_TEST_OUTPUT_DIR}/housys/test/output
  COMMENT "Creating test output directory"
)



# Copy test files.
ADD_CUSTOM_COMMAND(
  TARGET ${EXE_HOUSYS_TEST} POST_BUILD
  COMMAND ${CMAKE_COMMAND} -E copy_directory
  ${CMAKE_CURRENT_SOURCE_DIR}/data
  ${EXE_HOUSYS_TEST_OUTPUT_DIR}/housys/test/data
  COMMENT "Copying test data directory to build folder"
)



MESSAGE(STATUS "")

