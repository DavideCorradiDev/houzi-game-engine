// Houzi Game Engine
// Copyright (c) 2018 Davide Corradi
// Licensed under the MIT license.

#ifndef HOU_AUD_AUDIO_CONTEXT_HPP
#define HOU_AUD_AUDIO_CONTEXT_HPP

#include "hou/cor/non_copyable.hpp"

#include "hou/aud/aud_export.hpp"

#include "hou/al/al_context.hpp"
#include "hou/al/al_device.hpp"

#include <string>
#include <vector>



namespace hou
{

/** Represents the global state of the audio device.
 *
 *  At least one audio_context must exist when creating audio_buffer,
 * audio_source, and streaming_audio_source objects, and when using listener
 * functions. An audio_context can be shared among multiple threads. The audio
 * drivers may limit the number of AudioContexts that can be created at one
 * time. For most applications, it is sufficient to create a single
 * audio_context at the start of the application and destroy it at shutdown. If
 * an audio_context is destroyed while it is current, there will be no current
 *  audio_context until another audio_context is created or set as current.
 */
class HOU_AUD_API audio_context : public non_copyable
{
public:
  /** Sets this as the current context.
   *
   * \param ctx the context to be bound.
   */
  static void set_current(audio_context& ctx);

  /** Unsets the current audio_context.
   */
  static void unset_current();

  /** Gets a list of the names of the available audio devices.
   *
   *  \return a list of the names of the available audio devices.
   */
  static std::vector<std::string> get_device_names();

public:
  /** Creates an audio_context and sets it as the current audio_context.
   */
  audio_context();

  /** Creates an audio_context with the given device.
   *
   *  a list of available devices may be obtained by calling get_device_names.
   *
   *  \param dev_name the name of the device.
   */
  audio_context(const std::string& dev_name);

  /** Move constructor.
   */
  audio_context(audio_context&& other) noexcept;

  /** Checks if this is the current context.
   *
   *  \return true if this is the current context.
   */
  bool is_current() const;

private:
  al::device m_al_device;
  al::context m_al_context;
};

}  // namespace hou

#endif
