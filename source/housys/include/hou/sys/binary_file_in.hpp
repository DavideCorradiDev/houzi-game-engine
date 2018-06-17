// Houzi Game Engine
// Copyright (c) 2018 Davide Corradi
// Licensed under the MIT license.

#ifndef HOU_SYS_BINARY_FILE_IN_HPP
#define HOU_SYS_BINARY_FILE_IN_HPP

#include "hou/sys/binary_stream_in.hpp"

#include "hou/sys/file.hpp"

#include "hou/sys/sys_config.hpp"

#include "hou/cor/non_copyable.hpp"



namespace hou
{

/**
 * Input binary file stream.
 */
class HOU_SYS_API binary_file_in
  : public non_copyable
  , public binary_stream_in
{
public:
  /**
   * Path constructor.
   *
   * Throws if the provided path is not valid.
   *
   * \param path the path to the file to be opened.
   */
  explicit binary_file_in(const std::string& path);

  // stream overrides.
  bool eof() const noexcept final;
  bool error() const noexcept final;
  size_t get_byte_count() const noexcept final;

  // stream_in overrides.
  size_t get_read_byte_count() const noexcept final;
  size_t get_read_element_count() const noexcept final;

  // binary_stream overrides.
  byte_position get_byte_pos() const final;
  binary_stream& set_byte_pos(byte_position pos) final;
  binary_stream& move_byte_pos(byte_offset offset) final;

protected:
  // stream_in overrides.
  void on_read(void* buf, size_t element_size, size_t buf_size) final;

private:
  file m_file;
  size_t m_byte_count;
  size_t m_element_count;
};

}  // namespace hou

#endif
