// Houzi Game Engine
// Copyright (c) 2018 Davide Corradi
// Licensed under the MIT license.

#include "hou/test.hpp"

#include "hou/cor/std_string.hpp"

using namespace hou;
using namespace testing;



namespace
{

class test_std_string : public Test {};

}



TEST_F(test_std_string, format_string)
{
  std::string str = u8"This is a %s string with number: %d";
  std::string formatted_string_ref = u8"This is a nice string with number: 2";
  std::string formatted_string = format_string(str, u8"nice", 2);
  EXPECT_EQ(formatted_string_ref, formatted_string);
}



TEST_F(test_std_string, replace_all)
{
  std::string s_in = u8"This is a blue blueprint of a blueblue blues";
  std::string s_out = replace_all(s_in, "blue", "red");
  EXPECT_EQ(u8"This is a red redprint of a redred reds", s_out);
}



TEST_F(test_std_string, format_regex)
{
  std::string s_in = u8".^$*+?()[{\\|";
  std::string s_out = escape_regex(s_in);
  EXPECT_EQ(u8"\\.\\^\\$\\*\\+\\?\\(\\)\\[\\{\\\\\\|", s_out);
}



TEST_F(test_std_string, bool_to_string)
{
  EXPECT_EQ("true", to_string(true));
  EXPECT_EQ("false", to_string(false));
}



TEST_F(test_std_string, split_string)
{
  std::string s = "This ;; is a, string; delimited; by ;semicolons";

  std::vector<std::string> items_semicolon;
  std::vector<std::string> items_semicolon_ref
  {
    "This ",
    "",
    " is a, string",
    " delimited",
    " by ",
    "semicolons",
  };
  split_string(s, ';', std::back_inserter(items_semicolon));
  EXPECT_EQ(items_semicolon_ref, items_semicolon);

  std::vector<std::string> items_comma;
  std::vector<std::string> items_comma_ref
  {
    "This ;; is a",
    " string; delimited; by ;semicolons",
  };
  split_string(s, ',', std::back_inserter(items_comma));
  EXPECT_EQ(items_comma_ref, items_comma);
}



TEST_F(test_std_string, split_string_output)
{
  std::string s = "a b c d";
  std::vector<std::string> chars(4, std::string());

  auto it = split_string(s, ' ', chars.begin());
  EXPECT_EQ(chars.end(), it);
}



TEST_F(test_std_string, to_string)
{
  EXPECT_EQ("46", to_string(46));
  EXPECT_EQ("34.56", to_string(34.56f));
  EXPECT_EQ("a", to_string('a'));
}

