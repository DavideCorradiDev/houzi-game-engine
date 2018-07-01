CMAKE_MINIMUM_REQUIRED(VERSION 3.3)

SET(EXE_HOUCOR_TEST "${LIB_HOUCOR}-test")
MESSAGE(STATUS "--- Configuring target ${EXE_HOUCOR_TEST} ---")

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
  ${LIB_GOOGLE_MOCK_INCLUDE_DIR}
  ${LIB_HOUTEST_INCLUDE_DIR}
  ${CMAKE_CURRENT_SOURCE_DIR}
)

# Source files.
SET(EXE_HOUCOR_TEST_SRC
  hou/cor/houcor_test_main.cpp
  hou/cor/test_assertions.cpp
  hou/cor/test_basic_static_string.cpp
  hou/cor/test_bitwise_operators.cpp
  hou/cor/test_character_encodings.cpp
  hou/cor/test_checked_variable.cpp
  hou/cor/test_clock.cpp
  hou/cor/test_cor_exceptions.cpp
  hou/cor/test_core_functions.cpp
  hou/cor/test_exception.cpp
  hou/cor/test_is_same_signedness.cpp
  hou/cor/test_member_detector.cpp
  hou/cor/test_module.cpp
  hou/cor/test_narrow_cast.cpp
  hou/cor/test_not_null.cpp
  hou/cor/test_span.cpp
  hou/cor/test_std_array.cpp
  hou/cor/test_std_chrono.cpp
  hou/cor/test_std_iostream.cpp
  hou/cor/test_std_set.cpp
  hou/cor/test_std_string.cpp
  hou/cor/test_std_vector.cpp
  hou/cor/test_stopwatch.cpp
  hou/cor/test_template_utils.cpp
  hou/cor/test_uid_generator.cpp
)

# Linked libraries.
SET(EXE_HOUCOR_TEST_LIBS
  ${LIB_HOUCOR}
  ${LIB_GOOGLE_TEST}
  ${LIB_GOOGLE_MOCK}
)
MESSAGE(STATUS "Linked libs: ${EXE_HOUCOR_TEST_LIBS}")

# Add target.
ADD_EXECUTABLE(${EXE_HOUCOR_TEST} ${EXE_HOUCOR_TEST_SRC})
SET_TARGET_PROPERTIES(${EXE_HOUCOR_TEST} PROPERTIES
  COMPILE_FLAGS ${EXE_HOU_FLAGS}
  LINKER_LANGUAGE CXX
)
TARGET_LINK_LIBRARIES(${EXE_HOUCOR_TEST} ${EXE_HOUCOR_TEST_LIBS})

# Create test files directory.
ADD_CUSTOM_COMMAND(
  TARGET ${EXE_HOUCOR_TEST} POST_BUILD
  COMMAND ${CMAKE_COMMAND} -E make_directory
  ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/source/houcor/test/output
  COMMENT "Creating test output directory"
)

# Copy test files.
ADD_CUSTOM_COMMAND(
  TARGET ${EXE_HOUCOR_TEST} POST_BUILD
  COMMAND ${CMAKE_COMMAND} -E copy_directory
  ${CMAKE_CURRENT_SOURCE_DIR}/data
  ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/source/houcor/test/data
  COMMENT "Copying test data directory to build folder"
)

MESSAGE(STATUS "")
