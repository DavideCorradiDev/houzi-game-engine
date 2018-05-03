// Houzi Game Engine
// Copyright (c) 2018 Davide Corradi
// Licensed under the MIT license.

#include "hou/Test.hpp"

#include "hou/cor/character_encodings.hpp"

using namespace hou;
using namespace testing;



namespace
{

class test_character_encodings : public Test
{};
class test_character_encodings_death_test : public test_character_encodings
{};

}  // namespace



TEST_F(test_character_encodings, utf8_encoding)
{
  std::array<utf8::code_unit, 4u> utf8_char;
  auto retval = utf8_char.begin();

  // a
  retval = utf8::encode(U'\U00000061', utf8_char.begin());
  EXPECT_EQ(&utf8_char[0] + 1, retval);
  EXPECT_EQ('\x61', utf8_char[0]);

  // a with macron
  retval = utf8::encode(U'\U00000101', utf8_char.begin());
  EXPECT_EQ(&utf8_char[0] + 2, retval);
  EXPECT_EQ('\xC4', utf8_char[0]);
  EXPECT_EQ('\x81', utf8_char[1]);

  // devanagari short a
  retval = utf8::encode(U'\U00000904', utf8_char.begin());
  EXPECT_EQ(&utf8_char[0] + 3, retval);
  EXPECT_EQ('\xE0', utf8_char[0]);
  EXPECT_EQ('\xA4', utf8_char[1]);
  EXPECT_EQ('\x84', utf8_char[2]);

  // pau cin hau letter pa
  retval = utf8::encode(U'\U00011AC0', utf8_char.begin());
  EXPECT_EQ(&utf8_char[0] + 4, retval);
  EXPECT_EQ('\xF0', utf8_char[0]);
  EXPECT_EQ('\x91', utf8_char[1]);
  EXPECT_EQ('\xAB', utf8_char[2]);
  EXPECT_EQ('\x80', utf8_char[3]);
}



TEST_F(test_character_encodings, utf8_decoding)
{
  std::array<utf8::code_unit, 4u> utf8_char;
  auto retval = utf8_char.begin();
  code_point char_code;

  // a
  utf8_char[0] = '\x61';
  utf8_char[1] = '\x00';
  utf8_char[2] = '\x00';
  utf8_char[3] = '\x00';
  retval = utf8::decode(utf8_char.begin(), utf8_char.end(), char_code);
  EXPECT_EQ(U'\U00000061', char_code);
  EXPECT_EQ(&utf8_char[0] + 1, retval);

  // a with macron
  utf8_char[0] = '\xC4';
  utf8_char[1] = '\x81';
  utf8_char[2] = '\x00';
  utf8_char[3] = '\x00';
  retval = utf8::decode(utf8_char.begin(), utf8_char.end(), char_code);
  EXPECT_EQ(U'\U00000101', char_code);
  EXPECT_EQ(&utf8_char[0] + 2, retval);

  // devanagari short a
  utf8_char[0] = '\xE0';
  utf8_char[1] = '\xA4';
  utf8_char[2] = '\x84';
  utf8_char[3] = '\x00';
  retval = utf8::decode(utf8_char.begin(), utf8_char.end(), char_code);
  EXPECT_EQ(U'\U00000904', char_code);
  EXPECT_EQ(&utf8_char[0] + 3, retval);

  // pau cin hau letter pa
  utf8_char[0] = '\xF0';
  utf8_char[1] = '\x91';
  utf8_char[2] = '\xAB';
  utf8_char[3] = '\x80';
  retval = utf8::decode(utf8_char.begin(), utf8_char.end(), char_code);
  EXPECT_EQ(U'\U00011AC0', char_code);
  EXPECT_EQ(&utf8_char[0] + 4, retval);
}



