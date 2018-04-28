// Houzi Game Engine
// Copyright (c) 2018 Davide Corradi
// Licensed under the MIT license.

#include "hou/sys/Keyboard.hpp"



namespace hou
{

namespace Keyboard
{

ModifierKeys getModifierKeysState()
{
  ModifierKeys modifierKeys = ModifierKeys::None;
  if(isKeyPressed(ScanCode::LAlt)
    || isKeyPressed(ScanCode::RAlt))
  {
    modifierKeys |= ModifierKeys::Alt;
  }
  if(isKeyPressed(ScanCode::LCtrl)
    || isKeyPressed(ScanCode::RCtrl))
  {
    modifierKeys |= ModifierKeys::Ctrl;
  }
  if(isKeyPressed(ScanCode::LShift)
    || isKeyPressed(ScanCode::RShift))
  {
    modifierKeys |= ModifierKeys::Shift;
  }
  if(isKeyPressed(ScanCode::LSystem)
    || isKeyPressed(ScanCode::RSystem))
  {
    modifierKeys |= ModifierKeys::System;
  }
  return modifierKeys;
}

}

}

