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
  static hou::audio_context& get_context();

  static void SetUpTestCase();

public:
  test_aud_base();
};

#endif
