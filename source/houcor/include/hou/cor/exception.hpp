// Houzi Game Engine
// Copyright (c) 2018 Davide Corradi
// Licensed under the MIT license.

#ifndef HOU_COR_EXCEPTION_HPP
#define HOU_COR_EXCEPTION_HPP

#include "hou/cor/cor_export.hpp"

#include "hou/cor/basic_static_string.hpp"
#include "hou/cor/basic_types.hpp"

#include <exception>



namespace hou
{

class HOU_COR_API exception : public std::exception
{
public:
  static constexpr size_t max_filename_length = 256u;
  using filename_type = static_string<max_filename_length>;

public:
  exception(const filename_type& filename, uint line) noexcept;

  const char* what() const noexcept override;
  std::string message() const;

protected:
  virtual std::string message_extension() const;

private:
  static const std::string what_msg;

private:
  filename_type m_filename;
  uint m_line;
};



#define HOU_TERMINATE(message) \
  do \
  { \
    std::cerr << message << std::endl; \
    std::terminate(); \
  } while(false)



#if defined(HOU_DISABLE_EXCEPTIONS)

#define HOU_THROW_0(exception_type) \
  do \
  { \
    HOU_TERMINATE(std::string(#exception_type) + std::string(u8" - ") \
      + exception_type(__FILE__, __LINE__).message()); \
  } while(false)

#define HOU_THROW_N(exception_type, ...) \
  do \
  { \
    HOU_TERMINATE(std::string(#exception_type) + std::string(u8" - ") \
      + exception_type(__FILE__, __LINE__, __VA_ARGS__).message()); \
  } while(false)

#else

#define HOU_THROW_0(exception_type) \
  do \
  { \
    throw exception_type(__FILE__, __LINE__); \
  } while(false)

#define HOU_THROW_N(exception_type, ...) \
  do \
  { \
    throw exception_type(__FILE__, __LINE__, __VA_ARGS__); \
  } while(false)

#endif

}  // namespace hou

#endif
