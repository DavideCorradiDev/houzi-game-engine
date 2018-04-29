// Houzi Game Engine
// Copyright (c) 2018 Davide Corradi
// Licensed under the MIT license.

#include "hou/aud/TestAudBaseTestSpecificContext.hpp"



TestAudBaseTestSpecificContext::TestAudBaseTestSpecificContext()
  : mContext()
{
  hou::AudioContext::set_current(mContext);
}



TestAudBaseTestSpecificContext::~TestAudBaseTestSpecificContext()
{}
