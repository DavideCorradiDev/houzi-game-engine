MESSAGE(STATUS "--- Looking for SDL2 ---")

FIND_PATH(LIB_SDL2_INCLUDE_DIR SDL.h PATH_SUFFIXES SDL2)
FIND_LIBRARY(LIB_SDL2 NAMES SDL2)

IF(NOT SDL2_FIND_QUIETLY)
  IF(LIB_SDL2_INCLUDE_DIR)
    MESSAGE(STATUS "Found SDL2 include dir: ${LIB_SDL2_INCLUDE_DIR}")
  ENDIF()
  IF(LIB_SDL2)
    MESSAGE(STATUS "Found SDL2 library: ${LIB_SDL2}")
  ENDIF()
ENDIF()

IF(SDL2_FIND_REQUIRED)
  IF(NOT LIB_SDL2_INCLUDE_DIR OR NOT LIB_SDL2)
    MESSAGE(SEND_ERROR
      "Could not find SDL2. Please manually specify the library and include \
      paths or set HOU_CFG_BUILD_SDL2 to build SDL2 from source.")
  ENDIF()
ENDIF()

MESSAGE(STATUS "")