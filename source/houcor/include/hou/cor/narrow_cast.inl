// Houzi Game Engine
// Copyright (c) 2018 Davide Corradi
// Licensed under the MIT license.



namespace hou
{


template <typename T, typename U>
bool check_matching_sign<T, U>::check(const T& t, const U& u)
{
  return (t < T(0)) == (u < U(0));
}



template <typename To, typename From>
constexpr To narrow_cast(const From& from)
{
  using is_same_signedness = is_same_signedness<To, From>;
  using check_matching_sign = check_matching_sign<To, From>;

  auto to = static_cast<To>(from);

  HOU_CHECK_0(static_cast<From>(to) == from, narrowing_error);
  HOU_CHECK_0(is_same_signedness::value || check_matching_sign::check(to, from),
    narrowing_error);

  return to;
}

}  // namespace hou
