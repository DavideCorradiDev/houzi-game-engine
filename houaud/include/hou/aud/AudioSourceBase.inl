// Houzi Game Engine
// Copyright (c) 2018 Davide Corradi
// Licensed under the MIT license. See license.md for more details.

namespace hou
{

template <typename TimeDuration>
  void AudioSourceBase::setTimePos(TimeDuration pos)
{
  setTimePos(std::chrono::duration_cast<std::chrono::nanoseconds>(pos));
}

}