TEST_F(test_character_encodings_death_test, utf8_decoding_failure)
{
  std::array<utf8::code_unit, 4u> utf8_char{'\xF0', '\x91', '\xAB', '\x80'};
  code_point char_code;

  DEPRECATED_HOU_EXPECT_ERROR(
    utf8::decode(utf8_char.end(), utf8_char.begin(), char_code),
    std::logic_error, get_text(cor_error::pre_condition));
}



TEST_F(test_character_encodings, utf8_next)
{
  std::array<utf8::code_unit, 4u> utf8_char;
  auto retval = utf8_char.begin();

  // a
  utf8_char[0] = '\x61';
  utf8_char[1] = '\x00';
  utf8_char[2] = '\x00';
  utf8_char[3] = '\x00';
  retval = utf8::next(utf8_char.begin(), utf8_char.end());
  EXPECT_EQ(&utf8_char[0] + 1, retval);

  // a with macron
  utf8_char[0] = '\xC4';
  utf8_char[1] = '\x81';
  utf8_char[2] = '\x00';
  utf8_char[3] = '\x00';
  retval = utf8::next(utf8_char.begin(), utf8_char.end());
  EXPECT_EQ(&utf8_char[0] + 2, retval);

  // devanagari short a
  utf8_char[0] = '\xE0';
  utf8_char[1] = '\xA4';
  utf8_char[2] = '\x84';
  utf8_char[3] = '\x00';
  retval = utf8::next(utf8_char.begin(), utf8_char.end());
  EXPECT_EQ(&utf8_char[0] + 3, retval);

  // pau cin hau letter pa
  utf8_char[0] = '\xF0';
  utf8_char[1] = '\x91';
  utf8_char[2] = '\xAB';
  utf8_char[3] = '\x80';
  retval = utf8::next(utf8_char.begin(), utf8_char.end());
  EXPECT_EQ(&utf8_char[0] + 4, retval);
}



TEST_F(test_character_encodings_death_test, utf8_next_failure)
{
  std::array<utf8::code_unit, 4u> utf8_char;
  DEPRECATED_HOU_EXPECT_ERROR(
    utf8::next(utf8_char.end(), utf8_char.begin()), std::logic_error,
    get_text(cor_error::pre_condition));
}



TEST_F(test_character_encodings, utf8_count)
{
  std::array<utf8::code_unit, 32u> utf8_string;
  auto next = utf8_string.begin();

  EXPECT_EQ(0u, utf8::count(utf8_string.begin(), next));

  next = utf8::encode(0x61, next);
  EXPECT_EQ(1u, utf8::count(utf8_string.begin(), next));

  next = utf8::encode(0x11AC0, next);
  EXPECT_EQ(2u, utf8::count(utf8_string.begin(), next));

  next = utf8::encode(0x101, next);
  EXPECT_EQ(3u, utf8::count(utf8_string.begin(), next));

  next = utf8::encode(0x0904, next);
  EXPECT_EQ(4u, utf8::count(utf8_string.begin(), next));

  next = utf8::encode(0x61, next);
  EXPECT_EQ(5u, utf8::count(utf8_string.begin(), next));

  next = utf8::encode(0x61, next);
  EXPECT_EQ(6u, utf8::count(utf8_string.begin(), next));

  next = utf8::encode(0x101, next);
  EXPECT_EQ(7u, utf8::count(utf8_string.begin(), next));

  next = utf8::encode(0x101, next);
  EXPECT_EQ(8u, utf8::count(utf8_string.begin(), next));
}



TEST_F(test_character_encodings_death_test, utf8_count_failure)
{
  std::array<utf8::code_unit, 32u> utf8_string;
  DEPRECATED_HOU_EXPECT_ERROR(
    utf8::count(utf8_string.end(), utf8_string.begin()), std::logic_error,
    get_text(cor_error::pre_condition));
}



