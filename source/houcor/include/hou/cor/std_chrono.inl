namespace std
{

template <typename Rep>
std::ostream& operator<<(
  std::ostream& os, std::chrono::duration<Rep, std::nano> d)
{
  return os << d.count() << " ns";
}



template <typename Rep>
std::ostream& operator<<(
  std::ostream& os, std::chrono::duration<Rep, std::micro> d)
{
  return os << d.count() << " us";
}



template <typename Rep>
std::ostream& operator<<(
  std::ostream& os, std::chrono::duration<Rep, std::milli> d)
{
  return os << d.count() << " ms";
}



template <typename Rep>
std::ostream& operator<<(
  std::ostream& os, std::chrono::duration<Rep, std::ratio<1>> d)
{
  return os << d.count() << " s";
}



template <typename Rep>
std::ostream& operator<<(
  std::ostream& os, std::chrono::duration<Rep, std::ratio<60>> d)
{
  return os << d.count() << " m";
}



template <typename Rep>
std::ostream& operator<<(
  std::ostream& os, std::chrono::duration<Rep, std::ratio<3600>> d)
{
  return os << d.count() << " h";
}

}  // namespace hou
