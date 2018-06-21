// Houzi Game Engine
// Copyright (c) 2018 Davide Corradi
// Licensed under the MIT license.

#ifndef HOU_AL_AL_DEVICE_HPP
#define HOU_AL_AL_DEVICE_HPP

#include "hou/al/open_al.hpp"

#include "hou/al/al_config.hpp"

#include "hou/cor/non_copyable.hpp"

#include <string>
#include <vector>



namespace hou
{

namespace al
{

/**
 * Represents an audio device.
 */
class HOU_AL_API device : public non_copyable
{
public:
  /**
   * Underlying implementation type.
   */
  using impl_type = ALCdevice;

  /**
   * Unique identifier type.
   */
  using uid_type = uint32_t;

public:
  /**
   * Gets the names of the available devices.
   *
   * \return the  names of the available devices.
   */
  static std::vector<std::string> get_device_names();

public:
  /**
   * Creates a reference to the default device.
   *
   * \throws hou::al::device_open_error if the device could not be opened.
   */
  device();

  /**
   * Creates a reference to the required device.
   *
   * \param dev_name the device name.
   *
   * \throws hou::al::device_open_error if the device could not be opened.
   */
  device(const std::string& dev_name);

  /**
   * Move constructor.
   *
   * \param other the other device.
   */
  device(device&& other) noexcept;

  /**
   * Destructor.
   */
  ~device();

  /**
   * Gets a reference to the underlying implementation.
   *
   * \return a reference to the underlying implementation.
   */
  const impl_type* get_impl() const noexcept;

  /**
   * Gets a reference to the underlying implementation.
   *
   * \return a reference to the underlying implementation.
   */
  impl_type* get_impl() noexcept;

  /**
   * Gets the context unique identifier.
   *
   * \return the context unique identifier.
   */
  uid_type get_uid() const noexcept;

private:
  ALCdevice* m_device;
  uint32_t m_uid;
};

}  // namespace al

}  // namespace hou

#endif
