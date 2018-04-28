// Houzi Game Engine
// Copyright (c) 2018 Davide Corradi
// Licensed under the MIT license.

#include "hou/Test.hpp"

#include "hou/cor/character_encodings.hpp"

using namespace hou;
using namespace testing;



namespace
{

class TestCharacterEncodings : public Test {};
class TestCharacterEncodingsDeathTest : public TestCharacterEncodings {};

}



TEST_F(TestCharacterEncodings, Utf8Encoding)
{
  std::array<utf8::code_unit, 4u> utf8Char;
  auto retval = utf8Char.begin();

  // a
  retval = utf8::encode(U'\U00000061', utf8Char.begin());
  EXPECT_EQ(&utf8Char[0] + 1, retval);
  EXPECT_EQ('\x61', utf8Char[0]);

  // a with macron
  retval = utf8::encode(U'\U00000101', utf8Char.begin());
  EXPECT_EQ(&utf8Char[0] + 2, retval);
  EXPECT_EQ('\xC4', utf8Char[0]);
  EXPECT_EQ('\x81', utf8Char[1]);

  // devanagari short a
  retval = utf8::encode(U'\U00000904', utf8Char.begin());
  EXPECT_EQ(&utf8Char[0] + 3, retval);
  EXPECT_EQ('\xE0', utf8Char[0]);
  EXPECT_EQ('\xA4', utf8Char[1]);
  EXPECT_EQ('\x84', utf8Char[2]);

  // pau cin hau letter pa
  retval = utf8::encode(U'\U00011AC0', utf8Char.begin());
  EXPECT_EQ(&utf8Char[0] + 4, retval);
  EXPECT_EQ('\xF0', utf8Char[0]);
  EXPECT_EQ('\x91', utf8Char[1]);
  EXPECT_EQ('\xAB', utf8Char[2]);
  EXPECT_EQ('\x80', utf8Char[3]);
}



TEST_F(TestCharacterEncodings, Utf8Decoding)
{
  std::array<utf8::code_unit, 4u> utf8Char;
  auto retval = utf8Char.begin();
  CodePoint charCode;

  // a
  utf8Char[0] = '\x61';
  utf8Char[1] = '\x00';
  utf8Char[2] = '\x00';
  utf8Char[3] = '\x00';
  retval = utf8::decode(utf8Char.begin(), utf8Char.end(), charCode);
  EXPECT_EQ(U'\U00000061', charCode);
  EXPECT_EQ(&utf8Char[0] + 1, retval);

  // a with macron
  utf8Char[0] = '\xC4';
  utf8Char[1] = '\x81';
  utf8Char[2] = '\x00';
  utf8Char[3] = '\x00';
  retval = utf8::decode(utf8Char.begin(), utf8Char.end(), charCode);
  EXPECT_EQ(U'\U00000101', charCode);
  EXPECT_EQ(&utf8Char[0] + 2, retval);

  // devanagari short a
  utf8Char[0] = '\xE0';
  utf8Char[1] = '\xA4';
  utf8Char[2] = '\x84';
  utf8Char[3] = '\x00';
  retval = utf8::decode(utf8Char.begin(), utf8Char.end(), charCode);
  EXPECT_EQ(U'\U00000904', charCode);
  EXPECT_EQ(&utf8Char[0] + 3, retval);

  // pau cin hau letter pa
  utf8Char[0] = '\xF0';
  utf8Char[1] = '\x91';
  utf8Char[2] = '\xAB';
  utf8Char[3] = '\x80';
  std::cout << utf8Char.data() << std::endl;
  retval = utf8::decode(utf8Char.begin(), utf8Char.end(), charCode);
  EXPECT_EQ(U'\U00011AC0', charCode);
  EXPECT_EQ(&utf8Char[0] + 4, retval);
}



