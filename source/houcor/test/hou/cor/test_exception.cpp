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



TEST_F(test_exception, copy_constructor)
{
  auto ex1 = std::make_unique<exception>("file1.txt", 88u, "Message.");
  exception ex2(*ex1);
  ex1.reset();
  EXPECT_STREQ("file1.txt:88 - Message.", ex2.what());
}



TEST_F(test_exception_death_test, terminate)
{
  EXPECT_DEATH(terminate("Message."), "Message.");
}



TEST_F(test_exception_death_test, terminate_macro)
{
  EXPECT_DEATH(HOU_TERMINATE("Message."), ".*:.* - Message.");
}


#ifndef HOU_DISABLE_EXCEPTIONS
TEST_F(test_exception_death_test, expect_throw_std_0_macro)
{
  EXPECT_THROW_STD_0(throw std::exception(), std::exception);
}
#endif



#ifndef HOU_DISABLE_EXCEPTIONS
TEST_F(test_exception_death_test, expect_throw_std_n_macro)
{
  EXPECT_THROW_STD_N(
    throw std::runtime_error("message"), std::runtime_error, "message");
}
#endif



#ifndef HOU_DISABLE_EXCEPTIONS
TEST_F(test_exception_death_test, expect_throw_0_macro)
{
  EXPECT_THROW_0(throw exception_0_args("a", 2), exception_0_args);
}
#endif



#ifndef HOU_DISABLE_EXCEPTIONS
TEST_F(test_exception_death_test, expect_throw_n_macro)
{
  EXPECT_THROW_N(
    throw exception_2_args("a", 2, 88, 'b'), exception_2_args, 88, 'b');
}
#endif



TEST_F(test_exception_death_test, hou_throw_std_0_macro)
{
  EXPECT_THROW_STD_0(HOU_THROW_STD_0(std::exception), std::exception);
}



TEST_F(test_exception_death_test, hou_throw_std_n_macro)
{
  EXPECT_THROW_STD_N(HOU_THROW_STD_N(std::runtime_error, "Message."),
    std::runtime_error, "Message.");
}



TEST_F(test_exception_death_test, hou_throw_0_macro)
{
  EXPECT_THROW_0(HOU_THROW_0(exception_0_args), exception_0_args);
}



TEST_F(test_exception_death_test, hou_throw_n_macro)
{
  EXPECT_THROW_N(
    HOU_THROW_N(exception_2_args, 88, 'a'), exception_2_args, 88, 'a');
}



TEST_F(test_exception, hou_check_std_0_macro_success)
{
  EXPECT_NO_THROW(HOU_CHECK_STD_0(2 == 2, std::exception));
}



TEST_F(test_exception_death_test, hou_check_std_0_macro_failure)
{
  EXPECT_THROW_STD_0(HOU_CHECK_STD_0(0 == 2, std::exception), std::exception);
}



TEST_F(test_exception, hou_check_std_n_macro_success)
{
  EXPECT_NO_THROW(HOU_CHECK_STD_N(2 == 2, std::runtime_error, "Message."));
}



TEST_F(test_exception_death_test, hou_check_std_n_macro_failure)
{
  EXPECT_THROW_STD_N(HOU_CHECK_STD_N(0 == 2, std::runtime_error, "Message."),
    std::runtime_error, "Message.");
}



TEST_F(test_exception, hou_check_0_macro_success)
{
  EXPECT_NO_THROW(HOU_CHECK_0(2 == 2, exception_0_args));
}



TEST_F(test_exception_death_test, hou_check_0_macro_failure)
{
  EXPECT_THROW_0(HOU_CHECK_0(0 == 2, exception_0_args), exception_0_args);
}



TEST_F(test_exception, hou_check_n_macro_success)
{
  EXPECT_NO_THROW(HOU_CHECK_N(2 == 2, exception_2_args, 88, 'a'));
}



TEST_F(test_exception_death_test, hou_check_n_macro_failure)
{
  EXPECT_THROW_N(
    HOU_CHECK_N(0 == 2, exception_2_args, 88, 'a'), exception_2_args, 88, 'a');
}



TEST_F(test_exception, hou_dev_check_std_0_macro_success)
{
#ifdef NDEBUG
  EXPECT_NO_THROW(HOU_DEV_CHECK_STD_0(2 == 2, std::exception));
#else
  EXPECT_NO_THROW(HOU_DEV_CHECK_STD_0(2 == 2, std::exception));
#endif
}



TEST_F(test_exception_death_test, hou_dev_check_std_0_macro_failure)
{
#ifdef NDEBUG
  EXPECT_NO_THROW(HOU_DEV_CHECK_STD_0(0 == 2, std::exception));
#else
  EXPECT_THROW_STD_0(
    HOU_DEV_CHECK_STD_0(0 == 2, std::exception), std::exception);
#endif
}



TEST_F(test_exception, hou_dev_check_std_n_macro_success)
{
#ifdef NDEBUG
  EXPECT_NO_THROW(HOU_DEV_CHECK_STD_N(2 == 2, std::runtime_error, "Message."));
#else
  EXPECT_NO_THROW(HOU_DEV_CHECK_STD_N(2 == 2, std::runtime_error, "Message."));
#endif
}



TEST_F(test_exception_death_test, hou_dev_check_std_n_macro_failure)
{
#ifdef NDEBUG
  EXPECT_NO_THROW(HOU_DEV_CHECK_STD_N(0 == 2, std::runtime_error, "Message."));
#else
  EXPECT_THROW_STD_N(
    HOU_DEV_CHECK_STD_N(0 == 2, std::runtime_error, "Message."),
    std::runtime_error, "Message.");
#endif
}



TEST_F(test_exception, hou_dev_check_0_macro_success)
{
#ifdef NDEBUG
  EXPECT_NO_THROW(HOU_DEV_CHECK_0(2 == 2, exception_0_args));
#else
  EXPECT_NO_THROW(HOU_DEV_CHECK_0(2 == 2, exception_0_args));
#endif
}



TEST_F(test_exception_death_test, hou_dev_check_0_macro_failure)
{
#ifdef NDEBUG
  EXPECT_NO_THROW(HOU_DEV_CHECK_0(0 == 2, exception_0_args));
#else
  EXPECT_THROW_0(HOU_DEV_CHECK_0(0 == 2, exception_0_args), exception_0_args);
#endif
}



TEST_F(test_exception, hou_dev_check_n_macro_success)
{
#ifdef NDEBUG
  EXPECT_NO_THROW(HOU_DEV_CHECK_N(2 == 2, exception_2_args, 88, 'a'));
#else
  EXPECT_NO_THROW(HOU_DEV_CHECK_N(2 == 2, exception_2_args, 88, 'a'));
#endif
}



TEST_F(test_exception_death_test, hou_dev_check_n_macro_failure)
{
#ifdef NDEBUG
  EXPECT_NO_THROW(HOU_DEV_CHECK_N(0 == 2, exception_2_args, 88, 'a'));
#else
  EXPECT_THROW_N(HOU_DEV_CHECK_N(0 == 2, exception_2_args, 88, 'a'),
    exception_2_args, 88, 'a');
#endif
}
