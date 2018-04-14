// Houzi Game Engine
// Copyright (c) 2018 Davide Corradi
// Licensed under the MIT license. See license.md for more details.

#ifndef HOU_GFX_RENDER_BUFFER_HPP
#define HOU_GFX_RENDER_BUFFER_HPP

#include "hou/cor/NonCopyable.hpp"
#include "hou/gfx/GfxExport.hpp"

#include "hou/cor/BasicTypes.hpp"
#include "hou/cor/Error.hpp"
#include "hou/cor/Span.hpp"
#include "hou/cor/TemplateUtils.hpp"

#include "hou/gfx/RenderBufferFwd.hpp"
#include "hou/gfx/RenderBufferTarget.hpp"

#include "hou/gl/GlBufferHandle.hpp"

#include <vector>



namespace hou
{

/** Represents a generic interface for a graphical memory buffer.
 */
class HOU_GFX_API RenderBuffer : public NonCopyable
{
public:
  /** Binds the RenderBuffer to the current GraphicContext.
   *
   *  \param buffer the RenderBuffer to be bound.
   *  \param target the target to bound the buffer to.
   */
  static void bind(const RenderBuffer& buffer, RenderBufferTarget target);

  /** Unbinds the RenderBuffer for the given target, if present.
   *
   *  \param target the target.
   */
  static void unbind(RenderBufferTarget target);

public:
  /** Retrieves the reference to the OpenGL buffer.
   *
   *  \return the reference to the OpenGL buffer.
   */
  const gl::BufferHandle& getHandle() const;

  /** Checks if this RenderBuffer is bound to the given target.
   *
   *  \target target the target to check.
   *  \return the result of the check.
   */
  bool isBound(RenderBufferTarget target) const;

  /** Returns the number of bytes used by the RenderBuffer.
   *
   *  \return the number of bytes used by the RenderBuffer.
   */
  uint getByteCount() const;

protected:
  /** Size constructor.
   *
   *  Builds a RenderBuffer with the given size.
   *  The buffer is initialized to 0.
   *
   *  \param size the size of the buffer in bytes.
   *  \param dynamicStorage if true, the RenderBuffer is modifiable, otherwise
   * it is not.
   */
  RenderBuffer(uint byteCount, bool dynamicStorage);

  /** Data constructor
   *
   *  Builds a RenderBuffer with the given data.
   *
   *  \param byteCount the size of the buffer in bytes.
   *  \param data a pointer to a data buffer.
   *  \param dynamicStorage if true, the RenderBuffer is modifiable, otherwise
   * it is not.
   */
  RenderBuffer(uint byteCount, const void* data, bool dynamicStorage);

  /** Move constructor.
   *
   *  \param other the other RenderBuffer.
   */
  RenderBuffer(RenderBuffer&& other);

private:
  gl::BufferHandle mHandle;
  uint mByteCount;
};

/** Represents a concrete instance of a type of graphical memory buffer.
 *
 *  \tparam T the type of objects stored in the buffer.
 *  \tparam dynamicStorage if true, the buffer can be modified after creation.
 *  If false, this is not possible.
 */
template <typename T, bool dynamicStorage = false>
class RenderBufferT : public RenderBuffer
{
public:
  /** Type of the objects stored in the buffer. */
  using ValueType = T;

  /** Type representing the whole data stored in the buffer. */
  using DataType = std::vector<T>;

public:
  /** Size constructor.
   *
   *  Builds a RenderBuffer with the given number of elements of type T.
   *  The buffer is initialized to 0.
   *
   *  \param size the number of elements composing the buffer.
   */
  RenderBufferT(uint size);

  /** Data constructor.
   *
   *  Builds a RenderBuffer with the given data.
   *
   *  \param data the data.
   */
  RenderBufferT(const Span<const T>& data);

  /** Move constructor.
   *
   *  \param other the other RenderBuffer.
   */
  RenderBufferT(RenderBuffer&& other);

  /** Retrieves the number of elements in the buffer.
   *
   *  \return the number of elements in the buffer.
   */
  uint getSize() const;

  /** Retrieves the data contained in the buffer.
   *
   *  \return the data contained in the buffer.
   */
  DataType getData() const;

  /** Retrieves a sub-set of the data contained in the buffer.
   *
   *  Throws if offset plus size is greater than the size of the buffer.
   *
   *  \param offset the number of elements to skip at the beginning of the
   *  buffer.
   *  \param elementCount the number of elements to read.
   *  \return a collection with elementCount elements taken from the
   *  RenderBuffer starting from the given offset.
   */
  DataType getSubData(uint offset, uint elementCount) const;

  /** Sets the data contained in the buffer.
   *
   *  This function is defined only for dynamic render buffers.
   *
   *  \tparam ds dummy template parameter.
   *  \tparam Enable enabling parameter.
   *  \param data the data.
   */
  template <bool ds = dynamicStorage, typename Enable = std::enable_if_t<ds>>
  void setData(const Span<const T>& data);

  /** Sets a sub-set of the data contained in the buffer.
   *
   *  This function is defined only for dynamic render buffers.
   *  Throws if offset plus the size of data is greater then the size of the
   *  RenderBuffer.
   *
   *  \tparam ds dummy template parameter.
   *  \tparam Enable enabling parameter.
   *  \param offset the offset.
   *  \param data the data.
   */
  template <bool ds = dynamicStorage, typename Enable = std::enable_if_t<ds>>
  void setSubData(uint offset, const Span<const T>& data);
};

}  // namespace hou

#include "hou/gfx/RenderBuffer.inl"

#endif
