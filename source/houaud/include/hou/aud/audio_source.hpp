// Houzi Game Engine
// Copyright (c) 2018 Davide Corradi
// Licensed under the MIT license.

#ifndef HOU_AUD_AUDIO_SOURCE_HPP
#define HOU_AUD_AUDIO_SOURCE_HPP

#include "hou/aud/audio_buffer_format.hpp"

#include "hou/aud/aud_config.hpp"

#include "hou/al/al_source_handle.hpp"

#include "hou/cor/checked_variable.hpp"
#include "hou/cor/non_copyable.hpp"
#include "hou/cor/std_chrono.hpp"

#include "hou/mth/matrix.hpp"



namespace hou
{

/**
 * Parent class for audio sources.
 */
class HOU_AUD_API audio_source : public non_copyable
{
public:
  using sample_position = long;

public:
  /**
   * Default constructor.
   */
  audio_source();

  /**
   * Move constructor.
   *
   * \param other the other audio_source.
   */
  audio_source(audio_source&& other) noexcept = default;

  /**
   * Destructor.
   */
  virtual ~audio_source() = 0;

  /**
   * Gets the OpenAL audio source handle.
   *
   * \return the OpenAL audio source handle.
   */
  const al::source_handle& get_handle() const noexcept;

  /**
   * Plays the audio source.
   *
   * If the audio source was already playing, nothing happens.
   * If the audio source was stopped, starts playing from the beginning.
   * If the audio source was paused, starts playing from the current offset.
   *
   * If the audio source is looping, playing will not stop by itself.
   * Otherwise, the audio source state will change to stopped as soon as the
   * end is reached.
   */
  void play();

  /**
   * Pause the audio source.
   *
   * If the audio source was paused or stopped, nothing happens.
   * If the audio source was playing, pauses playing without modifying the
   * current offset.
   */
  void pause();

  /**
   * Stops the audio source.
   *
   * If the audio source was stopped, nothing happens.
   * If the audio source was paused, sets the offset to the beginning.
   * If the audio source was playing, stops playing and sets the offset to the
   * beginning.
   */
  void stop();

  /**
   * Stops and replays the audio source.
   */
  void replay();

  /**
   * Gets the state of the audio source.
   *
   * \return the state of the audio source.
   */
  virtual bool is_playing() const = 0;

  /**
   * Checks if the audio source is valid, that is if it references audio data.
   *
   * An invalid audio source will not play any sound and will return default
   * property values.
   *
   * \return true if the audio source references audio data.
   */
  virtual bool is_valid() const = 0;

  /**
   * Gets the audio format of the audio source.
   *
   * \return the audio format.
   */
  audio_buffer_format get_format() const;

  /**
   * Gets the number of channels of the audio source, based on its audio
   * format.
   *
   * \return 1 if the audio format is mono, 2 if the audio format is stereo.
   */
  uint get_channel_count() const;

  /**
   * Gets the number of bytes per sample of the audio stream, based on its
   * audio format.
   *
   * The number returned is the number of bytes per sample for a single
   * channel. \return 1 for 8-bit audio formats, 2 for 16-bit audio formats.
   */
  uint get_bytes_per_sample() const;

  /**
   * Gets the number of samples per second.
   *
   * \return the sample rate in samples per second.
   */
  uint get_sample_rate() const;

  /**
   * Sets the time position of the audio source.
   *
   * \param nsPos the position in nanoseconds.
   */
  void set_time_pos(std::chrono::nanoseconds nsPos);

  /**
   * Sets the time position of the audio source.
   *
   * \tparam TimeDuration the time duration type of the position.
   *
   * \param pos the position.
   */
  template <typename TimeDuration>
  void set_time_pos(TimeDuration pos);

  /**
   * Gets the time position of the audio source in nanoseconds.
   *
   * \return the position of the audio source in nanoseconds.
   */
  std::chrono::nanoseconds get_time_pos() const;

  /**
   * Gets the duration of the audio source in nanoseconds.
   *
   * \return the duration of the audio source in nanoseconds.
   */
  std::chrono::nanoseconds get_duration() const;

  /**
   * Sets the sample position of the audio source.
   *
   * \param pos the position.
   */
  void set_sample_pos(sample_position pos);

  /**
   * Gets the sample position of the audio source.
   *
   * \return the sample position.
   */
  sample_position get_sample_pos() const;

  /**
   * Gets the number of samples in the audio source.
   *
   * \return the number of samples.
   */
  uint get_sample_count() const;

  /**
   * Sets whether the audio source is looping or not.
   *
   * \param looping true to set the audio source to looping, false otherwise.
   */
  void set_looping(bool looping);

  /**
   * Checks if the audio source is looping.
   *
   * \return true if the audio source is looping.
   */
  virtual bool is_looping() const = 0;

  /**
   * Sets the audio source pitch.
   *
   * Throws if the provided value is null or negative.
   *
   * \param value the pitch.
   */
  void set_pitch(non_negative<float> value);

  /**
   * Gets the audio source pitch.
   *
   * \return the pitch.
   */
  non_negative<float> get_pitch() const;

  /**
   * Sets the audio source gain.
   *
   * Throws if the provided value is null or negative.
   *
   * \param value the gain.
   */
  void set_gain(non_negative<float> value);

