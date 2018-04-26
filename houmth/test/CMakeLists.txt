CMAKE_MINIMUM_REQUIRED(VERSION 3.3)



SET(EXE_HOUMTH_TEST "${LIB_HOUMTH}-test")
MESSAGE(STATUS "--- Configuring target ${EXE_HOUMTH_TEST} ---")




# Output dir
SET(EXE_HOUMTH_TEST_OUTPUT_DIR ${CMAKE_BINARY_DIR})
MESSAGE(STATUS "Output dir: ${EXE_HOUMTH_TEST_OUTPUT_DIR}")



# Definitions
REMOVE_DEFINITIONS(-DHOU_COR_EXPORTS)
GET_PROPERTY(EXE_HOUMTH_TEST_DEFINITIONS
  DIRECTORY ${CURRENT_SOURCE_DIR}
  PROPERTY COMPILE_DEFINITIONS
)
MESSAGE(STATUS "Definitions: ${EXE_HOUMTH_TEST_DEFINITIONS}")



# Include directories.
INCLUDE_DIRECTORIES(
  ${LIB_GOOGLE_TEST_INCLUDE_DIR}
  ${LIB_HOUTEST_INCLUDE_DIR}
  ${CMAKE_CURRENT_SOURCE_DIR}
)



# Source files.
SET(EXE_HOUMTH_TEST_SRC
  ${LIB_HOUTEST_SOURCE_DIR}/src/TestMain.cpp
  hou/mth/TestMatrix.cpp
  hou/mth/TestMathFunctions.cpp
  hou/mth/TestQuaternion.cpp
  hou/mth/TestRectangle.cpp
  hou/mth/TestRotation2.cpp
  hou/mth/TestRotation3.cpp
  hou/mth/TestTransform2.cpp
  hou/mth/TestTransform3.cpp
  hou/mth/TestVec2.cpp
  hou/mth/TestVec3.cpp
)



# Linked libraries.
SET(EXE_HOUMTH_TEST_LIB
  ${LIB_HOUMTH}
  ${LIB_HOUCOR}
  ${LIB_GOOGLE_TEST}
)
MESSAGE(STATUS "Linked libs: ${EXE_HOUMTH_TEST_LIB}")



# Add target.
ADD_EXECUTABLE(${EXE_HOUMTH_TEST} ${EXE_HOUMTH_TEST_SRC})
SET_TARGET_PROPERTIES(${EXE_HOUMTH_TEST} PROPERTIES
  COMPILE_FLAGS ${EXE_HOU_TEST_FLAGS}
  LINKER_LANGUAGE CXX
  RUNTIME_OUTPUT_DIRECTORY ${EXE_HOUMTH_TEST_OUTPUT_DIR}
)
TARGET_LINK_LIBRARIES(${EXE_HOUMTH_TEST} ${EXE_HOUMTH_TEST_LIB})



# Create test files directory.
ADD_CUSTOM_COMMAND(
  TARGET ${EXE_HOUMTH_TEST} POST_BUILD
  COMMAND ${CMAKE_COMMAND} -E make_directory
  ${EXE_HOUMTH_TEST_OUTPUT_DIR}/houmth/test/output
  COMMENT "Creating test output directory"
)



# Copy test files.
ADD_CUSTOM_COMMAND(
  TARGET ${EXE_HOUMTH_TEST} POST_BUILD
  COMMAND ${CMAKE_COMMAND} -E copy_directory
  ${CMAKE_CURRENT_SOURCE_DIR}/data
  ${EXE_HOUMTH_TEST_OUTPUT_DIR}/houmth/test/data
  COMMENT "Copying test data directory to build folder"
)



MESSAGE(STATUS "")

