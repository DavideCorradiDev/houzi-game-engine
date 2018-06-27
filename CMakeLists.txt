CMAKE_MINIMUM_REQUIRED(VERSION 3.3)
SET(PROJECT_NAME "houzi-game-engine")
PROJECT(${PROJECT_NAME} C CXX)

# Includes.
INCLUDE(${CMAKE_CURRENT_SOURCE_DIR}/cmake/CleanUp.cmake)

# Set current version.
SET(HOU_VERSION_MAJOR 0)
SET(HOU_VERSION_MINOR 4)
SET(HOU_VERSION_PATCH 0)
MESSAGE(STATUS "--- Configuring ${PROJECT_NAME} version ${HOU_VERSION_MAJOR}.${HOU_VERSION_MINOR}.${HOU_VERSION_PATCH} ---")
MESSAGE(STATUS "")

# Set CMake module and include paths.
SET(CMAKE_MODULE_PATH ${PROJECT_SOURCE_DIR}/cmake)

# Set compiler variables
# MINGW exists by default.
# MSVC exists by default.
IF("${CMAKE_CXX_COMPILER_ID}" STREQUAL "GNU")
  SET(GCC 1)
ELSEIF("${CMAKE_CXX_COMPILER_ID}" STREQUAL "Clang")
  SET(CLANG 1)
ENDIF()

# Check if OS is supported.
MESSAGE(STATUS "--- OS check ---")
IF(WIN32 OR UNIX)
  MESSAGE(STATUS "Supported OS: ${CMAKE_SYSTEM}")
ELSE()
  MESSAGE(FATAL_ERROR, "Unsupported OS: ${CMAKE_SYSTEM}")
ENDIF()

IF(WIN32)
  IF(MINGW OR MSVC)
    MESSAGE(STATUS "Supported Compiler: ${CMAKE_CXX_COMPILER_ID}")
  ELSE()
    MESSAGE(FATAL_ERROR "Unsupported Compiler: ${CMAKE_CXX_COMPILER_ID}")
  ENDIF()
ELSEIF(UNIX)
  IF(GCC)
    MESSAGE(STATUS "Supported Compiler: ${CMAKE_CXX_COMPILER_ID}")
  ELSE()
    MESSAGE(FATAL_ERROR "Unsupported Compiler: ${CMAKE_CXX_COMPILER_ID}")
  ENDIF()
ENDIF()

MESSAGE(STATUS "")

# Print generic information about compiler, OS, and source and build directories
MESSAGE(STATUS "--- General information ---")
MESSAGE(STATUS "Compiler: ${CMAKE_CXX_COMPILER_ID}")
MESSAGE(STATUS "System: ${CMAKE_SYSTEM}")
MESSAGE(STATUS "Binary dir: ${PROJECT_BINARY_DIR}")
MESSAGE(STATUS "Source dir: ${PROJECT_SOURCE_DIR}")
MESSAGE(STATUS "Module path: ${CMAKE_MODULE_PATH}")

# Default build type.
IF(NOT CMAKE_BUILD_TYPE)
  SET(CMAKE_BUILD_TYPE "Release" CACHE STRING "Choose build type, options are: Debug, Release." FORCE)
ENDIF()

# Options and target name.
OPTION(HOU_CFG_BUILD_TESTS
  "Build test executables."
  ON
)
IF(HOU_CFG_BUILD_TESTS)
  OPTION(HOU_CFG_BUILD_GOOGLE_TEST
    "Build the gtest library. If unset, look for installed gtest libraries."
    OFF
  )
ELSE()
  UNSET_VAR(HOU_CFG_BUILD_GOOGLE_TEST)
ENDIF()
OPTION(HOU_CFG_BUILD_DEMOS
  "Build example executables."
  ON
)
OPTION(HOU_CFG_BUILD_SDL2
  "Build the SDL library. If unset, look for installed SDL libraries."
  OFF
)
OPTION(HOU_CFG_BUILD_OPENAL_SOFT
  "Build the OpenAL-Soft library. If unset, look for an installed OpenAL implementation."
  OFF
)
OPTION(HOU_CFG_BUILD_STATIC_LIBS
  "If set, build static libraries. If unset, build shared libraries."
  OFF
)
OPTION(HOU_CFG_DISABLE_EXCEPTIONS
  "If set, disable exception handling and crash in case of errors. If unset, use exceptions for error handling."
  OFF
)
OPTION(HOU_CFG_ENABLE_GL_ERROR_CHECKS
  "Enable GL function call error checks for performance."
  OFF
)
OPTION(HOU_CFG_ENABLE_AL_ERROR_CHECKS
  "Enable AL function call error checks for performance."
  OFF
)

