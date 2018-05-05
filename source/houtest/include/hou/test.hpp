// Houzi Multimedia Library
// Copyright (c) 2016-2017 Davide Corradi
// Licensed under the MIT license. See license.md for more details.

#ifndef HOU_TEST
#define HOU_TEST

#include "hou/cor/cor_error.hpp"
#include "hou/cor/exception.hpp"
#include "hou/cor/std_string.hpp"

#include <cstring>
#include <gmock/gmock.h>
#include <gtest/gtest.h>
#include <limits>
#include <sstream>
#include <string>



// Error assertions
inline std::string get_exception_message(const hou::exception& ex)
{
  std::string what_str = ex.what();
  return what_str.substr(what_str.find_first_not_of(
    ' ', 1 + what_str.find_first_of('-', what_str.find_first_of(':'))));
}

inline std::string get_exception_message(const std::exception& ex)
{
  return ex.what();
}

inline std::string get_no_exception_message_regex(
  const std::string& ex_name, const hou::exception& ex)
{
  std::stringstream ss;
  ss << ex_name << " - .*:.* - "
     << hou::escape_regex(get_exception_message(ex));
  return ss.str();
}

inline std::string get_no_exception_message_regex(
  const std::string& ex_name, const std::exception& ex)
{
  std::stringstream ss;
  ss << ex_name << " - " << hou::escape_regex(get_exception_message(ex));
  return ss.str();
}

#if defined(HOU_DISABLE_EXCEPTIONS)

