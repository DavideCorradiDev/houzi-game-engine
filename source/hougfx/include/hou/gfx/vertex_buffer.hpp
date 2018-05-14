// Houzi Game Engine
// Copyright (c) 2018 Davide Corradi
// Licensed under the MIT license.

#ifndef HOU_GFX_VERTEX_BUFFER_HPP
#define HOU_GFX_VERTEX_BUFFER_HPP

#include "hou/gfx/vertex_buffer_fwd.hpp"
#include "hou/gfx/vertex_buffer_target.hpp"

#include "hou/gfx/gfx_config.hpp"

#include "hou/cor/non_copyable.hpp"

#include "hou/cor/assertions.hpp"
#include "hou/cor/span.hpp"
#include "hou/cor/template_utils.hpp"

#include "hou/gl/gl_buffer_handle.hpp"

#include <vector>



namespace hou
{

/** Represents a generic interface for a graphical memory buffer.
 */
class HOU_GFX_API vertex_buffer : public non_copyable
{
public:
  /** Binds the vertex_buffer to the current graphic_context.
   *
   * \param buffer the vertex_buffer to be bound.
   *
   * \param target the target to bound the buffer to.
   */
  static void bind(const vertex_buffer& buffer, vertex_buffer_target target);

  /** Unbinds the vertex_buffer for the given target, if present.
   *
   * \param target the target.
   */
  static void unbind(vertex_buffer_target target);

public:
  /** size_type constructor.
   *
   * Builds a vertex_buffer with the given size.
   * The buffer is initialized to 0.
   *
   * \param size the size of the buffer in bytes.
   *
   * \param dynamic_storage if true, the vertex_buffer is modifiable, otherwise
   * it is not.
   */
  vertex_buffer(uint byte_count, bool dynamic_storage);

  /** Data constructor
   *
   * Builds a vertex_buffer with the given data.
   *
   * \param byte_count the size of the buffer in bytes.
   *
   * \param data a pointer to a data buffer.
   *
   * \param dynamic_storage if true, the vertex_buffer is modifiable, otherwise
   * it is not.
   */
  vertex_buffer(uint byte_count, const void* data, bool dynamic_storage);

  /** Move constructor.
   *
   * \param other the other vertex_buffer.
   */
  vertex_buffer(vertex_buffer&& other) noexcept = default;

  /** Retrieves the reference to the OpenGL buffer.
   *
   * \return the reference to the OpenGL buffer.
   */
  const gl::buffer_handle& get_handle() const noexcept;

  /** Checks if this vertex_buffer is bound to the given target.
   *
   * \target target the target to check.
   *
   * \return the result of the check.
   */
  bool is_bound(vertex_buffer_target target) const;

  /** Returns the number of bytes used by the vertex_buffer.
   *
   * \return the number of bytes used by the vertex_buffer.
   */
  uint get_byte_count() const;

private:
  gl::buffer_handle m_handle;
  uint m_byte_count;
};

/** Represents a concrete instance of a type of graphical memory buffer.
 *
 * \tparam T the type of objects stored in the buffer.
 *
 * \tparam DynamicStorage if true, the buffer can be modified after creation.
 * If false, this is not possible.
 */
template <typename T, bool DynamicStorage = false>
class vertex_buffer_t : public vertex_buffer
{
public:
  /** Type of the objects stored in the buffer. */
  using value_type = T;

  /** Type representing the whole data stored in the buffer. */
  using data_type = std::vector<T>;

public:
  /** size_type constructor.
   *
   * Builds a vertex_buffer with the given number of elements of type T.
   * The buffer is initialized to 0.
   *
   * \param size the number of elements composing the buffer.
   */
  vertex_buffer_t(uint size);

  /** Data constructor.
   *
   * Builds a vertex_buffer with the given data.
   *
   * \param data the data.
   */
  vertex_buffer_t(const span<const T>& data);

  /** Retrieves the number of elements in the buffer.
   *
   * \return the number of elements in the buffer.
   */
  uint get_size() const;

  /** Retrieves the data contained in the buffer.
   *
   * \return the data contained in the buffer.
   */
  data_type get_data() const;

  /** Retrieves a sub-set of the data contained in the buffer.
   *
   * Throws if offset plus size is greater than the size of the buffer.
   *
   * \param offset the number of elements to skip at the beginning of the
   * buffer.
   *
   * \param element_count the number of elements to read.
   *
   * \return a collection with element_count elements taken from the
   * vertex_buffer starting from the given offset.
   */
  data_type get_sub_data(uint offset, uint element_count) const;

  /** Sets the data contained in the buffer.
   *
   * This function is defined only for dynamic render buffers.
   *
   * \tparam DS dummy template parameter.
   *
   * \tparam Enable enabling parameter.
   *
   * \param data the data.
   */
  template <bool DS = DynamicStorage, typename Enable = std::enable_if_t<DS>>
  void set_data(const span<const T>& data);

  /** Sets a sub-set of the data contained in the buffer.
   *
   * This function is defined only for dynamic render buffers.
   * Throws if offset plus the size of data is greater then the size of the
   * vertex_buffer.
   *
   * \tparam DS dummy template parameter.
   *
   * \tparam Enable enabling parameter.
   *
   * \param offset the offset.
   *
   * \param data the data.
   */
  template <bool DS = DynamicStorage, typename Enable = std::enable_if_t<DS>>
  void set_sub_data(uint offset, const span<const T>& data);
};

}  // namespace hou

#include "hou/gfx/vertex_buffer.inl"

#endif
