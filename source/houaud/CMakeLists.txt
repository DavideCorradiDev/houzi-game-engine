CMAKE_MINIMUM_REQUIRED(VERSION 3.3)
MESSAGE(STATUS "--- Configuring target ${LIB_HOUAUD} ---")

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
  src/hou/aud/aud_exceptions.cpp
  src/hou/aud/aud_module.cpp
  src/hou/aud/audio_buffer.cpp
  src/hou/aud/audio_buffer_format.cpp
  src/hou/aud/audio_context.cpp
  src/hou/aud/audio_source.cpp
  src/hou/aud/audio_source_state.cpp
  src/hou/aud/audio_stream.cpp
  src/hou/aud/audio_stream_in.cpp
  src/hou/aud/listener.cpp
  src/hou/aud/memory_audio_source.cpp
  src/hou/aud/ogg_file_in.cpp
  src/hou/aud/sound_distance_model.cpp
  src/hou/aud/sound_model.cpp
  src/hou/aud/streaming_audio_source.cpp
  src/hou/aud/wav_file_in.cpp
)

# Linked libraries.
SET(LIB_HOUAUD_LIBS
  ${LIB_VORBISFILE}
  ${LIB_VORBISENC}
  ${LIB_VORBIS}
  ${LIB_OGG}
)
IF(NOT HOU_CFG_BUILD_STATIC_LIBS)
  SET(LIB_HOUAUD_LIBS
    ${LIB_HOUAUD_LIBS}
    ${LIB_HOUAL}
    ${LIB_HOUSYS}
    ${LIB_HOUMTH}
    ${LIB_HOUCOR}
  )
ENDIF()
MESSAGE(STATUS "Linked libs: ${LIB_HOUAUD_LIBS}")

# Add targets.
IF(HOU_CFG_BUILD_STATIC_LIBS)
  ADD_LIBRARY(${LIB_HOUAUD} STATIC ${LIB_HOUAUD_SRC})
ELSE()
  ADD_LIBRARY(${LIB_HOUAUD} SHARED ${LIB_HOUAUD_SRC})
ENDIF()
SET_TARGET_PROPERTIES(${LIB_HOUAUD} PROPERTIES
  COMPILE_FLAGS ${LIB_HOU_FLAGS}
  LINKER_LANGUAGE CXX
)
TARGET_LINK_LIBRARIES(${LIB_HOUAUD} ${LIB_HOUAUD_LIBS})

MESSAGE(STATUS "")

IF(HOU_CFG_BUILD_TESTS)
  ADD_SUBDIRECTORY(${CMAKE_CURRENT_SOURCE_DIR}/test)
ENDIF()
