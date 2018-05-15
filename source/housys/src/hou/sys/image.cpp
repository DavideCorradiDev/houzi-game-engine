// Houzi Game Engine
// Copyright (c) 2018 Davide Corradi
// Licensed under the MIT license.

#include "hou/sys/image.hpp"

#include "hou/cor/assertions.hpp"



namespace hou
{

namespace
{

template <size_t Dim>
bool element_wise_lower(const vec<uint, Dim>& lhs, const vec<uint, Dim>& rhs);

template <size_t Dim>
bool element_wise_lower_or_equal(
  const vec<uint, Dim>& lhs, const vec<uint, Dim>& rhs);

template <size_t DimOut, size_t DimIn>
vec<uint, DimOut> pad_vector(const vec<uint, DimIn>& vec_in, uint value);

template <pixel_format PF>
image1<PF> get_image_sub_image(
  const image1<PF>& in, const vec1u& offset, const vec1u& size);

template <pixel_format PF>
image2<PF> get_image_sub_image(
  const image2<PF>& in, const vec2u& offset, const vec2u& size);

template <pixel_format PF>
image3<PF> get_image_sub_image(
  const image3<PF>& in, const vec3u& offset, const vec3u& size);

template <pixel_format PF>
void set_image_sub_image(
  image1<PF>& out, const vec1u& offset, const image1<PF>& in);

template <pixel_format PF>
void set_image_sub_image(
  image2<PF>& out, const vec2u& offset, const image2<PF>& in);

template <pixel_format PF>
void set_image_sub_image(
  image3<PF>& out, const vec3u& offset, const image1<PF>& in);



template <size_t Dim>
bool element_wise_lower(const vec<uint, Dim>& lhs, const vec<uint, Dim>& rhs)
{
  for(size_t i = 0; i < Dim; ++i)
  {
    if(lhs(i) >= rhs(i))
    {
      return false;
    }
  }
  return true;
}



template <size_t Dim>
bool element_wise_lower_or_equal(
  const vec<uint, Dim>& lhs, const vec<uint, Dim>& rhs)
{
  return std::equal(
    lhs.begin(), lhs.end(), rhs.begin(), rhs.end(), std::less_equal<uint>());
}



template <size_t DimOut, size_t DimIn>
vec<uint, DimOut> pad_vector(const vec<uint, DimIn>& vec_in, uint value)
{
  vec<uint, DimOut> vec_out = vec<uint, DimOut>::filled(value);
  for(size_t i = 0; i < std::min(DimOut, DimIn); ++i)
  {
    vec_out(i) = vec_in(i);
  }
  return vec_out;
}



template <pixel_format PF>
image1<PF> get_image_sub_image(
  const image1<PF>& in, const vec1u& offset, const vec1u& size)
{
  HOU_CHECK_0(
    element_wise_lower_or_equal(offset + size, in.get_size()), out_of_range);
  image1<PF> out(size);
  for(uint x = 0; x < size.x(); ++x)
  {
    vec1u pos = vec1u(x);
    out.set_pixel(pos, in.get_pixel(offset + pos));
  }
  return out;
}



template <pixel_format PF>
image2<PF> get_image_sub_image(
  const image2<PF>& in, const vec2u& offset, const vec2u& size)
{
  HOU_CHECK_0(
    element_wise_lower_or_equal(offset + size, in.get_size()), out_of_range);
  image2<PF> out(size);
  for(uint x = 0; x < size.x(); ++x)
  {
    for(uint y = 0; y < size.y(); ++y)
    {
      vec2u pos = vec2u(x, y);
      out.set_pixel(pos, in.get_pixel(offset + pos));
    }
  }
  return out;
}



template <pixel_format PF>
image3<PF> get_image_sub_image(
  const image3<PF>& in, const vec3u& offset, const vec3u& size)
{
  HOU_CHECK_0(
    element_wise_lower_or_equal(offset + size, in.get_size()), out_of_range);
  image3<PF> out(size);
  for(uint x = 0; x < size.x(); ++x)
  {
    for(uint y = 0; y < size.y(); ++y)
    {
      for(uint z = 0; z < size.z(); ++z)
      {
        vec3u pos = vec3u(x, y, z);
        out.set_pixel(pos, in.get_pixel(offset + pos));
      }
    }
  }
  return out;
}



template <pixel_format PF>
void set_image_sub_image(
  image1<PF>& out, const vec1u& offset, const image1<PF>& in)
{
  HOU_CHECK_0(
    element_wise_lower_or_equal(offset + in.get_size(), out.get_size()),
    out_of_range);
  for(uint x = 0; x < in.get_size().x(); ++x)
  {
    vec1u pos = vec1u(x);
    out.set_pixel(offset + pos, in.get_pixel(pos));
  }
}



template <pixel_format PF>
void set_image_sub_image(
  image2<PF>& out, const vec2u& offset, const image2<PF>& in)
{
  HOU_CHECK_0(
    element_wise_lower_or_equal(offset + in.get_size(), out.get_size()),
    out_of_range);
  for(uint x = 0; x < in.get_size().x(); ++x)
  {
    for(uint y = 0; y < in.get_size().y(); ++y)
    {
      vec2u pos = vec2u(x, y);
      out.set_pixel(offset + pos, in.get_pixel(pos));
    }
  }
}



template <pixel_format PF>
void set_image_sub_image(
  image3<PF>& out, const vec3u& offset, const image3<PF>& in)
{
  HOU_CHECK_0(
    element_wise_lower_or_equal(offset + in.get_size(), out.get_size()),
    out_of_range);
  for(uint x = 0; x < in.get_size().x(); ++x)
  {
    for(uint y = 0; y < in.get_size().y(); ++y)
    {
      for(uint z = 0; z < in.get_size().z(); ++z)
      {
        vec3u pos = vec3u(x, y, z);
        out.set_pixel(offset + pos, in.get_pixel(pos));
      }
    }
  }
}

}  // namespace



template <size_t Dim, pixel_format PF>
image<Dim, PF>::image()
  : m_size()
  , m_pixels()
{}



template <size_t Dim, pixel_format PF>
image<Dim, PF>::image(const size_type& size)
  : m_size(size)
  , m_pixels(compute_pixel_count(), pixel())
{}



template <size_t Dim, pixel_format PF>
image<Dim, PF>::image(const size_type& size, const pixel& px)
  : m_size(size)
  , m_pixels(compute_pixel_count(), px)
{}



template <size_t Dim, pixel_format PF>
image<Dim, PF>::image(const size_type& size, const span<const pixel>& pixels)
  : m_size(size)
  , m_pixels(pixels.begin(), pixels.end())
{
  HOU_PRECOND(pixels.size() == compute_pixel_count());
}



template <size_t Dim, pixel_format PF>
image<Dim, PF>::image(const size_type& size, pixel_collection&& pixels)
  : m_size(size)
  , m_pixels(pixels)
{
  HOU_PRECOND(m_pixels.size() == compute_pixel_count());
}



template <size_t Dim, pixel_format PF>
template <size_t otherDim, pixel_format otherFmt, typename Enable>
image<Dim, PF>::image(const image<otherDim, otherFmt>& other)
  : m_size(pad_vector<Dim>(other.get_size(), 1u))
  , m_pixels(compute_pixel_count())
{
  for(size_t i = 0; i < m_pixels.size(); ++i)
  {
    m_pixels[i] = other.m_pixels[i];
  }
}



template <size_t Dim, pixel_format PF>
const typename image<Dim, PF>::size_type& image<Dim, PF>::get_size() const
  noexcept
{
  return m_size;
}



template <size_t Dim, pixel_format PF>
const typename image<Dim, PF>::pixel_collection& image<Dim, PF>::get_pixels()
  const noexcept
{
  return m_pixels;
}



template <size_t Dim, pixel_format PF>
void image<Dim, PF>::set_pixels(const span<const pixel>& pixels)
{
  HOU_PRECOND(pixels.size() == m_pixels.size());
  std::copy(pixels.begin(), pixels.end(), m_pixels.begin());
}



template <size_t Dim, pixel_format PF>
const typename image<Dim, PF>::pixel& image<Dim, PF>::get_pixel(
  const offset_type& coordinates) const
{
  // compute_pixel_index will throw if coordinates is not valid.
  return m_pixels[compute_pixel_index(coordinates)];
}



template <size_t Dim, pixel_format PF>
void image<Dim, PF>::set_pixel(
  const offset_type& coordinates, const pixel& value)
{
  // compute_pixel_index will throw if coordinates is not valid.
  m_pixels[compute_pixel_index(coordinates)] = value;
}



template <size_t Dim, pixel_format PF>
image<Dim, PF> image<Dim, PF>::get_sub_image(
  const offset_type& offset, const size_type& size)
{
  // get_image_sub_image will throw if the coordinates are not valid.
  return get_image_sub_image(*this, offset, size);
}



template <size_t Dim, pixel_format PF>
void image<Dim, PF>::set_sub_image(const offset_type& offset, const image& im)
{
  // set_image_sub_image will throw if the coordinates are not valid.
  return set_image_sub_image(*this, offset, im);
}



template <size_t Dim, pixel_format PF>
void image<Dim, PF>::clear(const pixel& pixel)
{
  m_pixels = pixel_collection(compute_pixel_count(), pixel);
}



template <size_t Dim, pixel_format PF>
size_t image<Dim, PF>::compute_pixel_count() const
{
  // TODO: implement and use operator[] on matrix to make this noexcept.
  size_t retval = 1u;
  for(size_t i = 0; i < Dim; ++i)
  {
    retval *= m_size(i);
  }
  return retval;
}



template <size_t Dim, pixel_format PF>
size_t image<Dim, PF>::compute_pixel_index(const offset_type& coordinates) const
{
  HOU_CHECK_0(element_wise_lower(coordinates, m_size), out_of_range);

  size_t idx = 0;
  size_t multiplier = 1;
  for(size_t i = 0; i < Dim; ++i)
  {
    idx += coordinates(i) * multiplier;
    multiplier *= m_size(i);
  }
  return idx;
}



template <size_t Dim, pixel_format PF>
bool operator==(const image<Dim, PF>& lhs, const image<Dim, PF>& rhs) noexcept
{
  return lhs.get_size() == rhs.get_size()
    && lhs.get_pixels() == rhs.get_pixels();
}



template <size_t Dim, pixel_format PF>
bool operator!=(const image<Dim, PF>& lhs, const image<Dim, PF>& rhs) noexcept
{
  return !(lhs == rhs);
}



template <size_t Dim, pixel_format PF>
std::ostream& operator<<(std::ostream& os, const image<Dim, PF>& im)
{
  return os << "{size_type = " << transpose(im.get_size())
            << ", pixels = " << im.get_pixels() << "}";
}



#define INSTANTIATE_IMAGE_BASE(Dim, PF)                                        \
  template class image<Dim, PF>;                                               \
  template bool operator==<Dim, PF>(                                           \
    const image<Dim, PF>&, const image<Dim, PF>&);                             \
  template bool operator!=<Dim, PF>(                                           \
    const image<Dim, PF>&, const image<Dim, PF>&);                             \
  template std::ostream& operator<<<Dim, PF>(                                  \
    std::ostream&, const image<Dim, PF>&);



#define INSTANTIATE_CONVERSION_CONSTRUCTOR(Dim1, Dim2, pf1, pf2)               \
  template image<Dim1, pf1>::image<Dim2, pf2, void>(const image<Dim2, pf2>&);



#define INSTANTIATE_CONVERSION_CONSTRUCTORS_WITH_DIMENSIONS(Dim1, Dim2)        \
  INSTANTIATE_CONVERSION_CONSTRUCTOR(                                          \
    Dim1, Dim2, pixel_format::r, pixel_format::rg)                             \
  INSTANTIATE_CONVERSION_CONSTRUCTOR(                                          \
    Dim1, Dim2, pixel_format::r, pixel_format::rgb)                            \
  INSTANTIATE_CONVERSION_CONSTRUCTOR(                                          \
    Dim1, Dim2, pixel_format::r, pixel_format::rgba)                           \
  INSTANTIATE_CONVERSION_CONSTRUCTOR(                                          \
    Dim1, Dim2, pixel_format::rg, pixel_format::r)                             \
  INSTANTIATE_CONVERSION_CONSTRUCTOR(                                          \
    Dim1, Dim2, pixel_format::rg, pixel_format::rgb)                           \
  INSTANTIATE_CONVERSION_CONSTRUCTOR(                                          \
    Dim1, Dim2, pixel_format::rg, pixel_format::rgba)                          \
  INSTANTIATE_CONVERSION_CONSTRUCTOR(                                          \
    Dim1, Dim2, pixel_format::rgb, pixel_format::r)                            \
  INSTANTIATE_CONVERSION_CONSTRUCTOR(                                          \
    Dim1, Dim2, pixel_format::rgb, pixel_format::rg)                           \
  INSTANTIATE_CONVERSION_CONSTRUCTOR(                                          \
    Dim1, Dim2, pixel_format::rgb, pixel_format::rgba)                         \
  INSTANTIATE_CONVERSION_CONSTRUCTOR(                                          \
    Dim1, Dim2, pixel_format::rgba, pixel_format::r)                           \
  INSTANTIATE_CONVERSION_CONSTRUCTOR(                                          \
    Dim1, Dim2, pixel_format::rgba, pixel_format::rg)                          \
  INSTANTIATE_CONVERSION_CONSTRUCTOR(                                          \
    Dim1, Dim2, pixel_format::rgba, pixel_format::rgb)



#define INSTANTIATE_CONVERSION_CONSTRUCTORS_WITH_SAME_DIMENSION(Dim)           \
  INSTANTIATE_CONVERSION_CONSTRUCTORS_WITH_DIMENSIONS(Dim, Dim)



#define INSTANTIATE_CONVERSION_CONSTRUCTORS_WITH_DIFFERENT_DIMENSIONS(         \
  Dim1, Dim2)                                                                  \
  INSTANTIATE_CONVERSION_CONSTRUCTORS_WITH_DIMENSIONS(Dim1, Dim2)              \
  INSTANTIATE_CONVERSION_CONSTRUCTOR(                                          \
    Dim1, Dim2, pixel_format::r, pixel_format::r)                              \
  INSTANTIATE_CONVERSION_CONSTRUCTOR(                                          \
    Dim1, Dim2, pixel_format::rg, pixel_format::rg)                            \
  INSTANTIATE_CONVERSION_CONSTRUCTOR(                                          \
    Dim1, Dim2, pixel_format::rgb, pixel_format::rgb)                          \
  INSTANTIATE_CONVERSION_CONSTRUCTOR(                                          \
    Dim1, Dim2, pixel_format::rgba, pixel_format::rgba)