TEST_F(TestCharacterEncodingsDeathTest, Utf8DecodingFailure)
{
  std::array<utf8::code_unit, 4u> utf8Char{'\xF0', '\x91', '\xAB', '\x80'};
  CodePoint charCode;

  HOU_EXPECT_ERROR(utf8::decode(utf8Char.end(), utf8Char.begin(), charCode)
    , std::logic_error, getText(CorError::Precondition));
}



TEST_F(TestCharacterEncodings, Utf8Next)
{
  std::array<utf8::code_unit, 4u> utf8Char;
  auto retval = utf8Char.begin();

  // a
  utf8Char[0] = '\x61';
  utf8Char[1] = '\x00';
  utf8Char[2] = '\x00';
  utf8Char[3] = '\x00';
  retval = utf8::next(utf8Char.begin(), utf8Char.end());
  EXPECT_EQ(&utf8Char[0] + 1, retval);

  // a with macron
  utf8Char[0] = '\xC4';
  utf8Char[1] = '\x81';
  utf8Char[2] = '\x00';
  utf8Char[3] = '\x00';
  retval = utf8::next(utf8Char.begin(), utf8Char.end());
  EXPECT_EQ(&utf8Char[0] + 2, retval);

  // devanagari short a
  utf8Char[0] = '\xE0';
  utf8Char[1] = '\xA4';
  utf8Char[2] = '\x84';
  utf8Char[3] = '\x00';
  retval = utf8::next(utf8Char.begin(), utf8Char.end());
  EXPECT_EQ(&utf8Char[0] + 3, retval);

  // pau cin hau letter pa
  utf8Char[0] = '\xF0';
  utf8Char[1] = '\x91';
  utf8Char[2] = '\xAB';
  utf8Char[3] = '\x80';
  retval = utf8::next(utf8Char.begin(), utf8Char.end());
  EXPECT_EQ(&utf8Char[0] + 4, retval);
}



TEST_F(TestCharacterEncodingsDeathTest, Utf8NextFailure)
{
  std::array<utf8::code_unit, 4u> utf8Char;
  HOU_EXPECT_ERROR(utf8::next(utf8Char.end(), utf8Char.begin())
    , std::logic_error, getText(CorError::Precondition));
}



TEST_F(TestCharacterEncodings, Utf8Count)
{
  std::array<utf8::code_unit, 32u> utf8String;
  auto next = utf8String.begin();

  EXPECT_EQ(0u, utf8::count(utf8String.begin(), next));

  next = utf8::encode(0x61, next);
  EXPECT_EQ(1u, utf8::count(utf8String.begin(), next));

  next = utf8::encode(0x11AC0, next);
  EXPECT_EQ(2u, utf8::count(utf8String.begin(), next));

  next = utf8::encode(0x101, next);
  EXPECT_EQ(3u, utf8::count(utf8String.begin(), next));

  next = utf8::encode(0x0904, next);
  EXPECT_EQ(4u, utf8::count(utf8String.begin(), next));

  next = utf8::encode(0x61, next);
  EXPECT_EQ(5u, utf8::count(utf8String.begin(), next));

  next = utf8::encode(0x61, next);
  EXPECT_EQ(6u, utf8::count(utf8String.begin(), next));

  next = utf8::encode(0x101, next);
  EXPECT_EQ(7u, utf8::count(utf8String.begin(), next));

  next = utf8::encode(0x101, next);
  EXPECT_EQ(8u, utf8::count(utf8String.begin(), next));
}



TEST_F(TestCharacterEncodingsDeathTest, Utf8CountFailure)
{
  std::array<utf8::code_unit, 32u> utf8String;
  HOU_EXPECT_ERROR(utf8::count(utf8String.end(), utf8String.begin())
    , std::logic_error, getText(CorError::Precondition));
}



