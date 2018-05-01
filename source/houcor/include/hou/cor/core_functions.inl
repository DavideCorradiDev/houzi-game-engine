namespace hou
{

template <typename T, typename InputIt1, typename InputIt2, typename Enable>
bool container_close(InputIt1 begin1, InputIt1 end1, InputIt2 begin2, T acc)
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

}  // namespace hou