#define EXPECT_ERROR_STD_0(statement, exception_type)                          \
  do                                                                           \
  {                                                                            \
    EXPECT_DEATH(statement,                                                    \
      get_no_exception_message_regex(#exception_type, exception_type())        \
        .c_str());                                                             \
  } while(false)

#define EXPECT_ERROR_TEMPLATE(statement, exception_type, ...)                  \
  do                                                                           \
  {                                                                            \
    EXPECT_DEATH(statement,                                                    \
      get_no_exception_message_regex(                                          \
        #exception_type, exception_type(__VA_ARGS__))                          \
        .c_str());                                                             \
  } while(false)

#else

#define NO_ERR_FAILURE(statement, exception_type)                              \
  ADD_FAILURE() << "Expected: " #statement                                     \
                   " throws an exception of type " #exception_type             \
                   ".\n  Actual: it throws nothing."

#define WRONG_ERR_FAILURE(statement, exception_type)                           \
  ADD_FAILURE() << "Expected: " #statement                                     \
                   " throws an exception of type " #exception_type             \
                   ".\n  Actual: it throws a different type.";

#define EXPECT_ERROR_STD_0(statement, exception_type)                          \
  do                                                                           \
  {                                                                            \
    try                                                                        \
    {                                                                          \
      statement;                                                               \
      NO_ERR_FAILURE(statement, exception_type);                               \
    }                                                                          \
    catch(const exception_type& e)                                             \
    {                                                                          \
      EXPECT_THAT(e.what(),                                                    \
        ::testing::MatchesRegex(get_exception_message(exception_type())));     \
    }                                                                          \
    catch(...)                                                                 \
    {                                                                          \
      WRONG_ERR_FAILURE(statement, exception_type);                            \
    }                                                                          \
  } while(false)

#define EXPECT_ERROR_TEMPLATE(statement, exception_type, ...)                  \
  do                                                                           \
  {                                                                            \
    try                                                                        \
    {                                                                          \
      statement;                                                               \
      NO_ERR_FAILURE(statement, exception_type);                               \
    }                                                                          \
    catch(const exception_type& e)                                             \
    {                                                                          \
      EXPECT_THAT(e.what(),                                                    \
        ::testing::MatchesRegex(std::string(".*")                              \
          + get_exception_message(exception_type(__VA_ARGS__))));              \
    }                                                                          \
    catch(...)                                                                 \
    {                                                                          \
      WRONG_ERR_FAILURE(statement, exception_type);                            \
    }                                                                          \
  } while(false)

#endif

#define EXPECT_ERROR_STD_N(statement, exception_type, ...)                     \
  EXPECT_ERROR_TEMPLATE(statement, exception_type, __VA_ARGS__)

#define EXPECT_ERROR_0(statement, exception_type)                              \
  EXPECT_ERROR_TEMPLATE(statement, exception_type, "", 0)

#define EXPECT_ERROR_N(statement, exception_type, ...)                         \
  EXPECT_ERROR_TEMPLATE(statement, exception_type, "", 0, __VA_ARGS__)

#if defined(HOU_DISABLE_EXCEPTIONS)
#define EXPECT_NO_ERROR(statement)                                             \
  do                                                                           \
  {                                                                            \
    statement;                                                                 \
    SUCCEED();                                                                 \
  } while(false)
#else
#define EXPECT_NO_ERROR(statement)                                             \
  do                                                                           \
  {                                                                            \
    try                                                                        \
    {                                                                          \
      statement;                                                               \
    }                                                                          \
    catch(...)                                                                 \
    {                                                                          \
      ADD_FAILURE() << "Expected: " #statement                                 \
                       " throws nothing.\n  Actual: it throws.";               \
    }                                                                          \
  } while(false)
#endif



#if defined(HOU_DISABLE_EXCEPTIONS)
#define DEPRECATED_HOU_EXPECT_ERROR(statement, exception_type, message)        \
  {                                                                            \
    std::stringstream expected_output;                                         \
    expected_output << #exception_type << " -.*" << hou::escape_regex(message) \
                    << ".*";                                                   \
    EXPECT_DEATH(statement, expected_output.str().c_str());                    \
  }
#else
#include <stdexcept>
#define DEPRECATED_HOU_EXPECT_ERROR(statement, exception_type, message)        \
  {                                                                            \
    try                                                                        \
    {                                                                          \
      statement;                                                               \
      ADD_FAILURE() << "Expected: " #statement                                 \
                       " throws an exception of type " #exception_type         \
                       ".\n  Actual: it throws nothing.";                      \
    }                                                                          \
    catch(const exception_type& e)                                             \
    {                                                                          \
      std::stringstream expected_output;                                       \
      expected_output << ".*" << hou::escape_regex(message) << ".*";           \
      EXPECT_THAT(                                                             \
        e.what(), ::testing::MatchesRegex(expected_output.str().c_str()));     \
    }                                                                          \
    catch(...)                                                                 \
    {                                                                          \
      ADD_FAILURE() << "Expected: " #statement                                 \
                       " throws an exception of type " #exception_type         \
                       ".\n  Actual: it throws a different type.";             \
    }                                                                          \
  }
#endif



#define HOU_EXPECT_PRECONDITION(statement)                                     \
  DEPRECATED_HOU_EXPECT_ERROR(                                                 \
    statement, std::logic_error, get_text(cor_error::pre_condition));



#define HOU_EXPECT_POSTCONDITION(statement)                                    \
  DEPRECATED_HOU_EXPECT_ERROR(                                                 \
    statement, std::logic_error, get_text(cor_error::post_condition));



// Array check assertion.
#define HOU_EXPECT_ARRAY_EQ(lhs, rhs, size)                                    \
  do                                                                           \
  {                                                                            \
    for(size_t macro_i = 0; macro_i < size; ++macro_i)                         \
    {                                                                          \
      if(lhs[macro_i] != rhs[macro_i])                                         \
      {                                                                        \
        std::stringstream stream;                                              \
        stream << "      Expected: " << #lhs << "[" << macro_i << "]\n"        \
               << "      Which is: " << lhs[macro_i] << "\n"                   \
               << "To be equal to: " << #rhs << "[" << macro_i << "]\n"        \
               << "      Which is: " << rhs[macro_i];                          \
        ADD_FAILURE() << stream.str();                                         \
      }                                                                        \
      else                                                                     \
      {                                                                        \
        SUCCEED();                                                             \
      }                                                                        \
    }                                                                          \
  } while(false)



#define HOU_EXPECT_ARRAY_CLOSE(lhs, rhs, size, prec)                           \
  do                                                                           \
  {                                                                            \
    for(size_t macro_i = 0; macro_i < size; ++macro_i)                         \
    {                                                                          \
      if(!close(lhs[macro_i], rhs[macro_i], prec))                             \
      {                                                                        \
        std::stringstream stream;                                              \
        stream << "      Expected: " << #lhs << "[" << macro_i << "]\n"        \
               << "      Which is: " << lhs[macro_i] << "\n"                   \
               << "To be close to: " << #rhs << "[" << macro_i << "]\n"        \
               << "      Which is: " << rhs[macro_i] << "\n"                   \
               << "With precision: " << prec;                                  \
        ADD_FAILURE() << stream.str();                                         \
      }                                                                        \
      else                                                                     \
      {                                                                        \
        SUCCEED();                                                             \
      }                                                                        \
    }                                                                          \
  } while(false)



#define HOU_EXPECT_ARRAY_FLOAT_CLOSE(lhs, rhs, size)                           \
  HOU_EXPECT_ARRAY_CLOSE(lhs, rhs, size, std::numeric_limits<float>::epsilon())



// Floating point comparisons assertions.
#define HOU_EXPECT_CLOSE(lhs, rhs, prec)                                       \
  do                                                                           \
  {                                                                            \
    if(!close(lhs, rhs, prec))                                                 \
    {                                                                          \
      std::stringstream stream;                                                \
      stream << "      Expected: " << #lhs << "\n"                             \
             << "      Which is: " << lhs << "\n"                              \
             << "To be close to: " << #rhs << "\n"                             \
             << "      Which is: " << rhs << "\n"                              \
             << "With precision: " << prec;                                    \
      ADD_FAILURE() << stream.str();                                           \
    }                                                                          \
    else                                                                       \
    {                                                                          \
      SUCCEED();                                                               \
    }                                                                          \
  } while(false)



#define HOU_EXPECT_FLOAT_CLOSE(lhs, rhs)                                       \
  HOU_EXPECT_CLOSE(lhs, rhs, std::numeric_limits<float>::epsilon())



#define HOU_EXPECT_OUTPUT(expected_string, object)                             \
  {                                                                            \
    std::stringstream stream;                                                  \
    stream << object;                                                          \
    EXPECT_STREQ(expected_string, stream.str().c_str())                        \
      << "Error in operator<<";                                                \
  }

#endif  // HOU_TEST
