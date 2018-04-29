// Houzi Game Engine
// Copyright (c) 2018 Davide Corradi
// Licensed under the MIT license.

#ifndef TEST_HOU_AUD_TEST_AUD_BASE_HPP
#define TEST_HOU_AUD_TEST_AUD_BASE_HPP

#include <gtest/gtest.h>

#include "hou/aud/audio_context.hpp"

#include <memory>



class test_aud_base : public ::testing::Test
{
public:
  static void SetUpTestCase();
  static void TearDownTestCase();

public:
  test_aud_base();
  virtual ~test_aud_base() = 0;

public:
  static std::unique_ptr<hou::audio_context> sContext;
};

#endif
