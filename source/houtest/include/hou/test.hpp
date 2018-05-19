// Houzi Multimedia Library
// Copyright (c) 2016-2017 Davide Corradi
// Licensed under the MIT license. See license.md for more details.

#ifndef HOU_TEST
#define HOU_TEST

#include "hou/cor/assertions.hpp"
#include "hou/cor/exception.hpp"
#include "hou/cor/std_string.hpp"

#include <cstring>
#include <gmock/gmock.h>
#include <gtest/gtest.h>
#include <limits>
#include <sstream>
#include <string>



// Error assertions

inline std::string get_exception_msg_regex(const hou::exception& ex)
{
  std::string what_str = ex.what();
  return std::string(".*:.* - ")
    + hou::escape_regex(what_str.substr(what_str.find_first_not_of(
        ' ', 1 + what_str.find_first_of('-', what_str.find_first_of(':')))));
}

inline std::string get_exception_msg_regex(const std::exception& ex)
{
  return hou::escape_regex(ex.what());
}

#if defined(HOU_DISABLE_EXCEPTIONS)

#define EXPECT_ERROR_STD_0(statement, exception_type)                          \
  do                                                                           \
  {                                                                            \
    EXPECT_DEATH(                                                              \
      statement, get_exception_msg_regex(exception_type()).c_str());           \
  } while(false)

#define EXPECT_ERROR_TEMPLATE(statement, exception_type, ...)                  \
  do                                                                           \
  {                                                                            \
    EXPECT_DEATH(statement,                                                    \
      get_exception_msg_regex(exception_type(__VA_ARGS__)).c_str());           \
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
        ::testing::MatchesRegex(get_exception_msg_regex(exception_type())));   \
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
        ::testing::MatchesRegex(                                               \
          get_exception_msg_regex(exception_type(__VA_ARGS__))));              \
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

#define EXPECT_PRECOND_ERROR(statement)                                        \
  EXPECT_ERROR_0(statement, precondition_violation)

#define EXPECT_POSTCOND_ERROR(statement)                                       \
  EXPECT_ERROR_0(statement, postcondition_violation)

#define EXPECT_INVARIANT_ERROR(statement)                                      \
  EXPECT_ERROR_0(statement, invariant_violation)

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



// Array check assertion.

#define EXPECT_ARRAY_EQ(lhs, rhs, size)                                        \
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

#define EXPECT_ARRAY_CLOSE(lhs, rhs, size, prec)                               \
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

#define EXPECT_ARRAY_FLOAT_CLOSE(lhs, rhs, size)                               \
  EXPECT_ARRAY_CLOSE(lhs, rhs, size, std::numeric_limits<float>::epsilon())



// Floating point comparisons assertions.

#define EXPECT_CLOSE(lhs, rhs, prec)                                           \
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

#define EXPECT_FLOAT_CLOSE(lhs, rhs)                                           \
  EXPECT_CLOSE(lhs, rhs, std::numeric_limits<float>::epsilon())



// Output stream operator assertions.

#define EXPECT_OUTPUT(expected_string, object)                                 \
  {                                                                            \
    std::stringstream stream;                                                  \
    stream << object;                                                          \
    EXPECT_STREQ(expected_string, stream.str().c_str())                        \
      << "Error in operator<<";                                                \
  }

#endif  // HOU_TEST
