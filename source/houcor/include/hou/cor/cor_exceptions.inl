// Houzi Game Engine
// Copyright (c) 2018 Davide Corradi
// Licensed under the MIT license.

namespace hou
{

template <typename T>
invalid_enum<T>::invalid_enum(const std::string& path, uint line, T enum_value)
  : exception(path, line,
      format_string("Invalid enumeration value '%s'.",
        to_string(
          static_cast<typename std::underlying_type<T>::type>(enum_value))
          .c_str()))
{}

}  // namespace hou