TEST_F(test_character_encodings, utf16_encoding)
{
  std::array<utf16::code_unit, 2u> utf16_char;
  auto retval = utf16_char.begin();

  // a
  retval = utf16::encode(U'\U00000061', utf16_char.begin());
  EXPECT_EQ(&utf16_char[0] + 1, retval);
  EXPECT_EQ(u'\x0061', utf16_char[0]);

  // a with macron
  retval = utf16::encode(U'\U00000101', utf16_char.begin());
  EXPECT_EQ(&utf16_char[0] + 1, retval);
  EXPECT_EQ(u'\x0101', utf16_char[0]);

  // devanagari short a
  retval = utf16::encode(U'\U00000904', utf16_char.begin());
  EXPECT_EQ(&utf16_char[0] + 1, retval);
  EXPECT_EQ(u'\x0904', utf16_char[0]);

  // pau cin hau letter pa
  retval = utf16::encode(U'\U00011AC0', utf16_char.begin());
  EXPECT_EQ(&utf16_char[0] + 2, retval);
  EXPECT_EQ(u'\xD806', utf16_char[0]);
  EXPECT_EQ(u'\xDEC0', utf16_char[1]);
}



TEST_F(test_character_encodings, utf16_decoding)
{
  std::array<utf16::code_unit, 2u> utf16_char;
  auto retval = utf16_char.begin();
  code_point char_code;

  // a
  utf16_char[0] = u'\x0061';
  retval = utf16::decode(utf16_char.begin(), utf16_char.end(), char_code);
  EXPECT_EQ(U'\U00000061', char_code);
  EXPECT_EQ(&utf16_char[0] + 1, retval);

  // a with macron
  utf16_char[0] = u'\x0101';
  retval = utf16::decode(utf16_char.begin(), utf16_char.end(), char_code);
  EXPECT_EQ(U'\U00000101', char_code);
  EXPECT_EQ(&utf16_char[0] + 1, retval);

  // devanagari short a
  utf16_char[0] = u'\x0904';
  retval = utf16::decode(utf16_char.begin(), utf16_char.end(), char_code);
  EXPECT_EQ(U'\U00000904', char_code);
  EXPECT_EQ(&utf16_char[0] + 1, retval);

  // pau cin hau letter pa
  utf16_char[0] = u'\xD806';
  utf16_char[1] = u'\xDEC0';
  retval = utf16::decode(utf16_char.begin(), utf16_char.end(), char_code);
  EXPECT_EQ(U'\U00011AC0', char_code);
  EXPECT_EQ(&utf16_char[0] + 2, retval);
}



TEST_F(test_character_encodings_death_test, utf16_decoding_failure)
{
  std::array<utf16::code_unit, 2u> utf16_char = {u'\xD806', u'\xDEC0'};
  code_point char_code;

  DEPRECATED_HOU_EXPECT_ERROR(
    utf16::decode(utf16_char.end(), utf16_char.begin(), char_code),
    std::logic_error, get_text(cor_error::pre_condition));
}



TEST_F(test_character_encodings, utf16_next)
{
  std::array<utf16::code_unit, 2u> utf16_char;
  auto retval = utf16_char.begin();

  // a
  utf16_char[0] = u'\x0061';
  retval = utf16::next(utf16_char.begin(), utf16_char.end());
  EXPECT_EQ(&utf16_char[0] + 1, retval);

  // a with macron
  utf16_char[0] = u'\x0101';
  retval = utf16::next(utf16_char.begin(), utf16_char.end());
  EXPECT_EQ(&utf16_char[0] + 1, retval);

  // devanagari short a
  utf16_char[0] = u'\x0904';
  retval = utf16::next(utf16_char.begin(), utf16_char.end());
  EXPECT_EQ(&utf16_char[0] + 1, retval);

  // pau cin hau letter pa
  utf16_char[0] = u'\xD806';
  utf16_char[1] = u'\xDEC0';
  retval = utf16::next(utf16_char.begin(), utf16_char.end());
  EXPECT_EQ(&utf16_char[0] + 2, retval);
}