TEST_F(TestCharacterEncodings, Utf16Encoding)
{
  std::array<utf16::code_unit, 2u> utf16Char;
  auto retval = utf16Char.begin();

  // a
  retval = utf16::encode(U'\U00000061', utf16Char.begin());
  EXPECT_EQ(&utf16Char[0] + 1, retval);
  EXPECT_EQ(u'\x0061', utf16Char[0]);

  // a with macron
  retval = utf16::encode(U'\U00000101', utf16Char.begin());
  EXPECT_EQ(&utf16Char[0] + 1, retval);
  EXPECT_EQ(u'\x0101', utf16Char[0]);

  // devanagari short a
  retval = utf16::encode(U'\U00000904', utf16Char.begin());
  EXPECT_EQ(&utf16Char[0] + 1, retval);
  EXPECT_EQ(u'\x0904', utf16Char[0]);

  // pau cin hau letter pa
  retval = utf16::encode(U'\U00011AC0', utf16Char.begin());
  EXPECT_EQ(&utf16Char[0] + 2, retval);
  EXPECT_EQ(u'\xD806', utf16Char[0]);
  EXPECT_EQ(u'\xDEC0', utf16Char[1]);
}



TEST_F(TestCharacterEncodings, Utf16Decoding)
{
  std::array<utf16::code_unit, 2u> utf16Char;
  auto retval = utf16Char.begin();
  CodePoint charCode;

  // a
  utf16Char[0] = u'\x0061';
  retval = utf16::decode(utf16Char.begin(), utf16Char.end(), charCode);
  EXPECT_EQ(U'\U00000061', charCode);
  EXPECT_EQ(&utf16Char[0] + 1, retval);

  // a with macron
  utf16Char[0] = u'\x0101';
  retval = utf16::decode(utf16Char.begin(), utf16Char.end(), charCode);
  EXPECT_EQ(U'\U00000101', charCode);
  EXPECT_EQ(&utf16Char[0] + 1, retval);

  // devanagari short a
  utf16Char[0] = u'\x0904';
  retval = utf16::decode(utf16Char.begin(), utf16Char.end(), charCode);
  EXPECT_EQ(U'\U00000904', charCode);
  EXPECT_EQ(&utf16Char[0] + 1, retval);

  // pau cin hau letter pa
  utf16Char[0] = u'\xD806';
  utf16Char[1] = u'\xDEC0';
  retval = utf16::decode(utf16Char.begin(), utf16Char.end(), charCode);
  EXPECT_EQ(U'\U00011AC0', charCode);
  EXPECT_EQ(&utf16Char[0] + 2, retval);
}




TEST_F(TestCharacterEncodingsDeathTest, Utf16DecodingFailure)
{
  std::array<utf16::code_unit, 2u> utf16Char = {u'\xD806', u'\xDEC0'};
  CodePoint charCode;

  HOU_EXPECT_ERROR(utf16::decode(utf16Char.end(), utf16Char.begin(), charCode)
    , std::logic_error, getText(CorError::Precondition));
}



TEST_F(TestCharacterEncodings, Utf16Next)
{
  std::array<utf16::code_unit, 2u> utf16Char;
  auto retval = utf16Char.begin();

  // a
  utf16Char[0] = u'\x0061';
  retval = utf16::next(utf16Char.begin(), utf16Char.end());
  EXPECT_EQ(&utf16Char[0] + 1, retval);

  // a with macron
  utf16Char[0] = u'\x0101';
  retval = utf16::next(utf16Char.begin(), utf16Char.end());
  EXPECT_EQ(&utf16Char[0] + 1, retval);

  // devanagari short a
  utf16Char[0] = u'\x0904';
  retval = utf16::next(utf16Char.begin(), utf16Char.end());
  EXPECT_EQ(&utf16Char[0] + 1, retval);

  // pau cin hau letter pa
  utf16Char[0] = u'\xD806';
  utf16Char[1] = u'\xDEC0';
  retval = utf16::next(utf16Char.begin(), utf16Char.end());
  EXPECT_EQ(&utf16Char[0] + 2, retval);
}