# Definitions.
IF(CMAKE_BUILD_TYPE MATCHES Debug)
  ADD_DEFINITIONS(-DHOU_DEBUG)
ELSEIF(CMAKE_BUILD_TYPE MATCHES Release)
  ADD_DEFINITIONS(-DNDEBUG)
ENDIF()
IF(HOU_CFG_BUILD_STATIC_LIBS)
  ADD_DEFINITIONS(-DHOU_STATIC)
ENDIF()
IF(HOU_CFG_DISABLE_EXCEPTIONS)
  ADD_DEFINITIONS(-DHOU_DISABLE_EXCEPTIONS)
ENDIF()
IF(HOU_CFG_ENABLE_GL_ERROR_CHECKS)
  ADD_DEFINITIONS(-DHOU_ENABLE_GL_ERROR_CHECKS)
ENDIF()
IF(HOU_CFG_ENABLE_AL_ERROR_CHECKS)
  ADD_DEFINITIONS(-DHOU_ENABLE_AL_ERROR_CHECKS)
ENDIF()
ADD_DEFINITIONS(-DSDL_DEFAULT_ASSERT_LEVEL=0)

# Compiler flags

# Used by all houzi-game-engine targets and some external libs.
SET(COMPILER_FLAGS_BASIC "${CMAKE_CXX_FLAGS}")
# Used by all houzi-game-engine targets.
SET(COMPILER_FLAGS_COMMON "")
# Used by all houzi-game-engine libraries.
SET(COMPILER_FLAGS_LIB "")
# Used by all houzi-game-engine test executables.
SET(COMPILER_FLAGS_TESTS "")

IF(MINGW OR GCC)

  IF(CMAKE_BUILD_TYPE MATCHES Release)
    SET(COMPILER_FLAGS_BASIC "${COMPILER_FLAGS_BASIC} -O2")
  ENDIF()

  IF(HOU_CFG_DISABLE_EXCEPTIONS)
    SET(COMPILER_FLAGS_BASIC "${COMPILER_FLAGS_BASIC} -fno-exceptions")
  ELSE()
    SET(COMPILER_FLAGS_BASIC "${COMPILER_FLAGS_BASIC} -fexceptions")
  ENDIF()

  IF(MINGW)
    SET(COMPILER_FLAGS_BASIC "${COMPILER_FLAGS_BASIC} -mthreads")
  ENDIF()

  SET(COMPILER_FLAGS_COMMON "${COMPILER_FLAGS_COMMON} -std=c++14")

  SET(COMPILER_FLAGS_COMMON "${COMPILER_FLAGS_COMMON} -Wall")
  SET(COMPILER_FLAGS_COMMON "${COMPILER_FLAGS_COMMON} -Wextra")
  SET(COMPILER_FLAGS_COMMON "${COMPILER_FLAGS_COMMON} -pedantic")

  # Extra warning compiler flags
  SET(COMPILER_FLAGS_LIB "${COMPILER_FLAGS_LIB} -Wzero-as-null-pointer-constant")
  SET(COMPILER_FLAGS_LIB "${COMPILER_FLAGS_LIB} -Wswitch-enum")
  SET(COMPILER_FLAGS_LIB "${COMPILER_FLAGS_LIB} -Wmissing-declarations")
  SET(COMPILER_FLAGS_LIB "${COMPILER_FLAGS_LIB} -Wunreachable-code")
  SET(COMPILER_FLAGS_LIB "${COMPILER_FLAGS_LIB} -Wfloat-equal")
  SET(COMPILER_FLAGS_LIB "${COMPILER_FLAGS_LIB} -Wundef")
  SET(COMPILER_FLAGS_LIB "${COMPILER_FLAGS_LIB} -Wcast-align")
  SET(COMPILER_FLAGS_LIB "${COMPILER_FLAGS_LIB} -Wredundant-decls")
  SET(COMPILER_FLAGS_LIB "${COMPILER_FLAGS_LIB} -Winit-self")
  SET(COMPILER_FLAGS_LIB "${COMPILER_FLAGS_LIB} -Wshadow")
  SET(COMPILER_FLAGS_LIB "${COMPILER_FLAGS_LIB} -Wnon-virtual-dtor")

