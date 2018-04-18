// Houzi Game Engine
// Copyright (c) 2018 Davide Corradi
// Licensed under the MIT license.

#ifndef HOU_AUD_AUDIO_MODEL_HPP
#define HOU_AUD_AUDIO_MODEL_HPP

#include "hou/aud/AudExport.hpp"

#include "hou/aud/AudioDistanceModel.hpp"



namespace hou
{

namespace AudioModel
{

HOU_AUD_API AudioDistanceModel getDistanceModel();
HOU_AUD_API void setDistanceModel(AudioDistanceModel model);

HOU_AUD_API float getDopplerFactor();
HOU_AUD_API void setDopplerFactor(float dopplerFactor);

HOU_AUD_API float getSpeedOfSound();
HOU_AUD_API void setSpeedOfSound(float speedOfSound);

}  // namespace AudioModel

}  // namespace hou

#endif