TEST_F(TestCharacterEncodingsDeathTest, Utf16NextFailure)
{
  std::array<utf16::code_unit, 2u> utf16Char;
  HOU_EXPECT_ERROR(utf16::next(utf16Char.end(), utf16Char.begin())
    , std::logic_error, getText(CorError::Precondition));
}



TEST_F(TestCharacterEncodings, Utf16Count)
{
  std::array<utf16::code_unit, 16u> utf16String;
  auto next = utf16String.begin();

  EXPECT_EQ(0u, utf16::count(utf16String.begin(), next));

  next = utf16::encode(U'\U00000061', next);
  EXPECT_EQ(1u, utf16::count(utf16String.begin(), next));

  next = utf16::encode(U'\U00011AC0', next);
  EXPECT_EQ(2u, utf16::count(utf16String.begin(), next));

  next = utf16::encode(U'\U00000101', next);
  EXPECT_EQ(3u, utf16::count(utf16String.begin(), next));

  next = utf16::encode(U'\U00000904', next);
  EXPECT_EQ(4u, utf16::count(utf16String.begin(), next));

  next = utf16::encode(U'\U00000061', next);
  EXPECT_EQ(5u, utf16::count(utf16String.begin(), next));

  next = utf16::encode(U'\U00000061', next);
  EXPECT_EQ(6u, utf16::count(utf16String.begin(), next));

  next = utf16::encode(U'\U00000101', next);
  EXPECT_EQ(7u, utf16::count(utf16String.begin(), next));

  next = utf16::encode(U'\U00000101', next);
  EXPECT_EQ(8u, utf16::count(utf16String.begin(), next));
}



TEST_F(TestCharacterEncodingsDeathTest, Utf16CountDeathTest)
{
  std::array<utf16::code_unit, 16u> utf16String;
  HOU_EXPECT_ERROR(utf16::count(utf16String.end(), utf16String.begin())
    , std::logic_error, getText(CorError::Precondition));
}



TEST_F(TestCharacterEncodings, Utf32Encoding)
{
  std::array<utf32::code_unit, 1u> utf32Char;
  auto retval = utf32Char.begin();

  // a
  retval = utf32::encode(U'\U00000061', utf32Char.begin());
  EXPECT_EQ(&utf32Char[0] + 1, retval);
  EXPECT_EQ(U'\U00000061', utf32Char[0]);

  // a with macron
  retval = utf32::encode(U'\U00000101', utf32Char.begin());
  EXPECT_EQ(&utf32Char[0] + 1, retval);
  EXPECT_EQ(U'\U00000101', utf32Char[0]);

  // devanagari short a
  retval = utf32::encode(U'\U00000904', utf32Char.begin());
  EXPECT_EQ(&utf32Char[0] + 1, retval);
  EXPECT_EQ(U'\U00000904', utf32Char[0]);

  // pau cin hau letter pa
  retval = utf32::encode(U'\U00011AC0', utf32Char.begin());
  EXPECT_EQ(&utf32Char[0] + 1, retval);
  EXPECT_EQ(U'\U00011AC0', utf32Char[0]);
}



TEST_F(TestCharacterEncodings, Utf32Decoding)
{
  std::array<utf32::code_unit, 1u> utf32Char;
  auto retval = utf32Char.begin();
  CodePoint charCode;

  // a
  utf32Char[0] = U'\U00000061';
  retval = utf32::decode(utf32Char.begin(), utf32Char.end(), charCode);
  EXPECT_EQ(U'\U00000061', charCode);
  EXPECT_EQ(&utf32Char[0] + 1, retval);

  // a with macron
  utf32Char[0] = U'\U00000101';
  retval = utf32::decode(utf32Char.begin(), utf32Char.end(), charCode);
  EXPECT_EQ(U'\U00000101', charCode);
  EXPECT_EQ(&utf32Char[0] + 1, retval);

  // devanagari short a
  utf32Char[0] = U'\U00000904';
  retval = utf32::decode(utf32Char.begin(), utf32Char.end(), charCode);
  EXPECT_EQ(U'\U00000904', charCode);
  EXPECT_EQ(&utf32Char[0] + 1, retval);

  // pau cin hau letter pa
  utf32Char[0] = U'\U00011AC0';
  retval = utf32::decode(utf32Char.begin(), utf32Char.end(), charCode);
  EXPECT_EQ(U'\U00011AC0', charCode);
  EXPECT_EQ(&utf32Char[0] + 1, retval);
}



