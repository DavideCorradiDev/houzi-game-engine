// Houzi Game Engine
// Copyright (c) 2018 Davide Corradi
// Licensed under the MIT license.

#ifndef HOU_SYS_BINARY_FILE_OUT_HPP
#define HOU_SYS_BINARY_FILE_OUT_HPP

#include "hou/sys/binary_stream_out.hpp"

#include "hou/sys/file.hpp"

#include "hou/sys/sys_export.hpp"

#include "hou/cor/non_copyable.hpp"



namespace hou
{

/** Output binary file stream.
 */
class HOU_SYS_API binary_file_out
  : public non_copyable
  , public binary_stream_out
{
public:
  /** Path constructor.
   *
   * Throws if the provided path is not valid.
   *
   * \param path the path to the file to be opened.
   */
  explicit binary_file_out(const std::string& path);

  /** Move constructor.
   *
   * \param other the other object.
   */
  binary_file_out(binary_file_out&& other) noexcept;

  // stream overrides.
  bool eof() const noexcept final;
  bool error() const noexcept final;
  size_t get_byte_count() const noexcept final;

  // stream_out overrides.
  size_t get_write_byte_count() const noexcept final;
  size_t get_write_element_count() const noexcept final;

  // binary_stream overrides.
  byte_position get_byte_pos() const final;

  /** Sets the current byte position indicator.
   *
   * Throws if pos is negative.
   * The position may be over the end of the file.
   *
   * \param pos the byte position indicator value.
   *
   * \return a reference to this stream.
   */
  binary_stream& set_byte_pos(byte_position pos) final;

  /** Moves the current byte position indicator.
   *
   * Throws if the offset moves the position indicator to a negative position.
   * The position may be over the end of the file.
   *
   * \param offset the byte position indicator offset.
   *
   * \return a reference to this stream.
   */
  binary_stream& move_byte_pos(byte_offset offset) final;

protected:
  // stream_out overrides.
  void on_write(const void* buf, size_t element_size, size_t buf_size) final;

private:
  file m_file;
  size_t m_byte_count;
  size_t m_element_count;
};

}  // namespace hou

#endif
