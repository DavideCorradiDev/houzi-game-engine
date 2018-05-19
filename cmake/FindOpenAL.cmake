MESSAGE(STATUS "--- Finding OpenAL ---")

FIND_PATH(LIB_OPENAL_INCLUDE_DIR AL/al.h)
FIND_LIBRARY(LIB_OPENAL NAMES OpenAL32)

IF(NOT OPENAL_FIND_QUIETLY)
  IF(LIB_OPENAL_INCLUDE_DIR)
    MESSAGE(STATUS "Found OpenAL include dir: ${LIB_OPENAL_INCLUDE_DIR}")
  ENDIF()
  IF(LIB_OPENAL)
    MESSAGE(STATUS "Found OpenAL library: ${LIB_OPENAL}")
  ENDIF()
ENDIF()

IF(GoogleTest_FIND_REQUIRED)
  IF(NOT LIB_OPENAL_INCLUDE_DIR OR NOT LIB_OPENAL)
    MESSAGE(FATAL_ERROR "Could not find OpenAL")
  ENDIF()
ENDIF()

MESSAGE(STATUS "")
