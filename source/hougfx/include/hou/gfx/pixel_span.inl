namespace hou
{

template <size_t Dim>
pixel_span<Dim>::pixel_span() noexcept
  : m_data(nullptr)
  , m_size()
  , m_byte_depth(0u)
  , m_length(0u)
{}



template <size_t Dim>
pixel_span<Dim>::pixel_span(
  pointer data, const size_type& size, byte_depth_type bpp)
  : m_data(data)
  , m_size(size)
  , m_byte_depth(bpp)
  , m_length(compute_length(size, bpp))
{}



template <size_t Dim>
template <size_t OtherDim, typename Enable>
pixel_span<Dim>::pixel_span(const pixel_span<OtherDim>& other)
  : m_data(other.m_data)
  , m_size(pad_size(other.m_size))
  , m_byte_depth(other.m_byte_depth)
  , m_length(other.m_length)
{}



template <size_t Dim>
typename pixel_span<Dim>::pointer pixel_span<Dim>::get_data() const noexcept
{
  return m_data;
}



template <size_t Dim>

const typename pixel_span<Dim>::size_type& pixel_span<Dim>::get_size() const
  noexcept
{
  return m_size;
}



template <size_t Dim>
typename pixel_span<Dim>::byte_depth_type pixel_span<Dim>::get_byte_depth()
  const noexcept
{
  return m_byte_depth;
}



template <size_t Dim>
typename pixel_span<Dim>::length_type pixel_span<Dim>::get_length() const
  noexcept
{
  return m_length;
}



template <size_t Dim>
typename pixel_span<Dim>::reference pixel_span<Dim>::at(length_type idx) const
{
  HOU_CHECK_0(idx < m_length, hou::out_of_range);
  return *(m_data + idx);
}



template <size_t Dim>
typename pixel_span<Dim>::reference pixel_span<Dim>::operator[](
  length_type idx) const noexcept
{
  return *(m_data + idx);
}

template <size_t Dim>
typename pixel_span<Dim>::length_type pixel_span<Dim>::compute_length(
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
typename pixel_span<Dim>::size_type pixel_span<Dim>::pad_size(
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
