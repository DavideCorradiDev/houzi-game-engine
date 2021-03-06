CMAKE_MINIMUM_REQUIRED(VERSION 3.3)
MESSAGE(STATUS "--- Configuring internal targets ---")



# Compiler flags.
SET(COMPILER_FLAGS_COMMON "${CMAKE_CXX_FLAGS}")
SET(COMPILER_FLAGS_LIB "")
SET(COMPILER_FLAGS_EXE "")

IF(MINGW OR GCC OR CLANG)
  # C++ standard.
  SET(COMPILER_FLAGS_COMMON "${COMPILER_FLAGS_COMMON} -std=c++14")

  # Exceptions in the STL.
  IF(HOU_CFG_DISABLE_EXCEPTIONS)
    SET(COMPILER_FLAGS_COMMON "${COMPILER_FLAGS_COMMON} -fno-exceptions")
  ELSE()
    SET(COMPILER_FLAGS_COMMON "${COMPILER_FLAGS_COMMON} -fexceptions")
  ENDIF()

  IF(MINGW)
    SET(COMPILER_FLAGS_COMMON "${COMPILER_FLAGS_COMMON} -mthreads")
  ENDIF()

  # Position independent code.
  SET(COMPILER_FLAGS_LIB "${COMPILER_FLAGS_LIB} -fPIC")

  # Warnings
  SET(COMPILER_FLAGS_COMMON "${COMPILER_FLAGS_COMMON} -Wall")
  SET(COMPILER_FLAGS_COMMON "${COMPILER_FLAGS_COMMON} -Wextra")
  SET(COMPILER_FLAGS_COMMON "${COMPILER_FLAGS_COMMON} -pedantic")

  # Additional warnings.
  # Activating them in the tests causes some warning coming from googletest.
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
  # C++ standard.
  SET(COMPILER_FLAGS_COMMON "${COMPILER_FLAGS_COMMON} /std:c++14")

  # Exceptions in the STL.
  IF(HOU_CFG_DISABLE_EXCEPTIONS)
    ADD_DEFINITIONS(-D_HAS_EXCEPTIONS=0)
  ELSE()
    ADD_DEFINITIONS(-D_HAS_EXCEPTIONS=1)
  ENDIF()

  # This flags are used to disable compiler warnings about using or inheriting
  # from standard library classes. This is not an issue when the Houzi Game
  # Library and the executable are compiled on the same compiler.
  SET(COMPILER_FLAGS_COMMON "${COMPILER_FLAGS_COMMON} /wd4251")
  SET(COMPILER_FLAGS_COMMON "${COMPILER_FLAGS_COMMON} /wd4275")

  # Disable additional warnings.
  SET(COMPILER_FLAGS_COMMON "${COMPILER_FLAGS_COMMON} /wd4996")
  SET(COMPILER_FLAGS_COMMON "${COMPILER_FLAGS_COMMON} /wd4910")
  SET(COMPILER_FLAGS_EXE "${COMPILER_FLAGS_EXE} /wd4244")

ENDIF()

SET(LIB_HOU_FLAGS "${COMPILER_FLAGS_COMMON} ${COMPILER_FLAGS_LIB}")
SET(EXE_HOU_FLAGS "${COMPILER_FLAGS_COMMON} ${COMPILER_FLAGS_EXE}")
MESSAGE(STATUS "Houzi libraries base compiler flags: ${LIB_HOU_FLAGS}")
MESSAGE(STATUS "Houzi executables base compiler flags: ${EXE_HOU_FLAGS}")

MESSAGE(STATUS "")



# Target configuration.
SET(LIB_HOUTEST_SOURCE_DIR ${HOU_SOURCE_DIR}/houtest)
SET(LIB_HOUTEST_INCLUDE_DIR ${LIB_HOUTEST_SOURCE_DIR}/include)

SET(LIB_HOUCOR houcor)
SET(LIB_HOUCOR_SOURCE_DIR ${HOU_SOURCE_DIR}/houcor)
SET(LIB_HOUCOR_INCLUDE_DIR ${LIB_HOUCOR_SOURCE_DIR}/include)
ADD_SUBDIRECTORY(${LIB_HOUCOR_SOURCE_DIR})

SET(LIB_HOUMTH houmth)
SET(LIB_HOUMTH_SOURCE_DIR ${HOU_SOURCE_DIR}/houmth)
SET(LIB_HOUMTH_INCLUDE_DIR ${LIB_HOUMTH_SOURCE_DIR}/include)
ADD_SUBDIRECTORY(${LIB_HOUMTH_SOURCE_DIR})

SET(LIB_HOUSYS housys)
SET(LIB_HOUSYS_SOURCE_DIR ${HOU_SOURCE_DIR}/housys)
SET(LIB_HOUSYS_INCLUDE_DIR ${LIB_HOUSYS_SOURCE_DIR}/include)
ADD_SUBDIRECTORY(${LIB_HOUSYS_SOURCE_DIR})

SET(LIB_HOUGL hougl)
SET(LIB_HOUGL_SOURCE_DIR ${HOU_SOURCE_DIR}/hougl)
SET(LIB_HOUGL_INCLUDE_DIR ${LIB_HOUGL_SOURCE_DIR}/include)
ADD_SUBDIRECTORY(${LIB_HOUGL_SOURCE_DIR})

SET(LIB_HOUGFX hougfx)
SET(LIB_HOUGFX_SOURCE_DIR ${HOU_SOURCE_DIR}/hougfx)
SET(LIB_HOUGFX_INCLUDE_DIR ${LIB_HOUGFX_SOURCE_DIR}/include)
ADD_SUBDIRECTORY(${LIB_HOUGFX_SOURCE_DIR})

SET(LIB_HOUAL houal)
SET(LIB_HOUAL_SOURCE_DIR ${HOU_SOURCE_DIR}/houal)
SET(LIB_HOUAL_INCLUDE_DIR ${LIB_HOUAL_SOURCE_DIR}/include)
ADD_SUBDIRECTORY(${LIB_HOUAL_SOURCE_DIR})

SET(LIB_HOUAUD houaud)
SET(LIB_HOUAUD_SOURCE_DIR ${HOU_SOURCE_DIR}/houaud)
SET(LIB_HOUAUD_INCLUDE_DIR ${LIB_HOUAUD_SOURCE_DIR}/include)
ADD_SUBDIRECTORY(${LIB_HOUAUD_SOURCE_DIR})

IF(HOU_CFG_BUILD_DEMOS)
  SET(EXE_EXAMPLES_SOURCE_DIR ${HOU_SOURCE_DIR}/demo)
  ADD_SUBDIRECTORY(${EXE_EXAMPLES_SOURCE_DIR})
ENDIF()

MESSAGE(STATUS "")
