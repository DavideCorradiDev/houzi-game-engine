CMAKE_MINIMUM_REQUIRED(VERSION 3.3)



SET(EXE_HOUAUD_TEST "${LIB_HOUAUD}-test")
MESSAGE(STATUS "--- Configuring target ${EXE_HOUAUD_TEST} ---")




# Output dir
SET(EXE_HOUAUD_TEST_OUTPUT_DIR ${CMAKE_BINARY_DIR})
MESSAGE(STATUS "Output dir: ${EXE_HOUAUD_TEST_OUTPUT_DIR}")



# Definitions
REMOVE_DEFINITIONS(-DHOU_AUD_EXPORTS)
GET_PROPERTY(EXE_HOUAUD_TEST_DEFINITIONS
  DIRECTORY ${CURRENT_SOURCE_DIR}
  PROPERTY COMPILE_DEFINITIONS
)
MESSAGE(STATUS "Definitions: ${EXE_HOUAUD_TEST_DEFINITIONS}")



# Include directories.
INCLUDE_DIRECTORIES(
  ${LIB_GOOGLE_TEST_INCLUDE_DIR}
  ${LIB_HOUTEST_INCLUDE_DIR}
  ${CMAKE_CURRENT_SOURCE_DIR}
)



# Source files.
SET(EXE_HOUAUD_TEST_SRC
  ${LIB_HOUTEST_SOURCE_DIR}/src/TestMain.cpp
  hou/aud/TestAudBase.cpp
  hou/aud/TestAudBaseTestSpecificContext.cpp
  hou/aud/TestAudioBuffer.cpp
  hou/aud/TestAudioContext.cpp
  hou/aud/TestAudioSource.cpp
  hou/aud/TestAudioSourceBase.cpp
  hou/aud/TestData.cpp
  hou/aud/TestEmptyAudioStreamIn.cpp
  hou/aud/TestListener.cpp
  hou/aud/TestOggFileIn.cpp
  hou/aud/TestSoundModel.cpp
  hou/aud/TestStreamingAudioSource.cpp
  hou/aud/TestWavFileIn.cpp
)



# Linked libraries.
SET(EXE_HOUAUD_TEST_LIB
  ${LIB_HOUAUD}
  ${LIB_HOUAL}
  ${LIB_OPENAL}
  ${LIB_HOUSYS}
  ${LIB_HOUMTH}
  ${LIB_HOUCOR}
  ${LIB_GOOGLE_TEST}
)
MESSAGE(STATUS "Linked libs: ${EXE_HOUAUD_TEST_LIB}")



# Add target.
ADD_EXECUTABLE(${EXE_HOUAUD_TEST} ${EXE_HOUAUD_TEST_SRC})
SET_TARGET_PROPERTIES(${EXE_HOUAUD_TEST} PROPERTIES
  COMPILE_FLAGS ${EXE_HOU_TEST_FLAGS}
  LINKER_LANGUAGE CXX
  RUNTIME_OUTPUT_DIRECTORY ${EXE_HOUAUD_TEST_OUTPUT_DIR}
)
TARGET_LINK_LIBRARIES(${EXE_HOUAUD_TEST} ${EXE_HOUAUD_TEST_LIB})



# Create test files directory.
ADD_CUSTOM_COMMAND(
  TARGET ${EXE_HOUAUD_TEST} POST_BUILD
  COMMAND ${CMAKE_COMMAND} -E make_directory
  ${EXE_HOUAUD_TEST_OUTPUT_DIR}/houaud/test/output
  COMMENT "Creating test output directory"
)



# Copy test files.
ADD_CUSTOM_COMMAND(
  TARGET ${EXE_HOUAUD_TEST} POST_BUILD
  COMMAND ${CMAKE_COMMAND} -E copy_directory
  ${CMAKE_CURRENT_SOURCE_DIR}/data
  ${EXE_HOUAUD_TEST_OUTPUT_DIR}/houaud/test/data
  COMMENT "Copying test data directory to build folder"
)



MESSAGE(STATUS "")

