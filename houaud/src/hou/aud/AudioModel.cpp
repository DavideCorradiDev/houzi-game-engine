#include "hou/aud/AudioModel.hpp"

#include "hou/al/AlState.hpp"



namespace hou
{

namespace AudioModel
{

AudioDistanceModel getDistanceModel()
{
  return AudioDistanceModel(al::getDistanceModel());
}



void setDistanceModel(AudioDistanceModel model)
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

}  // namespace AudioModel

}  // namespace hou
