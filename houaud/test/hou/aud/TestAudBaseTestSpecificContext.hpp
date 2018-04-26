// Houzi Game Engine
// Copyright (c) 2018 Davide Corradi
// Licensed under the MIT license.

#ifndef TEST_HOU_AUD_TEST_AUD_BASE_TEST_SPECIFIC_CONTEXT_HPP
#define TEST_HOU_AUD_TEST_AUD_BASE_TEST_SPECIFIC_CONTEXT_HPP

#include <gtest/gtest.h>

#include "hou/aud/AudioContext.hpp"

#include <memory>



class TestAudBaseTestSpecificContext : public ::testing::Test
{
public:
  TestAudBaseTestSpecificContext();
  virtual ~TestAudBaseTestSpecificContext() = 0;

public:
  hou::AudioContext mContext;
};

#endif
