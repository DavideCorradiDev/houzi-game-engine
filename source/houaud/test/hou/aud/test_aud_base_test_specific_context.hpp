// Houzi Game Engine
// Copyright (c) 2018 Davide Corradi
// Licensed under the MIT license.

#ifndef TEST_HOU_AUD_TEST_AUD_BASE_TEST_SPECIFIC_CONTEXT_HPP
#define TEST_HOU_AUD_TEST_AUD_BASE_TEST_SPECIFIC_CONTEXT_HPP

#include <gtest/gtest.h>

#include "hou/aud/audio_context.hpp"

#include <memory>



class test_aud_base_test_specific_context : public ::testing::Test
{
public:
  test_aud_base_test_specific_context();
  virtual ~test_aud_base_test_specific_context() = 0;

public:
  hou::audio_context mContext;
};

#endif
