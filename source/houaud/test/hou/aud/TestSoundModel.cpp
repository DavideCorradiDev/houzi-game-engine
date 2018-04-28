// Houzi Game Engine
// Copyright (c) 2018 Davide Corradi
// Licensed under the MIT license.

#include "hou/Test.hpp"
#include "hou/aud/TestAudBaseTestSpecificContext.hpp"

#include "hou/aud/SoundModel.hpp"

using namespace hou;



namespace
{

class TestSoundModel : public TestAudBaseTestSpecificContext
{};

class TestSoundModelDeathTest : public TestSoundModel
{};

}  // namespace



TEST_F(TestSoundModel, SoundDistanceModel)
{
  EXPECT_EQ(
    SoundDistanceModel::InverseDistanceClamped, SoundModel::getDistanceModel());

  std::vector<SoundDistanceModel> distanceModels{
    SoundDistanceModel::InverseDistance,
    SoundDistanceModel::InverseDistanceClamped,
    SoundDistanceModel::LinearDistance,
    SoundDistanceModel::LinearDistanceClamped,
    SoundDistanceModel::ExponentDistance,
    SoundDistanceModel::ExponentDistanceClamped,
  };

  for(auto dm : distanceModels)
  {
    SoundModel::setDistanceModel(dm);
    EXPECT_EQ(dm, SoundModel::getDistanceModel());
  }
}



TEST_F(TestSoundModel, DopplerFactor)
{
  EXPECT_FLOAT_EQ(1.f, SoundModel::getDopplerFactor());

  std::vector<float> dopplerFactorValues{0.f, 0.5f, 1.f, 3.f, 10.f};

  for(auto df : dopplerFactorValues)
  {
    SoundModel::setDopplerFactor(df);
    EXPECT_FLOAT_EQ(df, SoundModel::getDopplerFactor());
  }
}



TEST_F(TestSoundModel, DopplerFactorErrorNegativeValue)
{
  HOU_EXPECT_PRECONDITION(SoundModel::setDopplerFactor(-1.f));
}



TEST_F(TestSoundModel, SpeedOfSound)
{
  EXPECT_FLOAT_EQ(343.3f, SoundModel::getSpeedOfSound());

  std::vector<float> speedOfSoundValues{0.5f, 1.f, 3.f, 10.f, 343.3f, 700.f};

  for(auto df : speedOfSoundValues)
  {
    SoundModel::setSpeedOfSound(df);
    EXPECT_FLOAT_EQ(df, SoundModel::getSpeedOfSound());
  }
}



TEST_F(TestSoundModel, SpeedOfSoundErrorNegativeOrNullValue)
{
  HOU_EXPECT_PRECONDITION(SoundModel::setSpeedOfSound(0.f));
  HOU_EXPECT_PRECONDITION(SoundModel::setSpeedOfSound(-1.f));
}
