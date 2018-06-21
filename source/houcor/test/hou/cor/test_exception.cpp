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

class test_exception_death_test : public test_exception
{};



class exception_0_args : public exception
{
public:
  exception_0_args(const std::string& filename, uint line) noexcept;
};



exception_0_args::exception_0_args(
  const std::string& filename, uint line) noexcept
  : exception(filename, line, "No arguments.")
{}



class exception_2_args : public exception
{
public:
  exception_2_args(
    const std::string& filename, uint line, int num, char c) noexcept;
};



exception_2_args::exception_2_args(
  const std::string& filename, uint line, int num, char c) noexcept
  : exception(filename, line, format_string("Num %d, char %c", num, c))
{}

}  // namespace



TEST_F(test_exception, constructor)
{
  exception ex("file1.txt", 88u, "Message.");
  EXPECT_STREQ("file1.txt:88 - Message.", ex.what());
}



TEST_F(test_exception, file_name_trimming)
{
  exception ex("path/to/file1.txt", 88u, "Message.");
  EXPECT_STREQ("file1.txt:88 - Message.", ex.what());
}



TEST_F(test_exception, copy_constructor)
{
  auto ex1 = std::make_unique<exception>("file1.txt", 88u, "Message.");
  exception ex2(*ex1);
  ex1.reset();
  EXPECT_STREQ("file1.txt:88 - Message.", ex2.what());
}



#ifndef HOU_DISABLE_EXCEPTIONS
TEST_F(test_exception_death_test, expect_error_std_0_macro)
{
  EXPECT_ERROR_STD_0(throw std::exception(), std::exception);
}
#endif



#ifndef HOU_DISABLE_EXCEPTIONS
TEST_F(test_exception_death_test, expect_error_std_n_macro)
{
  EXPECT_ERROR_STD_N(
    throw std::runtime_error("message"), std::runtime_error, "message");
}
#endif



#ifndef HOU_DISABLE_EXCEPTIONS
TEST_F(test_exception_death_test, expect_error_0_macro)
{
  EXPECT_ERROR_0(throw exception_0_args("a", 2), exception_0_args);
}
#endif



#ifndef HOU_DISABLE_EXCEPTIONS
TEST_F(test_exception_death_test, expect_error_n_macro)
{
  EXPECT_ERROR_N(
    throw exception_2_args("a", 2, 88, 'b'), exception_2_args, 88, 'b');
}
#endif



TEST_F(test_exception_death_test, exit_with_error)
{
  EXPECT_EXIT(
    exit_with_error("Message."), ExitedWithCode(EXIT_FAILURE), "Message\\.");
}



TEST_F(test_exception_death_test, exit_with_error_macro)
{
  EXPECT_EXIT(HOU_EXIT_WITH_ERROR("Message."), ExitedWithCode(EXIT_FAILURE),
    ".*:.* - Message\\.");
}



TEST_F(test_exception_death_test, error)
{
  EXPECT_ERROR_STD_0(error<std::exception>(), std::exception);
  EXPECT_ERROR_STD_N(
    error<std::runtime_error>("Message."), std::runtime_error, "Message.");
  EXPECT_ERROR_STD_N(error<hou::exception>("luck.cpp", 88u, "Message."),
    hou::exception, "luck.cpp", 88u, "Message.");
}



TEST_F(test_exception_death_test, hou_error_std_0_macro)
{
  EXPECT_ERROR_STD_0(HOU_ERROR_STD_0(std::exception), std::exception);
}



TEST_F(test_exception_death_test, hou_error_std_n_macro)
{
  EXPECT_ERROR_STD_N(HOU_ERROR_STD_N(std::runtime_error, "Message."),
    std::runtime_error, "Message.");
}



TEST_F(test_exception_death_test, hou_error_0_macro)
{
  EXPECT_ERROR_0(HOU_ERROR_0(exception_0_args), exception_0_args);
}



TEST_F(test_exception_death_test, hou_error_n_macro)
{
  EXPECT_ERROR_N(
    HOU_ERROR_N(exception_2_args, 88, 'a'), exception_2_args, 88, 'a');
}



TEST_F(test_exception, hou_assert_macro_success)
{
  HOU_ASSERT(2 == 2);
}



TEST_F(test_exception_death_test, hou_assert_macro_failure)
{
  EXPECT_EXIT(HOU_ASSERT(0 == 2), ExitedWithCode(EXIT_FAILURE),
    ".*:.* - Assertion failed \\(0 == 2\\).");
}



TEST_F(test_exception, hou_check_std_0_macro_success)
{
  EXPECT_NO_ERROR(HOU_CHECK_STD_0(2 == 2, std::exception));
}



TEST_F(test_exception_death_test, hou_check_std_0_macro_failure)
{
  EXPECT_ERROR_STD_0(HOU_CHECK_STD_0(0 == 2, std::exception), std::exception);
}



TEST_F(test_exception, hou_check_std_n_macro_success)
{
  EXPECT_NO_ERROR(HOU_CHECK_STD_N(2 == 2, std::runtime_error, "Message."));
}



TEST_F(test_exception_death_test, hou_check_std_n_macro_failure)
{
  EXPECT_ERROR_STD_N(HOU_CHECK_STD_N(0 == 2, std::runtime_error, "Message."),
    std::runtime_error, "Message.");
}



TEST_F(test_exception, hou_check_0_macro_success)
{
  EXPECT_NO_ERROR(HOU_CHECK_0(2 == 2, exception_0_args));
}



TEST_F(test_exception_death_test, hou_check_0_macro_failure)
{
  EXPECT_ERROR_0(HOU_CHECK_0(0 == 2, exception_0_args), exception_0_args);
}



TEST_F(test_exception, hou_check_n_macro_success)
{
  EXPECT_NO_ERROR(HOU_CHECK_N(2 == 2, exception_2_args, 88, 'a'));
}



TEST_F(test_exception_death_test, hou_check_n_macro_failure)
{
  EXPECT_ERROR_N(
    HOU_CHECK_N(0 == 2, exception_2_args, 88, 'a'), exception_2_args, 88, 'a');
}



TEST_F(test_exception, hou_dev_assert_macro_success)
{
  HOU_DEV_ASSERT(2 == 2);
}



TEST_F(test_exception_death_test, hou_dev_assert_macro_failure)
{
#ifdef HOU_DEBUG
  EXPECT_EXIT(HOU_DEV_ASSERT(0 == 2), ExitedWithCode(EXIT_FAILURE),
    ".*:.* - Assertion failed \\(0 == 2\\)\\.");
#else
  EXPECT_NO_ERROR(HOU_DEV_ASSERT(0 == 2));
#endif
}



TEST_F(test_exception_death_test, hou_unreachable_macro)
{
  EXPECT_EXIT(HOU_UNREACHABLE(), ExitedWithCode(EXIT_FAILURE),
    ".*:.* - Unreachable code path\\.");
}
