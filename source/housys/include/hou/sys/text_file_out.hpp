// Houzi Game Engine
// Copyright (c) 2018 Davide Corradi
// Licensed under the MIT license.

#ifndef HOU_SYS_TEXT_FILE_OUT_HPP
#define HOU_SYS_TEXT_FILE_OUT_HPP

#include "hou/sys/text_stream_out.hpp"

#include "hou/sys/file.hpp"

#include "hou/sys/sys_export.hpp"

#include "hou/cor/non_copyable.hpp"



namespace hou
{

/** Output text file stream.
 */
class HOU_SYS_API text_file_out
  : public non_copyable
  , public text_stream_out
{
public:
  /** Path constructor.
   *
   * Throws if the provided path is not valid.
   *
   * \param path the path to the file to be opened.
   */
  explicit text_file_out(const std::string& path);

  // stream overrides.
  bool eof() const noexcept final;
  bool error() const noexcept final;
  size_t get_byte_count() const noexcept final;

  // stream_out overrides.
  size_t get_write_byte_count() const noexcept final;
  size_t get_write_element_count() const noexcept final;

  // text_stream overrides.
  text_position get_text_pos() const final;
  text_stream& set_text_pos(text_position pos) final;

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