  /**
   * Gets the audio source gain.
   *
   * \return the gain.
   */
  non_negative<float> get_gain() const;

  /**
   * Sets the audio source maximum gain.
   *
   * Throws if the provided value is null or negative.
   *
   * \param value the maximum gain.
   */
  void set_max_gain(non_negative<float> value);

  /**
   * Gets the audio source maximum gain.
   *
   * \return the maximum gain.
   */
  non_negative<float> get_max_gain() const;

  /**
   * Sets the audio source minimum gain.
   *
   * Throws if the provided value is null or negative.
   *
   * \param value the minimum gain.
   */
  void set_min_gain(non_negative<float> value);

  /**
   * Gets the audio source minimum gain.
   *
   * \return the minimum gain.
   */
  non_negative<float> get_min_gain() const;

  /**
   * Sets the audio source maximum distance.
   *
   * Throws if the provided value is null or negative.
   *
   * \param value the maximum distance.
   */
  void set_max_distance(non_negative<float> value);

  /**
   * Gets the audio source maximum distance.
   *
   * \return the maximum distance.
   */
  non_negative<float> get_max_distance() const;

  /**
   * Sets the audio source rolloff factor.
   *
   * Throws if the provided value is null or negative.
   *
   * \param value the rolloff factor.
   */
  void set_rolloff_factor(non_negative<float> value);

  /**
   * Gets the audio source rolloff factor.
   *
   * \return the rolloff factor.
   */
  non_negative<float> get_rolloff_factor() const;

  /**
   * Sets the audio source reference distance.
   *
   * Throws if the provided value is null or negative.
   *
   * \param value the reference distance.
   */
  void set_reference_distance(non_negative<float> value);

  /**
   * Gets the audio source reference distance.
   *
   * \return the reference distance.
   */
  non_negative<float> get_reference_distance() const;

  /**
   * Sets if the audio source is relative or not.
   *
   * \param value true if the audio source is relative, false otherwise.
   */
  void set_relative(bool value);

  /**
   * Gets if the audio source is relative or not.
   *
   * \return true if the audio source is relative.
   */
  bool is_relative() const;

  /**
   * Sets the audio source cone outer gain.
   *
   * Throws if the provided value is null or negative.
   *
   * \param value the cone outer gain.
   */
  void set_cone_outer_gain(non_negative<float> value);

  /**
   * Gets the audio source cone outer gain.
   *
   * \return the cone outer gain.
   */
  non_negative<float> get_cone_outer_gain() const;

  /**
   * Sets the audio source cone inner angle.
   *
   * Throws if the provided value is not included between 0 and 2 * pi.
   *
   * \param value the cone inner angle.
   */
  void set_cone_inner_angle(float value);

  /**
   * Gets the audio source cone inner angle.
   *
   * \return the cone inner angle.
   */
  float get_cone_inner_angle() const;

  /**
   * Sets the audio source cone outer angle.
   *
   * Throws if the provided value is not included between 0 and 2 * pi.
   *
   * \param value the cone outer angle.
   */
  void set_cone_outer_angle(float value);

  /**
   * Gets the audio source cone outer angle.
   *
   * \return the cone outer angle.
   */
  float get_cone_outer_angle() const;

  /**
   * Sets the audio source position.
   *
   * \param pos the position.
   */
  void set_position(const vec3f& pos);

  /**
   * Gets the audio source position.
   *
   * \return the position.
   */
  vec3f get_position() const;

  /**
   * Sets the audio source velocity.
   *
   * \param vel the velocity.
   */
  void set_velocity(const vec3f& vel);

  /**
   * Gets the audio source vleocity.
   *
   * \return the velocity.
   */
  vec3f get_velocity() const;

  /**
   * Sets the audio source direction.
   *
   * \param dir the direction.
   */
  void set_direction(const vec3f& dir);

  /**
   * Gets the audio source direction.
   *
   * \return the direction.
   */
  vec3f get_direction() const;

protected:
  virtual void on_set_looping(bool looping) = 0;

  /**
   * Sets the sample position.
   *
   * The base class implementation simply sets the audio source offset.
   *
   * \param pos the sample position.
   */
  virtual void on_set_sample_pos(sample_position pos) = 0;

  /**
   * Gets the sample position.
   *
   * The base class implementation simply gets the audio source offset.
   *
   * \return the sample position.
   */
  virtual sample_position on_get_sample_pos() const = 0;

  /**
   * Called when play() or replay() are called.
   *
   * This function does nothing by default, but may contain special behaviour.
   */
  virtual void on_play() = 0;

  /**
   * Called when pause(), stop() or replay() are called.
   *
   * This function does nothing by default, but may contain special behaviour.
   */
  virtual void on_pause() = 0;

private:
  virtual audio_buffer_format get_format_internal() const = 0;
  virtual uint get_channel_count_internal() const = 0;
  virtual uint get_bytes_per_sample_internal() const = 0;
  virtual uint get_sample_rate_internal() const = 0;
  virtual uint get_sample_count_internal() const = 0;

private:
  al::source_handle m_handle;
  sample_position m_requested_sample_pos;
};

}  // namespace hou



#include "hou/aud/audio_source.inl"

#endif
