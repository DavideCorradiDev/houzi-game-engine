// Houzi Game Engine
// Copyright (c) 2018 Davide Corradi
// Licensed under the MIT license. See license.md for more details.

#include "hou/Test.hpp"
#include "hou/al/TestAlBase.hpp"

#include "hou/al/AlBuffer.hpp"

using namespace hou;



namespace
{

class TestAlBuffer : public TestAlBase {};

}



TEST_F(TestAlBuffer, DefaultCreation)
{
  al::Buffer b;

  EXPECT_NE(0u, b.getHandle().getName());
  EXPECT_EQ(0, b.getFrequency());
  // Note: channels and samples are undefined when buffer format is unset.
  EXPECT_EQ(al::BufferFormat::Unset, b.getFormat());
  EXPECT_EQ(0, b.getSize());
}



TEST_F(TestAlBuffer, Creation)
{
  {
    std::vector<float> dataRef1{1.f, 2.f, 3.f};
    al::Buffer b(dataRef1, al::BufferFormat::Stereo16, 144);

    EXPECT_NE(0u, b.getHandle().getName());
    EXPECT_EQ(144, b.getFrequency());
    EXPECT_EQ(al::BufferFormat::Stereo16, b.getFormat());
    EXPECT_EQ(16, b.getBits());
    EXPECT_EQ(2, b.getChannels());
    EXPECT_EQ(static_cast<ALsizei>(dataRef1.size() * sizeof(float)), b.getSize());
  }

  {
    std::vector<double> dataRef2{4.f, 5.f};
    al::Buffer b(dataRef2, al::BufferFormat::Mono16, 200);

    EXPECT_NE(0u, b.getHandle().getName());
    EXPECT_EQ(200, b.getFrequency());
    EXPECT_EQ(al::BufferFormat::Mono16, b.getFormat());
    EXPECT_EQ(16, b.getBits());
    EXPECT_EQ(1, b.getChannels());
    EXPECT_EQ(static_cast<ALsizei>(dataRef2.size() * sizeof(double)), b.getSize());
  }
}



TEST_F(TestAlBuffer, MoveConstructor)
{
  std::vector<float> dataRef{1.f, 2.f, 3.f};
  al::Buffer bDummy(dataRef, al::BufferFormat::Stereo16, 144);
  ALuint refName = bDummy.getHandle().getName();
  al::Buffer b(std::move(bDummy));

  EXPECT_EQ(refName, b.getHandle().getName());
  EXPECT_EQ(144, b.getFrequency());
  EXPECT_EQ(al::BufferFormat::Stereo16, b.getFormat());
  EXPECT_EQ(16, b.getBits());
  EXPECT_EQ(2, b.getChannels());
  EXPECT_EQ(static_cast<ALsizei>(dataRef.size() * sizeof(float)), b.getSize());
}



TEST_F(TestAlBuffer, SetData)
{
  std::vector<float> dataRef1{1.f, 2.f, 3.f};
  al::Buffer b(dataRef1, al::BufferFormat::Stereo16, 144);

  EXPECT_NE(0u, b.getHandle().getName());
  EXPECT_EQ(144, b.getFrequency());
  EXPECT_EQ(al::BufferFormat::Stereo16, b.getFormat());
  EXPECT_EQ(16, b.getBits());
  EXPECT_EQ(2, b.getChannels());
  EXPECT_EQ(static_cast<ALsizei>(dataRef1.size() * sizeof(float)), b.getSize());

  std::vector<double> dataRef2{4.f, 5.f};
  b.setData(dataRef2, al::BufferFormat::Mono16, 200);

  EXPECT_NE(0u, b.getHandle().getName());
  EXPECT_EQ(200, b.getFrequency());
  EXPECT_EQ(al::BufferFormat::Mono16, b.getFormat());
  EXPECT_EQ(16, b.getBits());
  EXPECT_EQ(1, b.getChannels());
  EXPECT_EQ(static_cast<ALsizei>(dataRef2.size() * sizeof(double)), b.getSize());
}



TEST_F(TestAlBuffer, GetFormatMeasures)
{
  // Note: the implementation might convert the format to a different one.
  // Bits per sample might change from 8 to 16. Samples will be padded and 
  // the size will increase.
  std::vector<uint8_t> data{1, 2, 3, 4};

  {
    al::Buffer b(data, al::BufferFormat::Mono8, 144);
    EXPECT_EQ(1, b.getChannels());
    EXPECT_EQ(b.getBits() == 8 ? al::BufferFormat::Mono8
      : al::BufferFormat::Mono16, b.getFormat());
    EXPECT_EQ(static_cast<ALint>(data.size() * b.getBits() / 8), b.getSize());
  }

  {
    al::Buffer b(data, al::BufferFormat::Mono16, 144);
    EXPECT_EQ(al::BufferFormat::Mono16, b.getFormat());
    EXPECT_EQ(16, b.getBits());
    EXPECT_EQ(1, b.getChannels());
    EXPECT_EQ(static_cast<ALint>(data.size()), b.getSize());
  }

  {
    al::Buffer b(data, al::BufferFormat::Stereo8, 144);
    EXPECT_EQ(2, b.getChannels());
    EXPECT_EQ(b.getBits() == 8 ? al::BufferFormat::Stereo8
      : al::BufferFormat::Stereo16, b.getFormat());
    EXPECT_EQ(static_cast<ALint>(data.size() * b.getBits() / 8), b.getSize());
  }

  {
    al::Buffer b(data, al::BufferFormat::Stereo16, 144);
    EXPECT_EQ(al::BufferFormat::Stereo16, b.getFormat());
    EXPECT_EQ(16, b.getBits());
    EXPECT_EQ(2, b.getChannels());
    EXPECT_EQ(static_cast<ALint>(data.size()), b.getSize());
  }
}

