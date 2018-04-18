CMAKE_MINIMUM_REQUIRED(VERSION 3.3)
MESSAGE(STATUS "--- Configuring target ${LIB_HOUAUD} ---")



# Output dir
SET(LIB_HOUAUD_OUTPUT_DIR ${CMAKE_BINARY_DIR})
MESSAGE(STATUS "Output dir: ${LIB_HOUAUD_OUTPUT_DIR}")



# Definitions.
ADD_DEFINITIONS(-DHOU_AUD_EXPORTS)
GET_PROPERTY(LIB_HOUAUD_DEFINITIONS
  DIRECTORY ${CURRENT_SOURCE_DIR}
  PROPERTY COMPILE_DEFINITIONS
)
MESSAGE(STATUS "Definitions: ${LIB_HOUAUD_DEFINITIONS}")



# Include directories.
INCLUDE_DIRECTORIES(
  ${LIB_OPENAL_INCLUDE_DIR}
  ${LIB_OGG_INCLUDE_DIR}
  ${LIB_VORBIS_INCLUDE_DIR}
  ${LIB_HOUCOR_INCLUDE_DIR}
  ${LIB_HOUMTH_INCLUDE_DIR}
  ${LIB_HOUSYS_INCLUDE_DIR}
  ${LIB_HOUAL_INCLUDE_DIR}
  ${LIB_HOUAUD_INCLUDE_DIR}
)



# Source files.
SET(LIB_HOUAUD_SRC
  src/hou/aud/AudError.cpp
  src/hou/aud/AudioBuffer.cpp
  src/hou/aud/AudioBufferFormat.cpp
  src/hou/aud/AudioContext.cpp
  src/hou/aud/AudioDistanceModel.cpp
  src/hou/aud/AudioSource.cpp
  src/hou/aud/AudioSourceBase.cpp
  src/hou/aud/AudioSourceState.cpp
  src/hou/aud/AudioStream.cpp
  src/hou/aud/AudioStreamIn.cpp
  src/hou/aud/EmptyAudioStreamIn.cpp
  src/hou/aud/Listener.cpp
  src/hou/aud/OggFileIn.cpp
  src/hou/aud/StreamingAudioSource.cpp
  src/hou/aud/WavFileIn.cpp
)



# Linked libraries.
IF(HOU_CFG_SHARED_LIBS)
  SET(LIB_HOUAUD_LIB
    ${LIB_HOUAL}
    ${LIB_OPENAL}
    ${LIB_HOUSYS}
    ${LIB_HOUMTH}
    ${LIB_HOUCOR}
  )
ELSE()
  SET(LIB_HOUAUD_LIB)
ENDIF()
# Ogg and Vorbis are always built as a static lib and linked.
# In this way they will be incorporated into hoaud.
# Ogg and Vorbis are completely encapsulated so there is no need to expose them.
SET(LIB_HOUAUD_LIB
  ${LIB_HOUAUD_LIB}
  ${LIB_VORBISFILE}
  ${LIB_VORBISENC}
  ${LIB_VORBIS}
  ${LIB_OGG}
)
MESSAGE(STATUS "Linked libs: ${LIB_HOUAUD_LIB}")



# Add targets.
IF(HOU_CFG_SHARED_LIBS)
  ADD_LIBRARY(${LIB_HOUAUD} SHARED ${LIB_HOUAUD_SRC})
ELSE()
  ADD_LIBRARY(${LIB_HOUAUD} STATIC ${LIB_HOUAUD_SRC})
ENDIF()
SET_TARGET_PROPERTIES(${LIB_HOUAUD} PROPERTIES
  COMPILE_FLAGS ${LIB_HOU_FLAGS}
  LINKER_LANGUAGE CXX
  ARCHIVE_OUTPUT_DIRECTORY ${LIB_HOUAUD_OUTPUT_DIR}
  LIBRARY_OUTPUT_DIRECTORY ${LIB_HOUAUD_OUTPUT_DIR}
  RUNTIME_OUTPUT_DIRECTORY ${LIB_HOUAUD_OUTPUT_DIR}
)
TARGET_LINK_LIBRARIES(${LIB_HOUAUD} ${LIB_HOUAUD_LIB})



MESSAGE(STATUS "")



IF(HOU_CFG_BUILD_AUD_TESTS)
  ADD_SUBDIRECTORY(${CMAKE_CURRENT_SOURCE_DIR}/test)
ENDIF()