TEST_F(TestCharacterEncodingsDeathTest, Utf32DecodingFailure)
{
  std::array<utf32::code_unit, 1u> utf32Char = {U'\U00000012'};
  CodePoint charCode;

  HOU_EXPECT_ERROR(utf32::decode(utf32Char.end(), utf32Char.begin(), charCode)
    , std::logic_error, getText(CorError::Precondition));
}



TEST_F(TestCharacterEncodings, Utf32Next)
{
  std::array<utf32::code_unit, 1u> utf32Char;
  auto retval = utf32Char.begin();

  // a
  utf32Char[0] = U'\U00000061';
  retval = utf32::next(utf32Char.begin(), utf32Char.end());
  EXPECT_EQ(&utf32Char[0] + 1, retval);

  // a with macron
  utf32Char[0] = U'\U00000101';
  retval = utf32::next(utf32Char.begin(), utf32Char.end());
  EXPECT_EQ(&utf32Char[0] + 1, retval);

  // devanagari short a
  utf32Char[0] = U'\U00000904';
  retval = utf32::next(utf32Char.begin(), utf32Char.end());
  EXPECT_EQ(&utf32Char[0] + 1, retval);

  // pau cin hau letter pa
  utf32Char[0] = U'\U00011AC0';
  retval = utf32::next(utf32Char.begin(), utf32Char.end());
  EXPECT_EQ(&utf32Char[0] + 1, retval);
}



TEST_F(TestCharacterEncodingsDeathTest, Utf32NextFaillure)
{
  std::array<utf32::code_unit, 1u> utf32Char;
  HOU_EXPECT_ERROR(utf32::next(utf32Char.end(), utf32Char.begin())
    , std::logic_error, getText(CorError::Precondition));
}



TEST_F(TestCharacterEncodings, Utf32Count)
{
  std::array<utf32::code_unit, 8u> utf32String;
  auto next = utf32String.begin();

  EXPECT_EQ(0u, utf32::count(utf32String.begin(), next));

  next = utf32::encode(U'\U00000061', next);
  EXPECT_EQ(1u, utf32::count(utf32String.begin(), next));

  next = utf32::encode(U'\U00011AC0', next);
  EXPECT_EQ(2u, utf32::count(utf32String.begin(), next));

  next = utf32::encode(U'\U00000101', next);
  EXPECT_EQ(3u, utf32::count(utf32String.begin(), next));

  next = utf32::encode(U'\U00000904', next);
  EXPECT_EQ(4u, utf32::count(utf32String.begin(), next));

  next = utf32::encode(U'\U00000061', next);
  EXPECT_EQ(5u, utf32::count(utf32String.begin(), next));

  next = utf32::encode(U'\U00000061', next);
  EXPECT_EQ(6u, utf32::count(utf32String.begin(), next));

  next = utf32::encode(U'\U00000101', next);
  EXPECT_EQ(7u, utf32::count(utf32String.begin(), next));

  next = utf32::encode(U'\U00000101', next);
  EXPECT_EQ(8u, utf32::count(utf32String.begin(), next));
}



TEST_F(TestCharacterEncodingsDeathTest, Utf32CountFailure)
{
  std::array<utf32::code_unit, 8u> utf32String;
  HOU_EXPECT_ERROR(utf32::count(utf32String.end(), utf32String.begin())
    , std::logic_error, getText(CorError::Precondition));
}



