namespace hou
{

template <typename T>
typename std::enable_if<enable_bitwise_operators<T>::enable, T>::type operator|(
  T lhs, T rhs) noexcept
{
  using utype = typename std::underlying_type<T>::type;
  return static_cast<T>(static_cast<utype>(lhs) | static_cast<utype>(rhs));
}



template <typename T>
typename std::enable_if<enable_bitwise_operators<T>::enable, T&>::type
  operator|=(T& lhs, T rhs) noexcept
{
  return lhs = lhs | rhs;
}



template <typename T>
typename std::enable_if<enable_bitwise_operators<T>::enable, T>::type operator&(
  T lhs, T rhs) noexcept
{
  using utype = typename std::underlying_type<T>::type;
  return static_cast<T>(static_cast<utype>(lhs) & static_cast<utype>(rhs));
}



template <typename T>
typename std::enable_if<enable_bitwise_operators<T>::enable, T&>::type
  operator&=(T& lhs, T rhs) noexcept
{
  return lhs = lhs & rhs;
}



template <typename T>
typename std::enable_if<enable_bitwise_operators<T>::enable, bool>::type
  check_all(T bitfield, T bits) noexcept
{
  return (bitfield & bits) == bits;
}



template <typename T>
typename std::enable_if<enable_bitwise_operators<T>::enable, bool>::type
  check_any(T bitfield, T bits) noexcept
{
  return (bitfield & bits) != T(0);
}



template <typename T>
typename std::enable_if<enable_bitwise_operators<T>::enable,
  std::ostream&>::type
  stream_bitfield(
    std::ostream& os, T bitfield, std::function<void(std::ostream&, T)> printer)
{
  using bitfield_type = typename std::underlying_type<T>::type;

  std::vector<T> bits_to_print;

  bitfield_type all_bits = static_cast<bitfield_type>(bitfield);
  if(all_bits == 0)
  {
    bits_to_print.push_back(T(0));
  }
  else
  {
    bitfield_type current_bit = 1;
    while(current_bit <= all_bits)
    {
      if(current_bit & all_bits)
      {
        bits_to_print.push_back(T(current_bit));
      }
      current_bit <<= 1;
    }
  }

  for(auto it = bits_to_print.rbegin(); it != bits_to_print.rend(); ++it)
  {
    if(it != bits_to_print.rbegin())
    {
      os << " | ";
    }
    printer(os, *it);
  }

  return os;
}

}  // namespace hou
