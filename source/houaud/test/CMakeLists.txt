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
  ${LIB_HOUTEST_SOURCE_DIR}/src/test_main.cpp
  hou/aud/test_aud_base.cpp
  hou/aud/test_aud_base_test_specific_context.cpp
  hou/aud/test_aud_exceptions.cpp
  hou/aud/test_audio_buffer.cpp
  hou/aud/test_audio_context.cpp
  hou/aud/test_audio_source.cpp
  hou/aud/test_data.cpp
  hou/aud/test_empty_audio_stream_in.cpp
  hou/aud/test_listener.cpp
  hou/aud/test_memory_audio_source.cpp
  hou/aud/test_ogg_file_in.cpp
  hou/aud/test_sound_model.cpp
  hou/aud/test_streaming_audio_source.cpp
  hou/aud/test_wav_file_in.cpp
)



# Linked libraries.
SET(EXE_HOUAUD_TEST_LIBS
  ${LIB_HOUAUD}
  ${LIB_HOUAL}
  ${LIB_HOUSYS}
  ${LIB_HOUMTH}
  ${LIB_HOUCOR}
  ${LIB_GOOGLE_TEST}
)
MESSAGE(STATUS "Linked libs: ${EXE_HOUAUD_TEST_LIBS}")



# Add target.
ADD_EXECUTABLE(${EXE_HOUAUD_TEST} ${EXE_HOUAUD_TEST_SRC})
SET_TARGET_PROPERTIES(${EXE_HOUAUD_TEST} PROPERTIES
  COMPILE_FLAGS ${EXE_HOU_TEST_FLAGS}
  LINKER_LANGUAGE CXX
  RUNTIME_OUTPUT_DIRECTORY ${EXE_HOUAUD_TEST_OUTPUT_DIR}
)
TARGET_LINK_LIBRARIES(${EXE_HOUAUD_TEST} ${EXE_HOUAUD_TEST_LIBS})



# Create test files directory.
ADD_CUSTOM_COMMAND(
  TARGET ${EXE_HOUAUD_TEST} POST_BUILD
  COMMAND ${CMAKE_COMMAND} -E make_directory
  ${EXE_HOUAUD_TEST_OUTPUT_DIR}/source/houaud/test/output
  COMMENT "Creating test output directory"
)



# Copy test files.
ADD_CUSTOM_COMMAND(
  TARGET ${EXE_HOUAUD_TEST} POST_BUILD
  COMMAND ${CMAKE_COMMAND} -E copy_directory
  ${CMAKE_CURRENT_SOURCE_DIR}/data
  ${EXE_HOUAUD_TEST_OUTPUT_DIR}/source/houaud/test/data
  COMMENT "Copying test data directory to build folder"
)



MESSAGE(STATUS "")

