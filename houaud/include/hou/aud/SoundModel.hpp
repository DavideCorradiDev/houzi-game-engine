// Houzi Game Engine
// Copyright (c) 2018 Davide Corradi
// Licensed under the MIT license.

#ifndef HOU_AUD_SOUND_MODEL_HPP
#define HOU_AUD_SOUND_MODEL_HPP

#include "hou/aud/AudExport.hpp"

#include "hou/aud/SoundDistanceModel.hpp"



namespace hou
{

namespace SoundModel
{

HOU_AUD_API SoundDistanceModel getDistanceModel();
HOU_AUD_API void setDistanceModel(SoundDistanceModel model);

HOU_AUD_API float getDopplerFactor();
HOU_AUD_API void setDopplerFactor(float dopplerFactor);

HOU_AUD_API float getSpeedOfSound();
HOU_AUD_API void setSpeedOfSound(float speedOfSound);

}  // namespace SoundModel

}  // namespace hou

#endif