TEST_F(TestCharacterEncodings, WideEncoding)
{
  std::array<wide::code_unit, 1u> wideChar;
  auto retval = wideChar.begin();

  // a
  retval = wide::encode(U'\U00000061', wideChar.begin());
  EXPECT_EQ(&wideChar[0] + 1, retval);
  EXPECT_EQ(0x0061, wideChar[0]);

  retval = wide::encode(U'\U00000101', wideChar.begin());
  EXPECT_EQ(&wideChar[0] + 1, retval);
  EXPECT_EQ(0x0101, wideChar[0]);

  retval = wide::encode(U'\U00000904', wideChar.begin());
  EXPECT_EQ(&wideChar[0] + 1, retval);
  EXPECT_EQ(0x0904, wideChar[0]);
}



TEST_F(TestCharacterEncodings, WideDecoding)
{
  std::array<wide::code_unit, 1u> wideChar;
  auto retval = wideChar.begin();
  CodePoint charCode;

  // a
  wideChar[0] = 0x0061;
  retval = wide::decode(wideChar.begin(), wideChar.end(), charCode);
  EXPECT_EQ(U'\U00000061', charCode);
  EXPECT_EQ(&wideChar[0] + 1, retval);

  // a with macron
  wideChar[0] = 0x0101;
  retval = wide::decode(wideChar.begin(), wideChar.end(), charCode);
  EXPECT_EQ(U'\U00000101', charCode);
  EXPECT_EQ(&wideChar[0] + 1, retval);

  // devanagari short a
  wideChar[0] = 0x0904;
  retval = wide::decode(wideChar.begin(), wideChar.end(), charCode);
  EXPECT_EQ(U'\U00000904', charCode);
  EXPECT_EQ(&wideChar[0] + 1, retval);
}



TEST_F(TestCharacterEncodingsDeathTest, WideDecodingFailure)
{
  wide::code_unit wideChar;
  CodePoint charCode;

  HOU_EXPECT_ERROR(wide::decode(&wideChar + 1, &wideChar, charCode)
    , std::logic_error, getText(CorError::Precondition));
}



TEST_F(TestCharacterEncodings, WideNext)
{
  std::array<wide::code_unit, 2u> wideChar;
  auto retval = wideChar.begin();

  // a
  wideChar[0] = u'\x0061';
  retval = wide::next(wideChar.begin(), wideChar.end());
  EXPECT_EQ(&wideChar[0] + 1, retval);

  // a with macron
  wideChar[0] = u'\x0101';
  retval = wide::next(wideChar.begin(), wideChar.end());
  EXPECT_EQ(&wideChar[0] + 1, retval);

  // devanagari short a
  wideChar[0] = u'\x0904';
  retval = wide::next(wideChar.begin(), wideChar.end());
  EXPECT_EQ(&wideChar[0] + 1, retval);
}




TEST_F(TestCharacterEncodingsDeathTest, WideNextFailure)
{
  wide::code_unit wideChar;
  HOU_EXPECT_ERROR(wide::next(&wideChar + 2, &wideChar + 1)
    , std::logic_error, getText(CorError::Precondition));
}



TEST_F(TestCharacterEncodings, WideCount)
{
  wide::code_unit wideString[] = L"hello!";
  EXPECT_EQ(7u, wide::count(wideString, wideString + 7));
}



TEST_F(TestCharacterEncodingsDeathTest, WideCountFailure)
{
  wide::code_unit wideString[] = L"hello!";
  HOU_EXPECT_ERROR(wide::count(wideString + 4, wideString + 3)
    , std::logic_error, getText(CorError::Precondition));
}



