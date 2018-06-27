CMAKE_MINIMUM_REQUIRED(VERSION 3.3)
MESSAGE(STATUS "--- Configuring target ${LIB_FREETYPE} ---")

# Definitions
# Defining this is necessary, otherwise internal headers will not be included
ADD_DEFINITIONS(-DFT2_BUILD_LIBRARY)

# Include directories
INCLUDE_DIRECTORIES(${LIB_FREETYPE_INCLUDE_DIR})

# Source files
SET(LIB_FREETYPE_SRC
  # Base components
  src/base/ftsystem.c
  src/base/ftinit.c
  src/base/ftdebug.c
  src/base/ftbase.c
  src/base/ftbbox.c
  src/base/ftglyph.c
  src/base/ftbdf.c
  src/base/ftbitmap.c
  src/base/ftcid.c
  src/base/ftfntfmt.c
  src/base/ftfstype.c
  src/base/ftgasp.c
  src/base/ftgxval.c
  src/base/ftlcdfil.c
  src/base/ftmm.c
  src/base/ftotval.c
  src/base/ftpatent.c
  src/base/ftpfr.c
  src/base/ftstroke.c
  src/base/ftsynth.c
  src/base/fttype1.c
  src/base/ftwinfnt.c
  # Font drivers
  src/bdf/bdf.c
  src/cff/cff.c
  src/cid/type1cid.c
  src/pcf/pcf.c
  src/pfr/pfr.c
  src/sfnt/sfnt.c
  src/truetype/truetype.c
  src/type1/type1.c
  src/type42/type42.c
  src/winfonts/winfnt.c
  # Rasterizers
  src/raster/raster.c
  src/smooth/smooth.c
  # Auxiliary modules
  src/autofit/autofit.c
  # src/cache/ftcache.c
  src/gzip/ftgzip.c
  src/lzw/ftlzw.c
  # src/bzip2/ftbzip2.c
  # src/gxvalid/gxvalid.c
  # src/otvalid/otvalid.c
  src/psaux/psaux.c
  src/pshinter/pshinter.c
  src/psnames/psnames.c
)

# Compile flags
SET(LIB_FREETYPE_FLAGS "${COMPILER_FLAGS_BASIC}")
IF(MINGW OR GCC)
  SET(LIB_FREETYPE_FLAGS "${LIB_FREETYPE_FLAGS} -w")
ELSEIF(MSVC)
  SET(LIB_FREETYPE_FLAGS "${LIB_FREETYPE_FLAGS} /wd4244 /wd4018 /wd4996 /wd4267 /wd4312")
ENDIF()

IF(UNIX)
  SET(LIB_FREETYPE_FLAGS "${LIB_FREETYPE_FLAGS} -fPIC")
ENDIF()

# Add targets
ADD_LIBRARY(${LIB_FREETYPE} STATIC ${LIB_FREETYPE_SRC})
SET_TARGET_PROPERTIES(${LIB_FREETYPE} PROPERTIES
  COMPILE_FLAGS ${LIB_FREETYPE_FLAGS}
)

MESSAGE(STATUS "")
