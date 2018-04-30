// Houzi Game Engine
// Copyright (c) 2018 Davide Corradi
// Licensed under the MIT license.

#ifndef HOU_SYS_TEXT_FILE_IN_HPP
#define HOU_SYS_TEXT_FILE_IN_HPP

#include "hou/sys/sys_export.hpp"
#include "hou/sys/text_stream_in.hpp"

#include "hou/cor/non_copyable.hpp"

#include "hou/sys/file.hpp"



namespace hou
{

/** Input text file ph_stream.
 */
class HOU_SYS_API text_file_in
  : public non_copyable
  , public text_stream_in
{
public:
  /** Path constructor.
   *
   * Throws if the provided path is not valid.
   *
   * \param path the path to the file to be opened.
   */
  explicit text_file_in(const std::string& path);

  /** Move constructor.
   *
   * \param other the other object.
   */
  text_file_in(text_file_in&& other);

  /** Destructor.
   */
  virtual ~text_file_in();

  // stream overrides.
  bool eof() const final;
  bool error() const final;
  size_t get_byte_count() const final;

  // stream_in overrides.
  size_t get_read_byte_count() const final;
  size_t get_read_element_count() const final;

  // text_stream overrides.
  text_position get_text_pos() const final;
  text_stream& set_text_pos(text_position pos) final;

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
