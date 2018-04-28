CMAKE_MINIMUM_REQUIRED(VERSION 3.3)



SET(EXE_HOUCOR_TEST "${LIB_HOUCOR}-test")
MESSAGE(STATUS "--- Configuring target ${EXE_HOUCOR_TEST} ---")




# Output dir
SET(EXE_HOUCOR_TEST_OUTPUT_DIR ${CMAKE_BINARY_DIR})
MESSAGE(STATUS "Output dir: ${EXE_HOUCOR_TEST_OUTPUT_DIR}")



# Definitions
REMOVE_DEFINITIONS(-DHOU_COR_EXPORTS)
GET_PROPERTY(EXE_HOUCOR_TEST_DEFINITIONS
  DIRECTORY ${CURRENT_SOURCE_DIR}
  PROPERTY COMPILE_DEFINITIONS
)
MESSAGE(STATUS "Definitions: ${EXE_HOUCOR_TEST_DEFINITIONS}")



# Include directories.
INCLUDE_DIRECTORIES(
  ${LIB_GOOGLE_TEST_INCLUDE_DIR}
  ${LIB_HOUTEST_INCLUDE_DIR}
  ${CMAKE_CURRENT_SOURCE_DIR}
)



# Source files.
SET(EXE_HOUCOR_TEST_SRC
  ${LIB_HOUTEST_SOURCE_DIR}/src/TestMain.cpp
  hou/cor/TestBitwiseOperators.cpp
  hou/cor/TestCharacterEncodings.cpp
  hou/cor/TestClock.cpp
  hou/cor/TestCoreFunctions.cpp
  hou/cor/TestError.cpp
  hou/cor/TestNotNull.cpp
  hou/cor/TestSpan.cpp
  hou/cor/TestStdArray.cpp
  hou/cor/TestStdChrono.cpp
  hou/cor/TestStdString.cpp
  hou/cor/TestStdVector.cpp
  hou/cor/TestStopwatch.cpp
  hou/cor/TestTemplateUtils.cpp
  hou/cor/TestUidGenerator.cpp
)



# Linked libraries.
SET(EXE_HOUCOR_TEST_LIB
  ${LIB_HOUCOR}
  ${LIB_GOOGLE_TEST}
)
MESSAGE(STATUS "Linked libs: ${EXE_HOUCOR_TEST_LIB}")



# Add target.
ADD_EXECUTABLE(${EXE_HOUCOR_TEST} ${EXE_HOUCOR_TEST_SRC})
SET_TARGET_PROPERTIES(${EXE_HOUCOR_TEST} PROPERTIES
  COMPILE_FLAGS ${EXE_HOU_TEST_FLAGS}
  LINKER_LANGUAGE CXX
  ARCHIVE_OUTPUT_DIRECTORY ${EXE_HOUCOR_TEST_OUTPUT_DIR}
  LIBRARY_OUTPUT_DIRECTORY ${EXE_HOUCOR_TEST_OUTPUT_DIR}
  RUNTIME_OUTPUT_DIRECTORY ${EXE_HOUCOR_TEST_OUTPUT_DIR}
)
TARGET_LINK_LIBRARIES(${EXE_HOUCOR_TEST} ${EXE_HOUCOR_TEST_LIB})



# Create test files directory.
ADD_CUSTOM_COMMAND(
  TARGET ${EXE_HOUCOR_TEST} POST_BUILD
  COMMAND ${CMAKE_COMMAND} -E make_directory
  ${EXE_HOUCOR_TEST_OUTPUT_DIR}/source/houcor/test/output
  COMMENT "Creating test output directory"
)



# Copy test files.
ADD_CUSTOM_COMMAND(
  TARGET ${EXE_HOUCOR_TEST} POST_BUILD
  COMMAND ${CMAKE_COMMAND} -E copy_directory
  ${CMAKE_CURRENT_SOURCE_DIR}/data
  ${EXE_HOUCOR_TEST_OUTPUT_DIR}/source/houcor/test/data
  COMMENT "Copying test data directory to build folder"
)



MESSAGE(STATUS "")

