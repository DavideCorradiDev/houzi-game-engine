// Houzi Game Engine
// Copyright (c) 2018 Davide Corradi
// Licensed under the MIT license.

#ifndef HOU_AUD_AUDIO_CONTEXT_HPP
#define HOU_AUD_AUDIO_CONTEXT_HPP

#include "hou/aud/AudExport.hpp"
#include "hou/cor/non_copyable.hpp"

#include "hou/al/al_context.hpp"
#include "hou/al/al_device.hpp"

#include <string>
#include <vector>



namespace hou
{

/** Represents the global state of the audio ph_device.
 *
 *  At least one AudioContext must exist when creating AudioBuffer, AudioSource,
 *  and StreamingAudioSource objects, and when using Listener functions.
 *  An AudioContext can be shared among multiple threads.
 *  The audio drivers may limit the number of AudioContexts that can be created
 *  at one time.
 *  For most applications, it is sufficient to create a single AudioContext
 *  at the start of the application and destroy it at shutdown.
 *  If an AudioContext is destroyed while it is current, there will be no current
 *  AudioContext until another AudioContext is created or set as current.
 */
class HOU_AUD_API AudioContext
  : public non_copyable
{
public:
  /** Sets this as the current ph_context.
   */
  static void set_current(AudioContext& ph_context);

  /** Unsets the current AudioContext.
   */
  static void unset_current();

  /** Gets a list of the names of the available audio devices.
   *
   *  \return a list of the names of the available audio devices.
   */
  static std::vector<std::string> get_device_names();

public:
  /** Creates an AudioContext and sets it as the current AudioContext.
   */
  AudioContext();

  /** Creates an AudioContext with the given ph_device.
   *
   *  a list of available devices may be obtained by calling get_device_names.
   *
   *  \param deviceName the name of the ph_device.
   */
  AudioContext(const std::string& deviceName);

  /** Move constructor.
   */
  AudioContext(AudioContext&& other);

  /** Checks if this is the current ph_context.
   *
   *  \return true if this is the current ph_context.
   */
  bool is_current() const;

private:
  al::device mAlDevice;
  al::context mAlContext;
};

}

#endif

