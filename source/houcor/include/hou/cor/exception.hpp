// Houzi Game Engine
// Copyright (c) 2018 Davide Corradi
// Licensed under the MIT license.

#ifndef HOU_COR_EXCEPTION_HPP
#define HOU_COR_EXCEPTION_HPP

#include "hou/cor/cor_export.hpp"

#include "hou/cor/basic_types.hpp"

#include <memory>
#include <stdexcept>



namespace hou
{

namespace prv
{
HOU_COR_API std::string format_error_message(
  const std::string& path, uint line, const std::string& message);
}

class HOU_COR_API exception : public std::exception
{
public:
  exception(const std::string& path, uint line, const std::string& message);

  const char* what() const noexcept final;

private:
  // The message string is reference counted to avoid allocation in case
  // of object copies.
  std::shared_ptr<std::string> m_message;
};

void HOU_COR_API terminate(const std::string& message) noexcept;



#define HOU_TERMINATE(message)                                                 \
  ::hou::terminate(                                                            \
    ::hou::prv::format_error_message(__FILE__, __LINE__, message));

#ifdef HOU_DISABLE_EXCEPTIONS

#define HOU_THROW_STD_0(exception_type)                                        \
  do                                                                           \
  {                                                                            \
    ::hou::terminate(std::string(#exception_type) + std::string(u8" - ")       \
      + exception_type().what());                                              \
  } while(false)

#define HOU_THROW_TEMPLATE(exception_type, ...)                                \
  do                                                                           \
  {                                                                            \
    ::hou::terminate(std::string(#exception_type) + std::string(u8" - ")       \
      + exception_type(__VA_ARGS__).what());                                   \
  } while(false)

#else

#define HOU_THROW_STD_0(exception_type)                                        \
  do                                                                           \
  {                                                                            \
    throw exception_type();                                                    \
  } while(false)

#define HOU_THROW_TEMPLATE(exception_type, ...)                                \
  do                                                                           \
  {                                                                            \
    throw exception_type(__VA_ARGS__);                                         \
  } while(false)

#endif

#define HOU_THROW_STD_N(exception_type, ...)                                   \
  HOU_THROW_TEMPLATE(exception_type, __VA_ARGS__)

#define HOU_THROW_0(exception_type)                                            \
  HOU_THROW_TEMPLATE(exception_type, __FILE__, __LINE__)

#define HOU_THROW_N(exception_type, ...)                                       \
  HOU_THROW_TEMPLATE(exception_type, __FILE__, __LINE__, __VA_ARGS__)

#define HOU_CHECK_TEMPLATE(condition, failure_action)                          \
  do                                                                           \
  {                                                                            \
    if(!(condition))                                                           \
    {                                                                          \
      failure_action;                                                          \
    }                                                                          \
  } while(false)

#define HOU_CHECK_STD_0(condition, exception_type)                             \
  HOU_CHECK_TEMPLATE(condition, HOU_THROW_STD_0(exception_type))

#define HOU_CHECK_STD_N(condition, exception_type, ...)                        \
  HOU_CHECK_TEMPLATE(condition, HOU_THROW_STD_N(exception_type, __VA_ARGS__))

#define HOU_CHECK_0(condition, exception_type)                                 \
  HOU_CHECK_TEMPLATE(condition, HOU_THROW_0(exception_type))

#define HOU_CHECK_N(condition, exception_type, ...)                            \
  HOU_CHECK_TEMPLATE(condition, HOU_THROW_N(exception_type, __VA_ARGS__))

#ifdef NDEBUG
#define HOU_DEV_CHECK_TEMPLATE(condition, failure_action)
#else
#define HOU_DEV_CHECK_TEMPLATE(condition, failure_action)                      \
  HOU_CHECK_TEMPLATE(condition, failure_action)
#endif

#define HOU_DEV_CHECK_STD_0(condition, exception_type)                         \
  HOU_DEV_CHECK_TEMPLATE(condition, HOU_THROW_STD_0(exception_type))

#define HOU_DEV_CHECK_STD_N(condition, exception_type, ...)                    \
  HOU_DEV_CHECK_TEMPLATE(                                                      \
    condition, HOU_THROW_STD_N(exception_type, __VA_ARGS__))

#define HOU_DEV_CHECK_0(condition, exception_type)                             \
  HOU_DEV_CHECK_TEMPLATE(condition, HOU_THROW_0(exception_type))

#define HOU_DEV_CHECK_N(condition, exception_type, ...)                        \
  HOU_DEV_CHECK_TEMPLATE(condition, HOU_THROW_N(exception_type, __VA_ARGS__))


}  // namespace hou

#endif