ELSEIF(MSVC)

  SET(COMPILER_FLAGS_BASIC "")

  # Define Windows symbols.
  SET(COMPILER_FLAGS_BASIC "${COMPILER_FLAGS_BASIC} /DWIN32")
  SET(COMPILER_FLAGS_BASIC "${COMPILER_FLAGS_BASIC} /DWINDOWS")

  # Link shared runtime library.
  IF(CMAKE_BUILD_TYPE MATCHES Release)
    SET(COMPILER_FLAGS_BASIC "${COMPILER_FLAGS_BASIC} /MD")
  ELSE()
    SET(COMPILER_FLAGS_BASIC "${COMPILER_FLAGS_BASIC} /MDd")
  ENDIF()

  IF(CMAKE_BUILD_TYPE MATCHES Release)
    SET(COMPILER_FLAGS_BASIC "${COMPILER_FLAGS_BASIC} /O2")
  ELSE()
    SET(COMPILER_FLAGS_BASIC "${COMPILER_FLAGS_BASIC} /Od")
  ENDIF()

  # Disable exceptions if necessary.
  IF(HOU_CFG_DISABLE_EXCEPTIONS)
    ADD_DEFINITIONS(-D_HAS_EXCEPTIONS=0)
  ELSE()
    ADD_DEFINITIONS(-D_HAS_EXCEPTIONS=1)
  ENDIF()
  SET(COMPILER_FLAGS_BASIC "${COMPILER_FLAGS_BASIC} /DEHsc")

  SET(COMPILER_FLAGS_COMMON "${COMPILER_FLAGS_COMMON} /std:c++14")

  # Warnings.
  SET(COMPILER_FLAGS_COMMON "${COMPILER_FLAGS_COMMON} /W3")

  # This flags are used to disable compiler warnings about using or inheriting
  # from standard library classes. This is not an issue when the Houzi Game
  # Library and the executable are compiled on the same compiler.
  SET(COMPILER_FLAGS_COMMON "${COMPILER_FLAGS_COMMON} /wd4251")
  SET(COMPILER_FLAGS_COMMON "${COMPILER_FLAGS_COMMON} /wd4275")

  SET(COMPILER_FLAGS_COMMON "${COMPILER_FLAGS_COMMON} /wd4996")
  SET(COMPILER_FLAGS_COMMON "${COMPILER_FLAGS_COMMON} /wd4910")

  SET(COMPILER_FLAGS_TESTS "${COMPILER_FLAGS_TESTS} /wd4244")

ENDIF()

# Library and test compiler flags.
# Advanced warnings are disabled in the test compiler flags to silence warnings
# coming from gtest.
SET(LIB_HOU_FLAGS "${COMPILER_FLAGS_BASIC} ${COMPILER_FLAGS_COMMON} ${COMPILER_FLAGS_LIB}")
SET(EXE_HOU_TEST_FLAGS "${COMPILER_FLAGS_BASIC} ${COMPILER_FLAGS_COMMON} ${COMPILER_FLAGS_TESTS}")
MESSAGE(STATUS "Library compiler flags: ${LIB_HOU_FLAGS}")
MESSAGE(STATUS "Test compiler flags: ${EXE_HOU_TEST_FLAGS}")

# Output directories
SET(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
SET(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
SET(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
MESSAGE(STATUS "Archive output directory: ${CMAKE_ARCHIVE_OUTPUT_DIRECTORY}")
MESSAGE(STATUS "Library output directory: ${CMAKE_LIBRARY_OUTPUT_DIRECTORY}")
MESSAGE(STATUS "Runtime output directory: ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}")

MESSAGE(STATUS "")

# Configure external libraries.
SET(EXT_LIBS_DIR ${PROJECT_SOURCE_DIR}/external-libs)
ADD_SUBDIRECTORY(${EXT_LIBS_DIR})

# Configure targets
SET(HOU_SOURCE_DIR ${PROJECT_SOURCE_DIR}/source)
ADD_SUBDIRECTORY(${HOU_SOURCE_DIR})

MESSAGE(STATUS "")
