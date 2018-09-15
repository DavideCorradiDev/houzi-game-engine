#ifndef HOU_GFX_PIXEL_VIEW_HPP
#define HOU_GFX_PIXEL_VIEW_HPP

#include "hou/gfx/pixel_view_fwd.hpp"

#include "hou/gfx/gfx_config.hpp"

#include "hou/mth/matrix.hpp"

#include "hou/sys/image.hpp"

#include <iostream>



namespace hou
{

template <size_t Dim>
class pixel_view
{
public:
  using value_type = uint8_t;
  using size_type = matrix<uint, Dim, 1u>;
  using length_type = std::size_t;
  using byte_depth_type = uint;
  using difference_type = std::ptrdiff_t;
  using reference = value_type&;
  using const_reference = const value_type&;
  using pointer = value_type*;
  using const_pointer = const value_type*;

public:
  pixel_view() noexcept;
  pixel_view(const_pointer data, const size_type& size, byte_depth_type bpp);
  template <pixel_format PF>
  pixel_view(const image<Dim, PF>& im);
  template <size_t OtherDim,
    typename Enable = std::enable_if_t<(OtherDim < Dim)>>
  pixel_view(const pixel_view<OtherDim>& other);

  const_pointer get_data() const noexcept;
  const size_type& get_size() const noexcept;
  byte_depth_type get_bytes_per_pixel() const noexcept;
  length_type get_byte_count() const noexcept;

  const_reference at(length_type idx) const;
  const_reference operator[](length_type idx) const noexcept;

private:
  template <size_t OtherDim>
  friend class pixel_view;

private:
  static length_type compute_length(const size_type& size, byte_depth_type bpp);
  template <size_t OtherDim,
    typename Enable = std::enable_if_t<(OtherDim < Dim)>>
  size_type pad_size(const matrix<uint, OtherDim, 1u>& size);

private:
  const_pointer m_data;
  size_type m_size;
  byte_depth_type m_byte_depth;
  length_type m_byte_count;
};

template <size_t Dim>
bool operator==(
  const pixel_view<Dim>& lhs, const pixel_view<Dim>& rhs) noexcept;
template <size_t Dim>
bool operator!=(
  const pixel_view<Dim>& lhs, const pixel_view<Dim>& rhs) noexcept;
template <size_t Dim>
std::ostream& operator<<(std::ostream& os, const pixel_view<Dim>& s);

}  // namespace hou



#include "hou/gfx/pixel_view.inl"

#endif