#define INSTANTIATE_IMAGE_WITH_DIMENSION(Dim)                                  \
  INSTANTIATE_IMAGE_BASE(Dim, pixel_format::r)                                 \
  INSTANTIATE_IMAGE_BASE(Dim, pixel_format::rg)                                \
  INSTANTIATE_IMAGE_BASE(Dim, pixel_format::rgb)                               \
  INSTANTIATE_IMAGE_BASE(Dim, pixel_format::rgba)



INSTANTIATE_IMAGE_WITH_DIMENSION(1u)
INSTANTIATE_CONVERSION_CONSTRUCTORS_WITH_SAME_DIMENSION(1u)
INSTANTIATE_IMAGE_WITH_DIMENSION(2u)
INSTANTIATE_CONVERSION_CONSTRUCTORS_WITH_DIFFERENT_DIMENSIONS(2u, 1u)
INSTANTIATE_CONVERSION_CONSTRUCTORS_WITH_SAME_DIMENSION(2u)
INSTANTIATE_IMAGE_WITH_DIMENSION(3u)
INSTANTIATE_CONVERSION_CONSTRUCTORS_WITH_DIFFERENT_DIMENSIONS(3u, 1u)
INSTANTIATE_CONVERSION_CONSTRUCTORS_WITH_DIFFERENT_DIMENSIONS(3u, 2u)
INSTANTIATE_CONVERSION_CONSTRUCTORS_WITH_SAME_DIMENSION(3u)

}  // namespace hou
