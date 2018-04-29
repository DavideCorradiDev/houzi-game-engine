// Houzi Multimedia Library
// Copyright (c) 2016-2017 Davide Corradi
// Licensed under the MIT license. See license.md for more details.

#ifndef HOU_TEST
#define HOU_TEST

#include "hou/cor/cor_error.hpp"
#include "hou/cor/std_string.hpp"

#include <cstring>
#include <gmock/gmock.h>
#include <gtest/gtest.h>
#include <limits>
#include <sstream>
#include <string>



// To be used in expressions passed as arguments to macros to avoid issues
// when the macro is expanded.
#define HOU_COMMA ,



#if defined(HOU_DISABLE_EXCEPTIONS)
  #define HOU_EXPECT_ERROR(statement, exception_type, message) \
  { \
    std::stringstream expectedOutput; \
    expectedOutput << #exception_type << " -.*" << hou::format_regex(message) \
      << ".*"; \
    EXPECT_DEATH(statement, expectedOutput.str().c_str()); \
  }
#else
  #include <stdexcept>
  #define HOU_EXPECT_ERROR(statement, exception_type, message) \
  { \
    try \
    { \
      statement; \
      ADD_FAILURE() << "Expected: " #statement " throws an exception of type " \
        #exception_type ".\n  Actual: it throws nothing."; \
    } \
    catch(const exception_type& e) \
    { \
      std::stringstream expectedOutput; \
      expectedOutput << ".*" << hou::format_regex(message) << ".*"; \
      EXPECT_THAT(e.what() \
        , ::testing::MatchesRegex(expectedOutput.str().c_str())); \
    } \
    catch(...) \
    { \
      ADD_FAILURE() << "Expected: " #statement " throws an exception of type " \
        #exception_type ".\n  Actual: it throws a different type."; \
    } \
  }
#endif



#define HOU_EXPECT_PRECONDITION(statement) \
  HOU_EXPECT_ERROR(statement, std::logic_error, get_text(cor_error::pre_condition));



#define HOU_EXPECT_POSTCONDITION(statement) \
  HOU_EXPECT_ERROR(statement, std::logic_error, get_text(cor_error::post_condition));



#define HOU_EXPECT_ARRAY_EQ(lhs, rhs, size) \
do \
{ \
  for(size_t macro_i = 0; macro_i < size; ++macro_i) \
  { \
    if(lhs[macro_i] != rhs[macro_i]) \
    { \
      std::stringstream ph_stream; \
      ph_stream \
        << "      Expected: " << #lhs << "[" << macro_i << "]\n" \
        << "      Which is: " << lhs[macro_i] << "\n" \
        << "To be equal to: " << #rhs << "[" << macro_i << "]\n" \
        << "      Which is: " << rhs[macro_i]; \
      ADD_FAILURE() << ph_stream.str(); \
    } \
    else \
    { \
      SUCCEED(); \
    } \
  } \
} \
while(false)




#define HOU_EXPECT_ARRAY_CLOSE(lhs, rhs, size, prec) \
do \
{ \
  for(size_t macro_i = 0; macro_i < size; ++macro_i) \
  { \
    if(!close(lhs[macro_i], rhs[macro_i], prec)) \
    { \
      std::stringstream ph_stream; \
      ph_stream \
        << "      Expected: " << #lhs << "[" << macro_i << "]\n" \
        << "      Which is: " << lhs[macro_i] << "\n" \
        << "To be close to: " << #rhs << "[" << macro_i << "]\n" \
        << "      Which is: " << rhs[macro_i] << "\n" \
        << "With precision: " << prec; \
      ADD_FAILURE() << ph_stream.str(); \
    } \
    else \
    { \
      SUCCEED(); \
    } \
  } \
} \
while(false)



#define HOU_EXPECT_ARRAY_FLOAT_CLOSE(lhs, rhs, size) \
  HOU_EXPECT_ARRAY_CLOSE(lhs, rhs, size, std::numeric_limits<float>::epsilon())



#define HOU_EXPECT_CLOSE(lhs, rhs, prec) \
do \
{ \
  if(!close(lhs, rhs, prec)) \
  { \
    std::stringstream ph_stream; \
    ph_stream \
      << "      Expected: " << #lhs << "\n" \
      << "      Which is: " << lhs << "\n" \
      << "To be close to: " << #rhs << "\n" \
      << "      Which is: " << rhs << "\n" \
      << "With precision: " << prec; \
    ADD_FAILURE() << ph_stream.str(); \
  } \
  else \
  { \
    SUCCEED(); \
  } \
} \
while(false)



#define HOU_EXPECT_FLOAT_CLOSE(lhs, rhs) \
  HOU_EXPECT_CLOSE(lhs, rhs, std::numeric_limits<float>::epsilon())



#define HOU_EXPECT_OUTPUT(expected_string, object) \
{ \
  std::stringstream ph_stream; \
  ph_stream << object; \
  EXPECT_STREQ(expected_string, ph_stream.str().c_str()) \
    << "Error in operator<<"; \
}



#endif // HOU_TEST