TEST_F(test_character_encodings_death_test, utf16_next_failure)
{
  std::array<utf16::code_unit, 2u> utf16_char;
  DEPRECATED_HOU_EXPECT_ERROR(
    utf16::next(utf16_char.end(), utf16_char.begin()), std::logic_error,
    get_text(cor_error::pre_condition));
}



TEST_F(test_character_encodings, utf16_count)
{
  std::array<utf16::code_unit, 16u> utf16_string;
  auto next = utf16_string.begin();

  EXPECT_EQ(0u, utf16::count(utf16_string.begin(), next));

  next = utf16::encode(U'\U00000061', next);
  EXPECT_EQ(1u, utf16::count(utf16_string.begin(), next));

  next = utf16::encode(U'\U00011AC0', next);
  EXPECT_EQ(2u, utf16::count(utf16_string.begin(), next));

  next = utf16::encode(U'\U00000101', next);
  EXPECT_EQ(3u, utf16::count(utf16_string.begin(), next));

  next = utf16::encode(U'\U00000904', next);
  EXPECT_EQ(4u, utf16::count(utf16_string.begin(), next));

  next = utf16::encode(U'\U00000061', next);
  EXPECT_EQ(5u, utf16::count(utf16_string.begin(), next));

  next = utf16::encode(U'\U00000061', next);
  EXPECT_EQ(6u, utf16::count(utf16_string.begin(), next));

  next = utf16::encode(U'\U00000101', next);
  EXPECT_EQ(7u, utf16::count(utf16_string.begin(), next));

  next = utf16::encode(U'\U00000101', next);
  EXPECT_EQ(8u, utf16::count(utf16_string.begin(), next));
}



TEST_F(test_character_encodings_death_test, utf16_count_failure)
{
  std::array<utf16::code_unit, 16u> utf16_string;
  DEPRECATED_HOU_EXPECT_ERROR(
    utf16::count(utf16_string.end(), utf16_string.begin()), std::logic_error,
    get_text(cor_error::pre_condition));
}



TEST_F(test_character_encodings, utf32_encoding)
{
  std::array<utf32::code_unit, 1u> utf32_char;
  auto retval = utf32_char.begin();

  // a
  retval = utf32::encode(U'\U00000061', utf32_char.begin());
  EXPECT_EQ(&utf32_char[0] + 1, retval);
  EXPECT_EQ(U'\U00000061', utf32_char[0]);

  // a with macron
  retval = utf32::encode(U'\U00000101', utf32_char.begin());
  EXPECT_EQ(&utf32_char[0] + 1, retval);
  EXPECT_EQ(U'\U00000101', utf32_char[0]);

  // devanagari short a
  retval = utf32::encode(U'\U00000904', utf32_char.begin());
  EXPECT_EQ(&utf32_char[0] + 1, retval);
  EXPECT_EQ(U'\U00000904', utf32_char[0]);

  // pau cin hau letter pa
  retval = utf32::encode(U'\U00011AC0', utf32_char.begin());
  EXPECT_EQ(&utf32_char[0] + 1, retval);
  EXPECT_EQ(U'\U00011AC0', utf32_char[0]);
}



TEST_F(test_character_encodings, utf32_decoding)
{
  std::array<utf32::code_unit, 1u> utf32_char;
  auto retval = utf32_char.begin();
  code_point char_code;

  // a
  utf32_char[0] = U'\U00000061';
  retval = utf32::decode(utf32_char.begin(), utf32_char.end(), char_code);
  EXPECT_EQ(U'\U00000061', char_code);
  EXPECT_EQ(&utf32_char[0] + 1, retval);

  // a with macron
  utf32_char[0] = U'\U00000101';
  retval = utf32::decode(utf32_char.begin(), utf32_char.end(), char_code);
  EXPECT_EQ(U'\U00000101', char_code);
  EXPECT_EQ(&utf32_char[0] + 1, retval);

  // devanagari short a
  utf32_char[0] = U'\U00000904';
  retval = utf32::decode(utf32_char.begin(), utf32_char.end(), char_code);
  EXPECT_EQ(U'\U00000904', char_code);
  EXPECT_EQ(&utf32_char[0] + 1, retval);

  // pau cin hau letter pa
  utf32_char[0] = U'\U00011AC0';
  retval = utf32::decode(utf32_char.begin(), utf32_char.end(), char_code);
  EXPECT_EQ(U'\U00011AC0', char_code);
  EXPECT_EQ(&utf32_char[0] + 1, retval);
}



