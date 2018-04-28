// Houzi Game Engine
// Copyright (c) 2018 Davide Corradi
// Licensed under the MIT license.

#ifndef HOU_SYS_TEXT_FILE_OUT_HPP
#define HOU_SYS_TEXT_FILE_OUT_HPP

#include "hou/sys/sys_export.hpp"
#include "hou/sys/text_stream_out.hpp"

#include "hou/cor/non_copyable.hpp"

#include "hou/sys/file.hpp"



namespace hou
{

/** Output text ph_file ph_stream.
 */
class HOU_SYS_API text_file_out
  : public non_copyable
  , public text_stream_out
{
public:
  /** Path constructor.
   *
   *  Throws if the provided path is not valid.
   *
   *  \param path the path to the ph_file to be opened.
   */
  explicit text_file_out(const std::string& path);

  /** Move constructor.
   *
   *  \param other the other object.
   */
  text_file_out(text_file_out&& other);

  /** Destructor.
   */
  virtual ~text_file_out();

  // stream overrides.
  bool eof() const final;
  bool error() const final;
  size_t get_byte_count() const final;

  // stream_out overrides.
  size_t get_write_byte_count() const final;
  size_t get_write_element_count() const final;

  // text_stream overrides.
  text_position get_text_pos() const final;
  text_stream& set_text_pos(text_position pos) final;

protected:
  // stream_out overrides.
  void on_write(const void* buf, size_t elementSize, size_t bufSize) final;

private:
  file m_file;
  size_t m_byte_count;
  size_t m_element_count;
};

}

#endif

