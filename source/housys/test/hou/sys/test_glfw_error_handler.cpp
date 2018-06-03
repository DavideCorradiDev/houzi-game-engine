// Houzi Game Engine
// Copyright (c) 2018 Davide Corradi
// Licensed under the MIT license.

#include "hou/test.hpp"

#include "hou/sys/glfw/glfw_error_handler.hpp"

using namespace hou;
using namespace testing;



namespace
{

class test_glfw_error_handler : public Test
{
public:
  test_glfw_error_handler();
  ~test_glfw_error_handler();
};



test_glfw_error_handler::test_glfw_error_handler()
{
  prv::glfw_error_handler::clear_callbacks();
}



test_glfw_error_handler::~test_glfw_error_handler()
{
  prv::glfw_error_handler::clear_callbacks();
}

}  // namespace



TEST_F(test_glfw_error_handler, unset_callbacks)
{
  prv::glfw_error_handler::callback(0, "");
  prv::glfw_error_handler::callback(1, "");
  prv::glfw_error_handler::callback(2, "");
  SUCCEED();
}



TEST_F(test_glfw_error_handler, set_callback)
{
  int calls = 0;
  std::string error_description;
  auto f = [&](const char* description) {
    ++calls;
    error_description = description;
  };
  prv::glfw_error_handler::set_callback(1, f);

  std::string error_ref("This is the error message.");

  EXPECT_EQ(0, calls);
  EXPECT_EQ(std::string(), error_description);

  prv::glfw_error_handler::callback(0, error_ref.c_str());
  EXPECT_EQ(0, calls);
  EXPECT_EQ(std::string(), error_description);

  prv::glfw_error_handler::callback(1, error_ref.c_str());
  EXPECT_EQ(1, calls);
  EXPECT_EQ(error_ref, error_description);

  prv::glfw_error_handler::callback(1, error_ref.c_str());
  EXPECT_EQ(2, calls);
  EXPECT_EQ(error_ref, error_description);
}



TEST_F(test_glfw_error_handler, set_multiple_callbacks)
{
  using namespace std::placeholders;

  auto f
    = [](const char* description, int& calls, std::string& out_description) {
        ++calls;
        out_description = description;
      };

  int calls1 = 0;
  std::string error_description_1;
  prv::glfw_error_handler::set_callback(
    1, std::bind(f, _1, std::ref(calls1), std::ref(error_description_1)));

  int calls2 = 4;
  std::string error_description_2;
  prv::glfw_error_handler::set_callback(
    2, std::bind(f, _1, std::ref(calls2), std::ref(error_description_2)));

  std::string error_ref("This is the error message.");

  EXPECT_EQ(0, calls1);
  EXPECT_EQ(std::string(), error_description_1);
  EXPECT_EQ(4, calls2);
  EXPECT_EQ(std::string(), error_description_2);

  prv::glfw_error_handler::callback(0, error_ref.c_str());
  EXPECT_EQ(0, calls1);
  EXPECT_EQ(std::string(), error_description_1);
  EXPECT_EQ(4, calls2);
  EXPECT_EQ(std::string(), error_description_2);

  prv::glfw_error_handler::callback(1, error_ref.c_str());
  EXPECT_EQ(1, calls1);
  EXPECT_EQ(error_ref, error_description_1);
  EXPECT_EQ(4, calls2);
  EXPECT_EQ(std::string(), error_description_2);

  prv::glfw_error_handler::callback(1, error_ref.c_str());
  EXPECT_EQ(2, calls1);
  EXPECT_EQ(error_ref, error_description_1);
  EXPECT_EQ(4, calls2);
  EXPECT_EQ(std::string(), error_description_2);

  prv::glfw_error_handler::callback(2, error_ref.c_str());
  EXPECT_EQ(2, calls1);
  EXPECT_EQ(error_ref, error_description_1);
  EXPECT_EQ(5, calls2);
  EXPECT_EQ(error_ref, error_description_2);
}



TEST_F(test_glfw_error_handler, overwrite_callback)
{
  using namespace std::placeholders;

  auto f = [](const char*, int& calls) { ++calls; };

  int calls1 = 0;
  int calls2 = 4;

  prv::glfw_error_handler::callback(0, "");
  EXPECT_EQ(0, calls1);
  EXPECT_EQ(4, calls2);

  prv::glfw_error_handler::set_callback(0, std::bind(f, _1, std::ref(calls1)));
  prv::glfw_error_handler::callback(0, "");
  EXPECT_EQ(1, calls1);
  EXPECT_EQ(4, calls2);

  prv::glfw_error_handler::set_callback(0, std::bind(f, _1, std::ref(calls2)));
  prv::glfw_error_handler::callback(0, "");
  EXPECT_EQ(1, calls1);
  EXPECT_EQ(5, calls2);
}



TEST_F(test_glfw_error_handler, unset_callback)
{
  int calls = 0;
  auto f = [&](const char*) { ++calls; };

  prv::glfw_error_handler::callback(0, "");
  EXPECT_EQ(0, calls);

  prv::glfw_error_handler::set_callback(0, f);
  prv::glfw_error_handler::callback(0, "");
  EXPECT_EQ(1, calls);

  prv::glfw_error_handler::set_callback(0, nullptr);
  prv::glfw_error_handler::callback(0, "");
  EXPECT_EQ(1, calls);
}



TEST_F(test_glfw_error_handler, unset_callback_already_unset)
{
  prv::glfw_error_handler::callback(0, "");
  prv::glfw_error_handler::set_callback(0, nullptr);
  prv::glfw_error_handler::callback(0, "");
  SUCCEED();
}



TEST_F(test_glfw_error_handler, shared_callback)
{
  int calls = 0;
  auto f = [&](const char*) { ++calls; };

  prv::glfw_error_handler::callback(0, "");
  EXPECT_EQ(0, calls);

  prv::glfw_error_handler::set_callback(0, f);
  prv::glfw_error_handler::callback(0, "");
  EXPECT_EQ(1, calls);

  prv::glfw_error_handler::set_callback(1, f);
  prv::glfw_error_handler::callback(1, "");
  EXPECT_EQ(2, calls);

  prv::glfw_error_handler::callback(0, "");
  EXPECT_EQ(3, calls);

  prv::glfw_error_handler::callback(1, "");
  EXPECT_EQ(4, calls);
}



TEST_F(test_glfw_error_handler, clear_callbacks)
{
  using namespace std::placeholders;

  auto f = [](const char*, int& calls) { ++calls; };

  int calls1 = 0;
  int calls2 = 3;

  prv::glfw_error_handler::set_callback(1, std::bind(f, _1, std::ref(calls1)));
  prv::glfw_error_handler::set_callback(2, std::bind(f, _1, std::ref(calls2)));
  prv::glfw_error_handler::callback(1, "");
  EXPECT_EQ(1, calls1);
  prv::glfw_error_handler::callback(2, "");
  EXPECT_EQ(4, calls2);
  prv::glfw_error_handler::clear_callbacks();
  prv::glfw_error_handler::callback(1, "");
  EXPECT_EQ(1, calls1);
  prv::glfw_error_handler::callback(2, "");
  EXPECT_EQ(4, calls2);
}
