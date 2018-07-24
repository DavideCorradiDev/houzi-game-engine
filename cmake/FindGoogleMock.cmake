MESSAGE(STATUS "--- Looking for gmock  ---")

FIND_PATH(LIB_GOOGLE_MOCK_INCLUDE_DIR gmock/gmock.h)
FIND_LIBRARY(LIB_GOOGLE_MOCK NAMES gmock)

IF(NOT GOOGLE_MOCK_FIND_QUIETLY)
  IF(LIB_GOOGLE_MOCK_INCLUDE_DIR)
    MESSAGE(STATUS "Found GoogleMock include dir: ${LIB_GOOGLE_MOCK_INCLUDE_DIR}")
  ENDIF()
  IF(LIB_GOOGLE_MOCK)
    MESSAGE(STATUS "Found GoogleMock library: ${LIB_GOOGLE_MOCK}")
  ENDIF()
ENDIF()

IF(GoogleMock_FIND_REQUIRED)
  IF(NOT LIB_GOOGLE_MOCK_INCLUDE_DIR OR NOT LIB_GOOGLE_MOCK)
    MESSAGE(SEND_ERROR
      "Could not find GoogleMock. Please manually specify the library and \
      include paths or set HOU_CFG_BUILD_GOOGLE_TEST to build GoogleMock from \
      source.")
  ENDIF()
ENDIF()

MESSAGE(STATUS "")