TEST_F(TestCharacterEncodings, Utf32Utf16Conversion)
{
  utf32::code_unit utf32Ref[] = {U'\U00000061', U'\U00011AC0', U'\U00000101'
    , U'\U00000904'};
  utf32::code_unit utf32Str[4] = {0};
  utf16::code_unit utf16Ref[] = {u'\x0061', u'\xD806', u'\xDEC0', u'\x0101'
    , u'\x0904'};
  utf16::code_unit utf16Str[5] = {0};

  convertEncoding<utf32, utf16>(utf32Ref, utf32Ref + 4, utf16Str);
  convertEncoding<utf16, utf32>(utf16Ref, utf16Ref + 5, utf32Str);

  HOU_EXPECT_ARRAY_EQ(utf32Ref, utf32Str, 4);
  HOU_EXPECT_ARRAY_EQ(utf16Ref, utf16Str, 5);
}



TEST_F(TestCharacterEncodings, Utf32Utf8Conversion)
{
  utf32::code_unit utf32Ref[] = {U'\U00000061', U'\U00011AC0', U'\U00000101'
    , U'\U00000904'};
  utf32::code_unit utf32Str[4] = {0};
  utf8::code_unit utf8Ref[] = {'\x61', '\xF0', '\x91', '\xAB', '\x80', '\xC4'
    , '\x81', '\xE0', '\xA4', '\x84'};
  utf8::code_unit utf8Str[10] = {0};

  convertEncoding<utf32, utf8>(utf32Ref, utf32Ref + 4, utf8Str);
  convertEncoding<utf8, utf32>(utf8Ref, utf8Ref + 10, utf32Str);

  HOU_EXPECT_ARRAY_EQ(utf32Ref, utf32Str, 4);
  HOU_EXPECT_ARRAY_EQ(utf8Ref, utf8Str, 10);
}



TEST_F(TestCharacterEncodings, Utf16Utf8Conversion)
{
  utf16::code_unit utf16Ref[] = {u'\x0061', u'\xD806', u'\xDEC0', u'\x0101'
    , u'\x0904'};
  utf16::code_unit utf16Str[5] = {0};
  utf8::code_unit utf8Ref[] = {'\x61', '\xF0', '\x91', '\xAB', '\x80', '\xC4'
    , '\x81', '\xE0', '\xA4', '\x84'};
  utf8::code_unit utf8Str[10] = {0};

  convertEncoding<utf16, utf8>(utf16Ref, utf16Ref + 5, utf8Str);
  convertEncoding<utf8, utf16>(utf8Ref, utf8Ref + 10, utf16Str);

  HOU_EXPECT_ARRAY_EQ(utf16Ref, utf16Str, 5);
  HOU_EXPECT_ARRAY_EQ(utf8Ref, utf8Str, 10);
}




TEST_F(TestCharacterEncodings, StringEncodingConversion)
{
  std::string utf8Ref = u8"\U00000061\U00011AC0\U00000101\U00000904";
  std::u16string utf16Ref = u"\U00000061\U00011AC0\U00000101\U00000904";
  std::u32string utf32Ref = U"\U00000061\U00011AC0\U00000101\U00000904";

  std::string u16to8 = convertEncoding<utf16, utf8>(utf16Ref);
  EXPECT_EQ(utf8Ref, u16to8);

  std::string u32to8 = convertEncoding<utf32, utf8>(utf32Ref);
  EXPECT_EQ(utf8Ref, u32to8);

  std::u16string u8to16 = convertEncoding<utf8, utf16>(utf8Ref);
  EXPECT_EQ(utf16Ref, u8to16);

  std::u16string u32to16 = convertEncoding<utf32, utf16>(utf32Ref);
  EXPECT_EQ(utf16Ref, u32to16);

  std::u32string u8to32 = convertEncoding<utf8, utf32>(utf8Ref);
  EXPECT_EQ(utf32Ref, u8to32);

  std::u32string u16to32 = convertEncoding<utf16, utf32>(utf16Ref);
  EXPECT_EQ(utf32Ref, u16to32);

}

