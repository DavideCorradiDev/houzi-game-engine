namespace hou
{

template <size_t Dim>
pixel_view<Dim>::pixel_view() noexcept
  : m_data(nullptr)
  , m_size()
  , m_byte_depth(0u)
  , m_byte_count(0u)
{}



template <size_t Dim>
pixel_view<Dim>::pixel_view(
  const_pointer data, const size_type& size, byte_depth_type bpp)
  : m_data(data)
  , m_size(size)
  , m_byte_depth(bpp)
  , m_byte_count(compute_length(size, bpp))
{}



template <size_t Dim>
template <pixel_format PF>
pixel_view<Dim>::pixel_view(const image<Dim, PF>& im)
  : pixel_view(reinterpret_cast<const_pointer>(im.get_pixels().data()),
      im.get_size(), image<Dim, PF>::pixel_byte_count)
{}



template <size_t Dim>
template <size_t OtherDim, typename Enable>
pixel_view<Dim>::pixel_view(const pixel_view<OtherDim>& other)
  : m_data(other.m_data)
  , m_size(pad_size(other.m_size))
  , m_byte_depth(other.m_byte_depth)
  , m_byte_count(other.m_byte_count)
{}



template <size_t Dim>
typename pixel_view<Dim>::const_pointer pixel_view<Dim>::get_data() const
  noexcept
{
  return m_data;
}



template <size_t Dim>

const typename pixel_view<Dim>::size_type& pixel_view<Dim>::get_size() const
  noexcept
{
  return m_size;
}



template <size_t Dim>
typename pixel_view<Dim>::byte_depth_type pixel_view<Dim>::get_bytes_per_pixel()
  const noexcept
{
  return m_byte_depth;
}



template <size_t Dim>
typename pixel_view<Dim>::length_type pixel_view<Dim>::get_byte_count() const
  noexcept
{
  return m_byte_count;
}



template <size_t Dim>
typename pixel_view<Dim>::const_reference pixel_view<Dim>::at(
  length_type idx) const
{
  HOU_CHECK_0(idx < m_byte_count, hou::out_of_range);
  return *(m_data + idx);
}



template <size_t Dim>
typename pixel_view<Dim>::const_reference pixel_view<Dim>::operator[](
  length_type idx) const noexcept
{
  return *(m_data + idx);
}

template <size_t Dim>
typename pixel_view<Dim>::length_type pixel_view<Dim>::compute_length(
  const size_type& size, byte_depth_type bpp)
{
  length_type pixel_count = bpp;
  for(size_t i = 0; i < Dim; ++i)
  {
    pixel_count *= size(i);
  }
  return pixel_count;
}



template <size_t Dim>
template <size_t OtherDim, typename Enable>
typename pixel_view<Dim>::size_type pixel_view<Dim>::pad_size(
  const matrix<uint, OtherDim, 1u>& size)
{
  size_type retval = size_type::filled(1u);
  for(size_t i = 0; i < OtherDim; ++i)
  {
    retval[i] = size[i];
  }
  return retval;
}

}  // namespace hou
