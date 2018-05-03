// Houzi Game Engine
// Copyright (c) 2018 Davide Corradi
// Licensed under the MIT license.

#include "hou/test.hpp"

#include "hou/cor/exception.hpp"

using namespace hou;
using namespace testing;



namespace
{

class test_exception : public Test
{};



class exception_with_args : public exception
{
public:
  exception_with_args(
    const filename_type& filename, uint line, int value, char c) noexcept;
  const char* what() const noexcept override;

protected:
  std::string message_extension() const override;

private:
  static const std::string what_msg;

private:
  int m_value;
  char m_char;
};



exception_with_args::exception_with_args(
  const filename_type& filename, uint line, int value, char c) noexcept
  : exception(filename, line)
  , m_value(value)
  , m_char(c)
{}



const char* exception_with_args::what() const noexcept
{
  return what_msg.c_str();
}



std::string exception_with_args::message_extension() const
{
  return format_string(what_msg, m_value, m_char);
}



const std::string exception_with_args::what_msg
  = u8"Dummy exception with value %d and char %c.";

}  // namespace



TEST_F(test_exception, constructor)
{
  exception ex("file1.txt", 88u);

  EXPECT_STREQ("A generic error has been encountered.", ex.what());
  EXPECT_EQ(
    "file1.txt:88 - A generic error has been encountered.", ex.message());
}



TEST_F(test_exception, hou_throw_0_macro)
{
  HOU_THROW_0(exception);
}



TEST_F(test_exception, hou_throw_n_macro)
{
  HOU_THROW_N(exception_with_args, 3, 'a');
}
