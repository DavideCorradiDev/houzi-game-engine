// Houzi Game Engine
// Copyright (c) 2018 Davide Corradi
// Licensed under the MIT license.



namespace hou
{

template <typename To, typename From, typename Enable>
constexpr To narrow_cast(const From& from)
{
  using is_same_signedness = is_same_signedness<To, From>;

  auto to = static_cast<To>(from);

  HOU_CHECK_0(static_cast<From>(to) == from, narrowing_error);
  HOU_CHECK_0((is_same_signedness::value || ((to < To(0)) == (from < From(0)))),
    narrowing_error);

  return to;
}

}  // namespace hou
