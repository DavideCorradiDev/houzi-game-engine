// Houzi Game Engine
// Copyright (c) 2018 Davide Corradi
// Licensed under the MIT license. See license.md for more details.

#ifndef HOU_AUD_AUDIO_SOURCE_BASE_HPP
#define HOU_AUD_AUDIO_SOURCE_BASE_HPP

#include "hou/aud/AudExport.hpp"

#include "hou/aud/AudioFormat.hpp"
#include "hou/aud/AudioSourceState.hpp"

#include "hou/al/AlSource.hpp"

#include "hou/cor/NonCopyable.hpp"
#include "hou/cor/StdChrono.hpp"

#include "hou/mth/Matrix.hpp"



namespace hou
{

/** Parent class for audio sources.
 */
class HOU_AUD_API AudioSourceBase
  : public NonCopyable
{
public:
  /** Default constructor.
   */
  AudioSourceBase();

  /** Move constructor.
   *
   *  \param other the other AudioSourceBase.
   */
  AudioSourceBase(AudioSourceBase&& other);

  /** Destructor.
   */
  virtual ~AudioSourceBase() = 0;

  /** Plays the audio source.
   *
   *  If the audio source was already playing, nothing happens.
   *  If the audio source was stopped, starts playing from the beginning.
   *  If the audio source was paused, starts playing from the current offset.
   *
   *  If the audio source is looping, playing will not stop by itself.
   *  Otherwise, the audio source state will change to Stopped as soon as the
   *  end is reached.
   */
  void play();

  /** Pause the audio source.
   *
   *  If the audio source was paused or stopped, nothing happens.
   *  If the audio source was playing, pauses playing without modifying the
   *  current offset.
   */
  void pause();

  /** Stops the audio source.
   *
   *  If the audio source was stopped, nothing happens.
   *  If the audio source was paused, sets the offset to the beginning.
   *  If the audio source was playing, stops playing and sets the offset to the
   *  beginning.
   */
  void stop();

  /** Stops and replays the audio source.
   */
  void replay();

  /** Gets the state of the audio source.
   *
   *  \return the state of the audio source.
   */
  AudioSourceState getState() const;

  /** Gets the audio format of the audio source.
   *
   *  \return the audio format.
   */
  virtual AudioFormat getAudioFormat() const = 0;

  /** Gets the number of channels of the audio source, based on its audio format.
   *
   *  \return 1 if the audio format is mono, 2 if the audio format is stereo.
   */
  virtual uint getChannelCount() const = 0;

  /** Gets the number of bytes per sample of the audio stream, based on its audio format.
   *
   *  The number returned is the number of bytes per sample for a single channel.
   *  \return 1 for 8-bit audio formats, 2 for 16-bit audio formats.
   */
  virtual uint getBytesPerSample() const = 0;

  /** Gets the number of samples per second.
   *
   *  \return the sample rate in samples per second.
   */
  virtual uint getSampleRate() const = 0;

  /** Sets the time position of the audio source.
   *
   *  \param nsPos the position in nanoseconds.
   */
  void setTimePos(std::chrono::nanoseconds nsPos);

  /** Sets the time position of the audio source.
   *
   *  \tparam TimeDuration the time duration type of the position.
   *  \param pos the position.
   */
  template <typename TimeDuration>
    void setTimePos(TimeDuration pos);

  // void moveTimePos(TimeDuration offset);

  /** Gets the time position of the audio source in nanoseconds.
   *
   *  \return the position of the audio source in nanoseconds.
   */
  std::chrono::nanoseconds getTimePos() const;

  /** Gets the duration of the audio source in nanoseconds.
   *
   *  \return the duration of the audio source in nanoseconds.
   */
  std::chrono::nanoseconds getDuration() const;

  /** Sets the sample position of the audio source.
   *
   *  \param pos the position.
   */
  void setSamplePos(uint pos);

  // void moveSamplePos(uint offset);

  /** Gets the sample position of the audio source.
   *
   *  \return the sample position.
   */
  uint getSamplePos() const;

  /** Gets the number of samples in the audio source.
   *
   *  \return the number of samples.
   */
  virtual uint getSampleCount() const = 0;

  /** Sets whether the audio source is looping or not.
   *
   *  \param looping true to set the audio source to looping, false otherwise.
   */
  virtual void setLooping(bool looping) = 0;

  /** Checks if the audio source is looping.
   *
   *  \return true if the audio source is looping.
   */
  virtual bool isLooping() const = 0;

  /** Sets the audio source pitch.
   *
   *  Throws if the provided value is null or negative.
   *
   *  \param value the pitch.
   */
  void setPitch(float value);

  /** Gets the audio source pitch.
   *
   *  \return the pitch.
   */
  float getPitch() const;

  /** Sets the audio source gain.
   *
   *  Throws if the provided value is null or negative.
   *
   *  \param value the gain.
   */
  void setGain(float value);

  /** Gets the audio source gain.
   *
   *  \return the gain.
   */
  float getGain() const;

  /** Sets the audio source maximum gain.
   *
   *  Throws if the provided value is null or negative.
   *
   *  \param value the maximum gain.
   */
  void setMaxGain(float value);

  /** Gets the audio source maximum gain.
   *
   *  \return the maximum gain.
   */
  float getMaxGain() const;

  /** Sets the audio source minimum gain.
   *
   *  Throws if the provided value is null or negative.
   *
   *  \param value the minimum gain.
   */
  void setMinGain(float value);

  /** Gets the audio source minimum gain.
   *
   *  \return the minimum gain.
   */
  float getMinGain() const;

  /** Sets the audio source maximum distance.
   *
   *  Throws if the provided value is null or negative.
   *
   *  \param value the maximum distance.
   */
  void setMaxDistance(float value);

  /** Gets the audio source maximum distance.
   *
   *  \return the maximum distance.
   */
  float getMaxDistance() const;

  /** Sets the audio source rolloff factor.
   *
   *  Throws if the provided value is null or negative.
   *
   *  \param value the rolloff factor.
   */
  void setRolloffFactor(float value);

  /** Gets the audio source rolloff factor.
   *
   *  \return the rolloff factor.
   */
  float getRolloffFactor() const;

  /** Sets the audio source reference distance.
   *
   *  Throws if the provided value is null or negative.
   *
   *  \param value the reference distance.
   */
  void setReferenceDistance(float value);

  /** Gets the audio source reference distance.
   *
   *  \return the reference distance.
   */
  float getReferenceDistance() const;

  /** Sets if the audio source is relative or not.
   *
   *  \param value true if the audio source is relative, false otherwise.
   */
  void setRelative(bool value);

  /** Gets if the audio source is relative or not.
   *
   *  \return true if the audio source is relative.
   */
  bool isRelative() const;

  /** Sets the audio source cone outer gain.
   *
   *  Throws if the provided value is null or negative.
   *
   *  \param value the cone outer gain.
   */
  void setConeOuterGain(float value);

  /** Gets the audio source cone outer gain.
   *
   *  \return the cone outer gain.
   */
  float getConeOuterGain() const;

  /** Sets the audio source cone inner angle.
   *
   *  Throws if the provided value is not included between 0 and 2 * pi.
   *
   *  \param value the cone inner angle.
   */
  void setConeInnerAngle(float value);

  /** Gets the audio source cone inner angle.
   *
   *  \return the cone inner angle.
   */
  float getConeInnerAngle() const;

  /** Sets the audio source cone outer angle.
   *
   *  Throws if the provided value is not included between 0 and 2 * pi.
   *
   *  \param value the cone outer angle.
   */
  void setConeOuterAngle(float value);

  /** Gets the audio source cone outer angle.
   *
   *  \return the cone outer angle.
   */
  float getConeOuterAngle() const;

  /** Sets the audio source position.
   *
   *  \param pos the position.
   */
  void setPosition(const Vec3f& pos);

  /** Gets the audio source position.
   *
   *  \return the position.
   */
  Vec3f getPosition() const;

  /** Sets the audio source velocity.
   *
   *  \param vel the velocity.
   */
  void setVelocity(const Vec3f& vel);

  /** Gets the audio source vleocity.
   *
   *  \return the velocity.
   */
  Vec3f getVelocity() const;

  /** Sets the audio source direction.
   *
   *  \param dir the direction.
   */
  void setDirection(const Vec3f& dir);

  /** Gets the audio source direction.
   *
   *  \return the direction.
   */
  Vec3f getDirection() const;

protected:
  /** Sets the sample position.
   *
   *  The base class implementation simply sets the audio source offset.
   *
   *  \param pos the sample position.
   */
  virtual void onSetSamplePos(uint pos) = 0;

  /** Gets the sample position.
   *
   *  The base class implementation simply gets the audio source offset.
   *
   *  \return the sample position.
   */
  virtual uint onGetSamplePos() const = 0;

protected:
  /** The OpenAL audio source.
   */
  al::Source mAlSource;

private:
  uint mRequestedSamplePos;
};

}



#include "hou/aud/AudioSourceBase.inl"

#endif

