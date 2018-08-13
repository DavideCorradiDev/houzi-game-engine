#ifndef HOU_GFX_PIXEL_SPAN_HPP
#define HOU_GFX_PIXEL_SPAN_HPP

#include "hou/gfx/pixel_span_fwd.hpp"

#include "hou/gfx/gfx_config.hpp"

#include "hou/mth/matrix.hpp"

#include <iostream>



namespace hou
{

template <size_t Dim>
class pixel_span
{
public:
  using value_type = uint8_t;
  using size_type = matrix<uint, Dim, 1u>;
  using length_type = std::size_t;
  using byte_depth_type = uint;
  using difference_type = std::ptrdiff_t;
  using reference = value_type&;
  using const_reference = std::add_const_t<reference>;
  using pointer = std::add_pointer_t<reference>;
  using const_pointer = std::add_pointer_t<const_reference>;

public:
  pixel_span() noexcept;
  pixel_span(pointer data, const size_type& size, byte_depth_type bpp);
  template <size_t OtherDim,
    typename Enable = std::enable_if_t<(OtherDim < Dim)>>
  pixel_span(const pixel_span<OtherDim>& other);

  pointer get_data() const noexcept;
  const size_type& get_size() const noexcept;
  byte_depth_type get_byte_depth() const noexcept;
  length_type get_length() const noexcept;

  reference at(length_type idx) const;
  reference operator[](length_type idx) const noexcept;

private:
  template <size_t OtherDim>
  friend class pixel_span;

private:
  static length_type compute_length(const size_type& size, byte_depth_type bpp);
  template <size_t OtherDim,
    typename Enable = std::enable_if_t<(OtherDim < Dim)>>
  size_type pad_size(const matrix<uint, OtherDim, 1u>& size);

private:
  pointer m_data;
  size_type m_size;
  byte_depth_type m_byte_depth;
  length_type m_length;
};

template <size_t Dim>
bool operator==(
  const pixel_span<Dim>& lhs, const pixel_span<Dim>& rhs) noexcept;
template <size_t Dim>
bool operator!=(
  const pixel_span<Dim>& lhs, const pixel_span<Dim>& rhs) noexcept;
template <size_t Dim>
std::ostream& operator<<(std::ostream& os, const pixel_span<Dim>& s);

}  // namespace hou



#include "hou/gfx/pixel_span.inl"

#endif
