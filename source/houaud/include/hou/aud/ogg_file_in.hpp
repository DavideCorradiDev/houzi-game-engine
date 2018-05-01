// Houzi Game Engine
// Copyright (c) 2018 Davide Corradi
// Licensed under the MIT license.

#ifndef HOU_AUD_OGG_FILE_IN_HPP
#define HOU_AUD_OGG_FILE_IN_HPP

#include "hou/aud/aud_export.hpp"
#include "hou/aud/audio_stream_in.hpp"

#include "hou/cor/non_copyable.hpp"

#include "hou/sys/file_handle.hpp"

#include <memory>



struct OggVorbis_File;



namespace hou
{

/** Input ogg file stream.
 */
class HOU_AUD_API ogg_file_in
  : public non_copyable
  , public audio_stream_in
{
public:
  /** Checks if the file corresponding to the given path is a ogg file.
   *
   * \param path the file path.
   *
   * \return true if the specified file is a ogg file.
   */
  static bool check(const std::string& path);

public:
  /** Path constructor.
   *
   * Throws if the provided path is not valid or does not correspond to a ogg
   * file.
   *
   * \param path the path to the file to be opened.
   */
  explicit ogg_file_in(const std::string& path);

  /** Move constructor.
   *
   * \param other the other object.
   */
  ogg_file_in(ogg_file_in&& other);

  /** Destructor.
   */
  virtual ~ogg_file_in();

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
   * Throws if pos is negative or greater than the number of bytes in the
   * stream.
   *
   * \param pos the byte position indicator value.
   *
   * \return a reference to this stream.
   */
  binary_stream& set_byte_pos(byte_position pos) final;

  /** Moves the current byte position indicator.
   *
   * Throws if the offset moves the position indicator to a negative position
   * or to a position greater than the number of bytes in the stream.
   *
   * \param offset the byte position indicator offset.
   *
   * \return a reference to this stream.
   */
  binary_stream& move_byte_pos(byte_offset offset) final;

  // audio_stream overrides.
  size_t get_sample_count() const final;
  sample_position get_sample_pos() const final;
  audio_stream_in& set_sample_pos(sample_position pos) final;
  audio_stream_in& move_sample_pos(sample_offset offset) final;

private:
  void read_metadata();
  void on_read(void* buf, size_t element_size, size_t buf_size) final;

private:
  std::unique_ptr<OggVorbis_File> m_vorbis_file;
  int m_logical_bit_stream;
  size_t m_pcm_size;
  size_t m_byte_count;
  size_t m_element_count;
  bool m_eof;
  bool m_error;
};

}  // namespace hou

#endif
