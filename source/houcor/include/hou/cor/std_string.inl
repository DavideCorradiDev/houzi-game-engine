// Houzi Game Engine
// Copyright (c) 2018 Davide Corradi
// Licensed under the MIT license.

namespace hou
{

template <typename... Args>
std::string format_string(const std::string& s, Args... args)
{
  // The +1 is for an extra space for null terminating char in the buffer.
  size_t size = std::snprintf(nullptr, 0, s.c_str(), args...) + 1;
  std::vector<char> buf(size);
  std::snprintf(&buf[0], size, s.c_str(), args...);
  // The -1 is to avoid saving the null terminating char in the returned string.
  return std::string(buf.begin(), buf.end() - 1);
}



template <typename OutputIterator>
OutputIterator split_string(
  const std::string& s, char delimiter, OutputIterator out)
{
  std::istringstream ss(s);
  while(!ss.eof())
  {
    std::string item;
    std::getline(ss, item, delimiter);
    *out = item;
    ++out;
  }
  return out;
}



template <typename T>
std::string to_string(const T& obj)
{
  std::stringstream ss;
  ss << obj;
  return ss.str();
}

}  // namespace hou
