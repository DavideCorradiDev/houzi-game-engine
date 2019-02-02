// Houzi Game Engine
// Copyright (c) 2018 Davide Corradi
// Licensed under the MIT license.

#include "hou/aud/test_data.hpp"



const std::string& get_output_dir()
{
  static const std::string dir = u8"source/houaud/test/output/";
  return dir;
}



const std::string& get_data_dir()
{
  static const std::string dir = u8"source/houaud/test/data/";
  return dir;
}



const std::string& get_mono8_wav_filename()
{
  static const std::string filename
    = get_data_dir() + u8"TestWav-mono-8-44100.wav";
  return filename;
}



const std::string& get_mono16_wav_filename()
{
  static const std::string filename
    = get_data_dir() + u8"TestWav-mono-16-44100.wav";
  return filename;
}



const std::string& get_stereo8_wav_filename()
{
  static const std::string filename
    = get_data_dir() + u8"TestWav-stereo-8-44100.wav";
  return filename;
}



const std::string& get_stereo16_wav_filename()
{
  static const std::string filename
    = get_data_dir() + u8"TestWav-stereo-16-44100.wav";
  return filename;
}



const std::string& get_stereo16_ogg_filename()
{
  static const std::string filename
    = get_data_dir() + u8"TestOgg-stereo-16-44100.ogg";
  return filename;
}

