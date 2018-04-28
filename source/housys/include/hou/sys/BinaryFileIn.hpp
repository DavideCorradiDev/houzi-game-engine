// Houzi Game Engine
// Copyright (c) 2018 Davide Corradi
// Licensed under the MIT license.

#ifndef HOU_SYS_BINARY_FILE_IN_HPP
#define HOU_SYS_BINARY_FILE_IN_HPP

#include "hou/sys/sys_export.hpp"
#include "hou/sys/binary_stream_in.hpp"

#include "hou/cor/non_copyable.hpp"

#include "hou/sys/file.hpp"



namespace hou
{

/** Input binary ph_file ph_stream.
 */
class HOU_SYS_API binary_file_in
  : public non_copyable
  , public binary_stream_in
{
public:
  /** Path constructor.
   *
   *  Throws if the provided path is not valid.
   *
   *  \param path the path to the ph_file to be opened.
   */
  explicit binary_file_in(const std::string& path);

  /** Move constructor.
   *
   *  \param other the other object.
   */
  binary_file_in(binary_file_in&& other);

  /** Destructor.
   */
  virtual ~binary_file_in();

  // stream overrides.
  bool eof() const final;
  bool error() const final;
  size_t get_byte_count() const final;

  // stream_in overrides.
  size_t get_read_byte_count() const final;
  size_t get_read_element_count() const final;

  // binary_stream overrides.
  byte_position get_byte_pos() const final;

  /** Sets the current byte position indicator.
   *
   *  Throws if pos is negative.
   *  The position may be over the end of the ph_file.
   *
   *  \param pos the byte position indicator value.
   *  \return a reference to this ph_stream.
   */
  binary_stream& set_byte_pos(byte_position pos) final;

  /** Moves the current byte position indicator.
   *
   *  Throws if the offset moves the position indicator to a negative position.
   *  The position may be over the end of the ph_file.
   *
   *  \param offset the byte position indicator offset.
   *  \return a reference to this ph_stream.
   */
  binary_stream& move_byte_pos(byte_offset offset) final;

protected:
  // stream_in overrides.
  void on_read(void* buf, size_t elementSize, size_t bufSize) final;

private:
  file m_file;
  size_t m_byte_count;
  size_t m_element_count;
};

}

#endif

