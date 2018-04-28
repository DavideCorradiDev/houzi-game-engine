// Houzi Game Engine
// Copyright (c) 2018 Davide Corradi
// Licensed under the MIT license.

#include "hou/Test.hpp"

#include "hou/cor/std_string.hpp"

using namespace hou;
using namespace testing;



namespace
{

class TestStdString : public Test {};

}



TEST_F(TestStdString, FormatString)
{
  std::string str = u8"This is a %s string with number: %d";
  std::string formattedStringRef = u8"This is a nice string with number: 2";
  std::string formattedString = format_string(str, u8"nice", 2);
  EXPECT_EQ(formattedStringRef, formattedString);
}



TEST_F(TestStdString, ReplaceAll)
{
  std::string sIn = u8"This is a blue blueprint of a blueblue blues";
  std::string sOut = replace_all(sIn, "blue", "red");
  EXPECT_EQ(u8"This is a red redprint of a redred reds", sOut);
}



TEST_F(TestStdString, FormatRegex)
{
  std::string sIn = u8".^$*+?()[{\\|";
  std::string sOut = format_regex(sIn);
  EXPECT_EQ(u8"\\.\\^\\$\\*\\+\\?\\(\\)\\[\\{\\\\\\|", sOut);
}



TEST_F(TestStdString, BoolToString)
{
  EXPECT_EQ("true", to_string(true));
  EXPECT_EQ("false", to_string(false));
}



TEST_F(TestStdString, SplitString)
{
  std::string s = "This ;; is a, string; delimited; by ;semicolons";

  std::vector<std::string> itemsSemicolon;
  std::vector<std::string> itemsSemicolonRef
  {
    "This ",
    "",
    " is a, string",
    " delimited",
    " by ",
    "semicolons",
  };
  split_string(s, ';', std::back_inserter(itemsSemicolon));
  EXPECT_EQ(itemsSemicolonRef, itemsSemicolon);

  std::vector<std::string> itemsComma;
  std::vector<std::string> itemsCommaRef
  {
    "This ;; is a",
    " string; delimited; by ;semicolons",
  };
  split_string(s, ',', std::back_inserter(itemsComma));
  EXPECT_EQ(itemsCommaRef, itemsComma);
}



TEST_F(TestStdString, SplitStringOutput)
{
  std::string s = "a b c d";
  std::vector<std::string> chars(4, std::string());
  std::vector<std::string> charsRef = {"a", "b", "c", "d"};

  auto it = split_string(s, ' ', chars.begin());
  EXPECT_EQ(chars.end(), it);
}



TEST_F(TestStdString, ToString)
{
  EXPECT_EQ("46", to_string(46));
  EXPECT_EQ("34.56", to_string(34.56f));
  EXPECT_EQ("a", to_string('a'));
}