TEST_F(test_character_encodings_death_test, utf32_decoding_failure)
{
  std::array<utf32::code_unit, 1u> utf32_char = {U'\U00000012'};
  code_point char_code;

  DEPRECATED_HOU_EXPECT_ERROR(
    utf32::decode(utf32_char.end(), utf32_char.begin(), char_code),
    std::logic_error, get_text(cor_error::pre_condition));
}



TEST_F(test_character_encodings, utf32_next)
{
  std::array<utf32::code_unit, 1u> utf32_char;
  auto retval = utf32_char.begin();

  // a
  utf32_char[0] = U'\U00000061';
  retval = utf32::next(utf32_char.begin(), utf32_char.end());
  EXPECT_EQ(&utf32_char[0] + 1, retval);

  // a with macron
  utf32_char[0] = U'\U00000101';
  retval = utf32::next(utf32_char.begin(), utf32_char.end());
  EXPECT_EQ(&utf32_char[0] + 1, retval);

  // devanagari short a
  utf32_char[0] = U'\U00000904';
  retval = utf32::next(utf32_char.begin(), utf32_char.end());
  EXPECT_EQ(&utf32_char[0] + 1, retval);

  // pau cin hau letter pa
  utf32_char[0] = U'\U00011AC0';
  retval = utf32::next(utf32_char.begin(), utf32_char.end());
  EXPECT_EQ(&utf32_char[0] + 1, retval);
}



TEST_F(test_character_encodings_death_test, utf32_nextFaillure)
{
  std::array<utf32::code_unit, 1u> utf32_char;
  DEPRECATED_HOU_EXPECT_ERROR(
    utf32::next(utf32_char.end(), utf32_char.begin()), std::logic_error,
    get_text(cor_error::pre_condition));
}



TEST_F(test_character_encodings, utf32_count)
{
  std::array<utf32::code_unit, 8u> utf32_string;
  auto next = utf32_string.begin();

  EXPECT_EQ(0u, utf32::count(utf32_string.begin(), next));

  next = utf32::encode(U'\U00000061', next);
  EXPECT_EQ(1u, utf32::count(utf32_string.begin(), next));

  next = utf32::encode(U'\U00011AC0', next);
  EXPECT_EQ(2u, utf32::count(utf32_string.begin(), next));

  next = utf32::encode(U'\U00000101', next);
  EXPECT_EQ(3u, utf32::count(utf32_string.begin(), next));

  next = utf32::encode(U'\U00000904', next);
  EXPECT_EQ(4u, utf32::count(utf32_string.begin(), next));

  next = utf32::encode(U'\U00000061', next);
  EXPECT_EQ(5u, utf32::count(utf32_string.begin(), next));

  next = utf32::encode(U'\U00000061', next);
  EXPECT_EQ(6u, utf32::count(utf32_string.begin(), next));

  next = utf32::encode(U'\U00000101', next);
  EXPECT_EQ(7u, utf32::count(utf32_string.begin(), next));

  next = utf32::encode(U'\U00000101', next);
  EXPECT_EQ(8u, utf32::count(utf32_string.begin(), next));
}



TEST_F(test_character_encodings_death_test, utf32_count_failure)
{
  std::array<utf32::code_unit, 8u> utf32_string;
  DEPRECATED_HOU_EXPECT_ERROR(
    utf32::count(utf32_string.end(), utf32_string.begin()), std::logic_error,
    get_text(cor_error::pre_condition));
}



