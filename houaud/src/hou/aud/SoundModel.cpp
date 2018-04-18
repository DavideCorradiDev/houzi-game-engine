#include "hou/aud/SoundModel.hpp"

#include "hou/al/AlState.hpp"



namespace hou
{

namespace SoundModel
{

SoundDistanceModel getDistanceModel()
{
  return SoundDistanceModel(al::getDistanceModel());
}



void setDistanceModel(SoundDistanceModel model)
{
  al::setDistanceModel(static_cast<ALenum>(model));
}



float getDopplerFactor()
{
  return static_cast<float>(al::getDopplerFactor());
}



void setDopplerFactor(float dopplerFactor)
{
  al::setDopplerFactor(static_cast<ALfloat>(dopplerFactor));
}



float getSpeedOfSound()
{
  return static_cast<float>(al::getSpeedOfSound());
}



void setSpeedOfSound(float speedOfSound)
{
  al::setSpeedOfSound(static_cast<ALfloat>(speedOfSound));
}

}  // namespace SoundModel

}  // namespace hou
