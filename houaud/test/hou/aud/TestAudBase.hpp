// Houzi Game Engine
// Copyright (c) 2018 Davide Corradi
// Licensed under the MIT license. See license.md for more details.

#ifndef TEST_HOU_AUD_TEST_AUD_BASE_HPP
#define TEST_HOU_AUD_TEST_AUD_BASE_HPP

#include <gtest/gtest.h>

#include "hou/aud/AudioContext.hpp"

#include <memory>



class TestAudBase
  : public ::testing::Test
{
public:
  static void SetUpTestCase();
  static void TearDownTestCase();

public:
  TestAudBase();
  virtual ~TestAudBase() = 0;

public:
  static std::unique_ptr<hou::AudioContext> sContext;
};

#endif