TEST_F(test_character_encodings, wide_encoding)
{
  std::array<wide::code_unit, 1u> wide_char;
  auto retval = wide_char.begin();

  // a
  retval = wide::encode(U'\U00000061', wide_char.begin());
  EXPECT_EQ(&wide_char[0] + 1, retval);
  EXPECT_EQ(0x0061, wide_char[0]);

  retval = wide::encode(U'\U00000101', wide_char.begin());
  EXPECT_EQ(&wide_char[0] + 1, retval);
  EXPECT_EQ(0x0101, wide_char[0]);

  retval = wide::encode(U'\U00000904', wide_char.begin());
  EXPECT_EQ(&wide_char[0] + 1, retval);
  EXPECT_EQ(0x0904, wide_char[0]);
}



TEST_F(test_character_encodings, wide_decoding)
{
  std::array<wide::code_unit, 1u> wide_char;
  auto retval = wide_char.begin();
  code_point char_code;

  // a
  wide_char[0] = 0x0061;
  retval = wide::decode(wide_char.begin(), wide_char.end(), char_code);
  EXPECT_EQ(U'\U00000061', char_code);
  EXPECT_EQ(&wide_char[0] + 1, retval);

  // a with macron
  wide_char[0] = 0x0101;
  retval = wide::decode(wide_char.begin(), wide_char.end(), char_code);
  EXPECT_EQ(U'\U00000101', char_code);
  EXPECT_EQ(&wide_char[0] + 1, retval);

  // devanagari short a
  wide_char[0] = 0x0904;
  retval = wide::decode(wide_char.begin(), wide_char.end(), char_code);
  EXPECT_EQ(U'\U00000904', char_code);
  EXPECT_EQ(&wide_char[0] + 1, retval);
}



TEST_F(test_character_encodings_death_test, wide_decoding_failure)
{
  wide::code_unit wide_char;
  code_point char_code;

  DEPRECATED_HOU_EXPECT_ERROR(
    wide::decode(&wide_char + 1, &wide_char, char_code), std::logic_error,
    get_text(cor_error::pre_condition));
}



TEST_F(test_character_encodings, wide_next)
{
  std::array<wide::code_unit, 2u> wide_char;
  auto retval = wide_char.begin();

  // a
  wide_char[0] = u'\x0061';
  retval = wide::next(wide_char.begin(), wide_char.end());
  EXPECT_EQ(&wide_char[0] + 1, retval);

  // a with macron
  wide_char[0] = u'\x0101';
  retval = wide::next(wide_char.begin(), wide_char.end());
  EXPECT_EQ(&wide_char[0] + 1, retval);

  // devanagari short a
  wide_char[0] = u'\x0904';
  retval = wide::next(wide_char.begin(), wide_char.end());
  EXPECT_EQ(&wide_char[0] + 1, retval);
}



TEST_F(test_character_encodings_death_test, wide_next_failure)
{
  wide::code_unit wide_char;
  DEPRECATED_HOU_EXPECT_ERROR(
    wide::next(&wide_char + 2, &wide_char + 1), std::logic_error,
    get_text(cor_error::pre_condition));
}



TEST_F(test_character_encodings, wide_count)
{
  wide::code_unit wide_string[] = L"hello!";
  EXPECT_EQ(7u, wide::count(wide_string, wide_string + 7));
}



TEST_F(test_character_encodings_death_test, wide_count_failure)
{
  wide::code_unit wide_string[] = L"hello!";
  DEPRECATED_HOU_EXPECT_ERROR(
    wide::count(wide_string + 4, wide_string + 3), std::logic_error,
    get_text(cor_error::pre_condition));
}



