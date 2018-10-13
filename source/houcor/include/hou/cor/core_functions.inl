namespace hou
{

template <typename T, typename InputIt1, typename InputIt2, typename Enable>
constexpr bool container_close(
  InputIt1 begin1, InputIt1 end1, InputIt2 begin2, T acc) noexcept
{
  for(; begin1 != end1; ++begin1, ++begin2)
  {
    if(!close(*begin1, *begin2, acc))
    {
      return false;
    }
  }
  return true;
}



template <typename Iterator>
std::ostream& container_stream(std::ostream& os, Iterator begin, Iterator end)
{
  os << "{";
  for(auto it = begin; it != end; ++it)
  {
    if(it != begin)
    {
      os << ", ";
    }
    os << *it;
  }
  return os << "}";
}



template <typename T>
std::ostream& stream_value(
  std::ostream& os, const std::string& type_name, T value)
{
  return os << type_name << "("
            << static_cast<typename std::underlying_type<T>::type>(value)
            << ")";
}



#ifndef HOU_DOXYGEN
extern template HOU_COR_API bool close<float, void>(
  float, float, float) noexcept;
extern template HOU_COR_API bool close<double, void>(
  double, double, double) noexcept;
#endif

}  // namespace hou
