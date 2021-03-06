// Houzi Multimedia Library
// Copyright (c) 2016-2017 Davide Corradi
// Licensed under the MIT license. See license.md for more details.

#ifndef HOU_TEST
#define HOU_TEST

#include "hou/cor/assertions.hpp"
#include "hou/cor/exception.hpp"
#include "hou/cor/std_string.hpp"

#include <gmock/gmock.h>
#include <gtest/gtest.h>

#include <cstring>
#include <limits>
#include <sstream>



// Message printing.
#define PRINT_MSG(message)                                                     \
  do                                                                           \
  {                                                                            \
    ::std::cout << "[          ] " << message << "\n";                         \
  } while(false)



// Error assertions

inline std::string get_exception_msg_regex(const hou::exception& ex)
{
  std::string what_str = ex.what();
  return std::string(".*:.* - ")
    + hou::escape_regex(what_str.substr(what_str.find_first_not_of(
        ' ', 1 + what_str.find_first_of('-', what_str.find_first_of(':')))));
}

inline std::string get_exception_msg_regex(const hou::assertion_violation& ex)
{
  // Assertions need a special treatment since they store the violated
  // condition in the error message.
  // Since this can't be easily known beforehand in tests, the condition will
  // not be checked in the test, only if the rest of the message is correct.
  std::string what_str = ex.what();
  what_str = what_str.substr(what_str.find_first_not_of(
    ' ', 1 + what_str.find_first_of('-', what_str.find_first_of(':'))));
  what_str = what_str.substr(0u, what_str.find_first_of('('));

  return std::string(".*:.* - ") + hou::escape_regex(what_str) + "\\(.*\\)\\.";
}

inline std::string get_exception_msg_regex(const std::exception& ex)
{
  return hou::escape_regex(ex.what());
}



#if defined(GTEST_HAS_DEATH_TEST)

#define EXPECT_EXIT_IF_SUPPORTED(statement, arg, message)                      \
  EXPECT_EXIT(statement, arg, message)

#else

#define EXPECT_EXIT_IF_SUPPORTED(statement, arg, message)                      \
  do                                                                           \
  {                                                                            \
    PRINT_MSG("[WARNING] EXPECT_EXIT assertion skipped because unsupported."); \
  } while(false)

#endif



#if defined(HOU_DISABLE_EXCEPTIONS)

#define EXPECT_ERROR_STD_0(statement, exception_type)                          \
  do                                                                           \
  {                                                                            \
    EXPECT_EXIT_IF_SUPPORTED(statement,                                        \
      ::testing::ExitedWithCode(EXIT_FAILURE),                                 \
      get_exception_msg_regex(exception_type()).c_str());                      \
  } while(false)

#define EXPECT_ERROR_TEMPLATE(statement, exception_type, ...)                  \
  do                                                                           \
  {                                                                            \
    EXPECT_EXIT_IF_SUPPORTED(statement,                                        \
      ::testing::ExitedWithCode(EXIT_FAILURE),                                 \
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
  EXPECT_ERROR_N(statement, precondition_violation, "*")

#define EXPECT_POSTCOND_ERROR(statement)                                       \
  EXPECT_ERROR_N(statement, postcondition_violation, "*")

#define EXPECT_INVARIANT_ERROR(statement)                                      \
  EXPECT_ERROR_N(statement, invariant_violation, "*")



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
      if(!::hou::close(lhs[macro_i], rhs[macro_i], prec))                      \
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
    if(!::hou::close(lhs, rhs, prec))                                          \
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
    stream << (object);                                                        \
    EXPECT_STREQ(expected_string, stream.str().c_str())                        \
      << "Error in operator<<";                                                \
  }



// Skip test.
#define SKIP(message)                                                          \
  do                                                                           \
  {                                                                            \
    PRINT_MSG(                                                                 \
      ::hou::format_string("[INFO] Test skipped. %s", message).c_str());       \
    return;                                                                    \
  } while(false)

#define SKIP_IF(condition, message)                                            \
  do                                                                           \
  {                                                                            \
    if(condition)                                                              \
    {                                                                          \
      SKIP(::hou::format_string(                                               \
        "Skipping condition: " #condition ". %s", message)                     \
             .c_str());                                                        \
    }                                                                          \
  } while(false)

#endif  // HOU_TEST
