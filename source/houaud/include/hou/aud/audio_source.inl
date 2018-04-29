// Houzi Game Engine
// Copyright (c) 2018 Davide Corradi
// Licensed under the MIT license.

namespace hou
{

template <typename TimeDuration>
  void audio_source::set_time_pos(TimeDuration pos)
{
  set_time_pos(std::chrono::duration_cast<std::chrono::nanoseconds>(pos));
}

}

