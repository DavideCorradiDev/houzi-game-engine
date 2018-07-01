MESSAGE(STATUS "--- Looking for gtest  ---")

FIND_PATH(LIB_GOOGLE_TEST_INCLUDE_DIR gtest/gtest.h)
FIND_LIBRARY(LIB_GOOGLE_TEST NAMES gtest)

IF(NOT GOOGLE_TEST_FIND_QUIETLY)
  IF(LIB_GOOGLE_TEST_INCLUDE_DIR)
    MESSAGE(STATUS "Found GoogleTest include dir: ${LIB_GOOGLE_TEST_INCLUDE_DIR}")
  ENDIF()
  IF(LIB_GOOGLE_TEST)
    MESSAGE(STATUS "Found GoogleTest library: ${LIB_GOOGLE_TEST}")
  ENDIF()
ENDIF()

IF(GoogleTest_FIND_REQUIRED)
  IF(NOT LIB_GOOGLE_TEST_INCLUDE_DIR OR NOT LIB_GOOGLE_TEST)
    MESSAGE(SEND_ERROR
      "Could not find GoogleTest. Please manually specify the library and \
      include paths or set HOU_CFG_BUILD_GOOGLE_TEST to build GoogleTest from \
      source.")
  ENDIF()
ENDIF()

MESSAGE(STATUS "")