TEST_F(test_character_encodings, utf32_utf16_conversion)
{
  utf32::code_unit utf32_ref[]
    = {U'\U00000061', U'\U00011AC0', U'\U00000101', U'\U00000904'};
  utf32::code_unit utf32Str[4] = {0};
  utf16::code_unit utf16_ref[]
    = {u'\x0061', u'\xD806', u'\xDEC0', u'\x0101', u'\x0904'};
  utf16::code_unit utf16Str[5] = {0};

  convert_encoding<utf32, utf16>(utf32_ref, utf32_ref + 4, utf16Str);
  convert_encoding<utf16, utf32>(utf16_ref, utf16_ref + 5, utf32Str);

  HOU_EXPECT_ARRAY_EQ(utf32_ref, utf32Str, 4);
  HOU_EXPECT_ARRAY_EQ(utf16_ref, utf16Str, 5);
}



TEST_F(test_character_encodings, utf32_utf8_conversion)
{
  utf32::code_unit utf32_ref[]
    = {U'\U00000061', U'\U00011AC0', U'\U00000101', U'\U00000904'};
  utf32::code_unit utf32Str[4] = {0};
  utf8::code_unit utf8_ref[] = {'\x61', '\xF0', '\x91', '\xAB', '\x80',
                               '\xC4', '\x81', '\xE0', '\xA4', '\x84'};
  utf8::code_unit utf8Str[10] = {0};

  convert_encoding<utf32, utf8>(utf32_ref, utf32_ref + 4, utf8Str);
  convert_encoding<utf8, utf32>(utf8_ref, utf8_ref + 10, utf32Str);

  HOU_EXPECT_ARRAY_EQ(utf32_ref, utf32Str, 4);
  HOU_EXPECT_ARRAY_EQ(utf8_ref, utf8Str, 10);
}



TEST_F(test_character_encodings, utf16_utf8_conversion)
{
  utf16::code_unit utf16_ref[]
    = {u'\x0061', u'\xD806', u'\xDEC0', u'\x0101', u'\x0904'};
  utf16::code_unit utf16Str[5] = {0};
  utf8::code_unit utf8_ref[] = {'\x61', '\xF0', '\x91', '\xAB', '\x80',
                               '\xC4', '\x81', '\xE0', '\xA4', '\x84'};
  utf8::code_unit utf8Str[10] = {0};

  convert_encoding<utf16, utf8>(utf16_ref, utf16_ref + 5, utf8Str);
  convert_encoding<utf8, utf16>(utf8_ref, utf8_ref + 10, utf16Str);

  HOU_EXPECT_ARRAY_EQ(utf16_ref, utf16Str, 5);
  HOU_EXPECT_ARRAY_EQ(utf8_ref, utf8Str, 10);
}



TEST_F(test_character_encodings, string_encoding_conversion)
{
  std::string utf8_ref = u8"\U00000061\U00011AC0\U00000101\U00000904";
  std::u16string utf16_ref = u"\U00000061\U00011AC0\U00000101\U00000904";
  std::u32string utf32_ref = U"\U00000061\U00011AC0\U00000101\U00000904";

  std::string u16to8 = convert_encoding<utf16, utf8>(utf16_ref);
  EXPECT_EQ(utf8_ref, u16to8);

  std::string u32to8 = convert_encoding<utf32, utf8>(utf32_ref);
  EXPECT_EQ(utf8_ref, u32to8);

  std::u16string u8to16 = convert_encoding<utf8, utf16>(utf8_ref);
  EXPECT_EQ(utf16_ref, u8to16);

  std::u16string u32to16 = convert_encoding<utf32, utf16>(utf32_ref);
  EXPECT_EQ(utf16_ref, u32to16);

  std::u32string u8to32 = convert_encoding<utf8, utf32>(utf8_ref);
  EXPECT_EQ(utf32_ref, u8to32);

  std::u32string u16to32 = convert_encoding<utf16, utf32>(utf16_ref);
  EXPECT_EQ(utf32_ref, u16to32);
}
