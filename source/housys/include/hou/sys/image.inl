// Houzi Game Engine
// Copyright (c) 2018 Davide Corradi
// Licensed under the MIT license.

namespace hou
{

template <size_t Dim, pixel_format PF>
template <size_t OtherDim>
vec<uint, Dim> image<Dim, PF>::resize_size_vec(
  const vec<uint, OtherDim>& vec_in, uint value)
{
  vec<uint, Dim> vec_out = vec<uint, Dim>::filled(value);
  for(size_t i = 0; i < std::min(Dim, OtherDim); ++i)
  {
    vec_out(i) = vec_in(i);
  }
  return vec_out;
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
  return os << "{size = " << transpose(im.get_size())
            << ", pixels = " << im.get_pixels() << "}";
}



extern template class HOU_SYS_API image<1u, pixel_format::r>;
extern template class HOU_SYS_API image<1u, pixel_format::rg>;
extern template class HOU_SYS_API image<1u, pixel_format::rgb>;
extern template class HOU_SYS_API image<1u, pixel_format::rgba>;

extern template class HOU_SYS_API image<2u, pixel_format::r>;
extern template class HOU_SYS_API image<2u, pixel_format::rg>;
extern template class HOU_SYS_API image<2u, pixel_format::rgb>;
extern template class HOU_SYS_API image<2u, pixel_format::rgba>;

extern template class HOU_SYS_API image<3u, pixel_format::r>;
extern template class HOU_SYS_API image<3u, pixel_format::rg>;
extern template class HOU_SYS_API image<3u, pixel_format::rgb>;
extern template class HOU_SYS_API image<3u, pixel_format::rgba>;

}  // namespace hou
