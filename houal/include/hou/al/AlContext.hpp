// Houzi Game Engine
// Copyright (c) 2018 Davide Corradi
// Licensed under the MIT license. See license.md for more details.

#ifndef HOU_AL_AL_CONTEXT_HPP
#define HOU_AL_AL_CONTEXT_HPP

#include "hou/al/AlExport.hpp"

#include "hou/al/OpenAl.hpp"

#include "hou/cor/BasicTypes.hpp"
#include "hou/cor/NonCopyable.hpp"



namespace hou
{

namespace al
{

class Device;

class HOU_AL_API Context
  : public NonCopyable
{
public:
  static void setCurrent(Context& context);
  static void unsetCurrent();
  static Context* getCurrent();

public:
  Context(Device& device);
  Context(Context&& other);
  ~Context();

  uint32_t getUid() const;
  uint32_t getDeviceUid() const;

  bool isCurrent() const;

private:
  ALCcontext* mHandle;
  uint32_t mUid;
  uint32_t mDeviceUid;
};

}

}

#endif

