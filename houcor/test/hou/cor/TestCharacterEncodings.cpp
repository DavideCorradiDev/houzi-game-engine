// Houzi Game Engine
// Copyright (c) 2018 Davide Corradi
// Licensed under the MIT license.

#include "hou/Test.hpp"

#include "hou/cor/CharacterEncodings.hpp"

using namespace hou;
using namespace testing;



namespace
{

class TestCharacterEncodings : public Test {};
class TestCharacterEncodingsDeathTest : public TestCharacterEncodings {};

}



TEST_F(TestCharacterEncodings, Utf8Encoding)
{
  std::array<Utf8::CodeUnit, 4u> utf8Char;
  auto retval = utf8Char.begin();

  // a
  retval = Utf8::encode(U'\U00000061', utf8Char.begin());
  EXPECT_EQ(&utf8Char[0] + 1, retval);
  EXPECT_EQ('\x61', utf8Char[0]);

  // a with macron
  retval = Utf8::encode(U'\U00000101', utf8Char.begin());
  EXPECT_EQ(&utf8Char[0] + 2, retval);
  EXPECT_EQ('\xC4', utf8Char[0]);
  EXPECT_EQ('\x81', utf8Char[1]);

  // devanagari short a
  retval = Utf8::encode(U'\U00000904', utf8Char.begin());
  EXPECT_EQ(&utf8Char[0] + 3, retval);
  EXPECT_EQ('\xE0', utf8Char[0]);
  EXPECT_EQ('\xA4', utf8Char[1]);
  EXPECT_EQ('\x84', utf8Char[2]);

  // pau cin hau letter pa
  retval = Utf8::encode(U'\U00011AC0', utf8Char.begin());
  EXPECT_EQ(&utf8Char[0] + 4, retval);
  EXPECT_EQ('\xF0', utf8Char[0]);
  EXPECT_EQ('\x91', utf8Char[1]);
  EXPECT_EQ('\xAB', utf8Char[2]);
  EXPECT_EQ('\x80', utf8Char[3]);
}



TEST_F(TestCharacterEncodings, Utf8Decoding)
{
  std::array<Utf8::CodeUnit, 4u> utf8Char;
  auto retval = utf8Char.begin();
  CodePoint charCode;

  // a
  utf8Char[0] = '\x61';
  utf8Char[1] = '\x00';
  utf8Char[2] = '\x00';
  utf8Char[3] = '\x00';
  retval = Utf8::decode(utf8Char.begin(), utf8Char.end(), charCode);
  EXPECT_EQ(U'\U00000061', charCode);
  EXPECT_EQ(&utf8Char[0] + 1, retval);

  // a with macron
  utf8Char[0] = '\xC4';
  utf8Char[1] = '\x81';
  utf8Char[2] = '\x00';
  utf8Char[3] = '\x00';
  retval = Utf8::decode(utf8Char.begin(), utf8Char.end(), charCode);
  EXPECT_EQ(U'\U00000101', charCode);
  EXPECT_EQ(&utf8Char[0] + 2, retval);

  // devanagari short a
  utf8Char[0] = '\xE0';
  utf8Char[1] = '\xA4';
  utf8Char[2] = '\x84';
  utf8Char[3] = '\x00';
  retval = Utf8::decode(utf8Char.begin(), utf8Char.end(), charCode);
  EXPECT_EQ(U'\U00000904', charCode);
  EXPECT_EQ(&utf8Char[0] + 3, retval);

  // pau cin hau letter pa
  utf8Char[0] = '\xF0';
  utf8Char[1] = '\x91';
  utf8Char[2] = '\xAB';
  utf8Char[3] = '\x80';
  std::cout << utf8Char.data() << std::endl;
  retval = Utf8::decode(utf8Char.begin(), utf8Char.end(), charCode);
  EXPECT_EQ(U'\U00011AC0', charCode);
  EXPECT_EQ(&utf8Char[0] + 4, retval);
}



TEST_F(TestCharacterEncodingsDeathTest, Utf8DecodingFailure)
{
  std::array<Utf8::CodeUnit, 4u> utf8Char{'\xF0', '\x91', '\xAB', '\x80'};
  CodePoint charCode;

  HOU_EXPECT_ERROR(Utf8::decode(utf8Char.end(), utf8Char.begin(), charCode)
    , std::logic_error, getText(CorError::Precondition));
}



TEST_F(TestCharacterEncodings, Utf8Next)
{
  std::array<Utf8::CodeUnit, 4u> utf8Char;
  auto retval = utf8Char.begin();

  // a
  utf8Char[0] = '\x61';
  utf8Char[1] = '\x00';
  utf8Char[2] = '\x00';
  utf8Char[3] = '\x00';
  retval = Utf8::next(utf8Char.begin(), utf8Char.end());
  EXPECT_EQ(&utf8Char[0] + 1, retval);

  // a with macron
  utf8Char[0] = '\xC4';
  utf8Char[1] = '\x81';
  utf8Char[2] = '\x00';
  utf8Char[3] = '\x00';
  retval = Utf8::next(utf8Char.begin(), utf8Char.end());
  EXPECT_EQ(&utf8Char[0] + 2, retval);

  // devanagari short a
  utf8Char[0] = '\xE0';
  utf8Char[1] = '\xA4';
  utf8Char[2] = '\x84';
  utf8Char[3] = '\x00';
  retval = Utf8::next(utf8Char.begin(), utf8Char.end());
  EXPECT_EQ(&utf8Char[0] + 3, retval);

  // pau cin hau letter pa
  utf8Char[0] = '\xF0';
  utf8Char[1] = '\x91';
  utf8Char[2] = '\xAB';
  utf8Char[3] = '\x80';
  retval = Utf8::next(utf8Char.begin(), utf8Char.end());
  EXPECT_EQ(&utf8Char[0] + 4, retval);
}



TEST_F(TestCharacterEncodingsDeathTest, Utf8NextFailure)
{
  std::array<Utf8::CodeUnit, 4u> utf8Char;
  HOU_EXPECT_ERROR(Utf8::next(utf8Char.end(), utf8Char.begin())
    , std::logic_error, getText(CorError::Precondition));
}



TEST_F(TestCharacterEncodings, Utf8Count)
{
  std::array<Utf8::CodeUnit, 32u> utf8String;
  auto next = utf8String.begin();

  EXPECT_EQ(0u, Utf8::count(utf8String.begin(), next));

  next = Utf8::encode(0x61, next);
  EXPECT_EQ(1u, Utf8::count(utf8String.begin(), next));

  next = Utf8::encode(0x11AC0, next);
  EXPECT_EQ(2u, Utf8::count(utf8String.begin(), next));

  next = Utf8::encode(0x101, next);
  EXPECT_EQ(3u, Utf8::count(utf8String.begin(), next));

  next = Utf8::encode(0x0904, next);
  EXPECT_EQ(4u, Utf8::count(utf8String.begin(), next));

  next = Utf8::encode(0x61, next);
  EXPECT_EQ(5u, Utf8::count(utf8String.begin(), next));

  next = Utf8::encode(0x61, next);
  EXPECT_EQ(6u, Utf8::count(utf8String.begin(), next));

  next = Utf8::encode(0x101, next);
  EXPECT_EQ(7u, Utf8::count(utf8String.begin(), next));

  next = Utf8::encode(0x101, next);
  EXPECT_EQ(8u, Utf8::count(utf8String.begin(), next));
}



TEST_F(TestCharacterEncodingsDeathTest, Utf8CountFailure)
{
  std::array<Utf8::CodeUnit, 32u> utf8String;
  HOU_EXPECT_ERROR(Utf8::count(utf8String.end(), utf8String.begin())
    , std::logic_error, getText(CorError::Precondition));
}



TEST_F(TestCharacterEncodings, Utf16Encoding)
{
  std::array<Utf16::CodeUnit, 2u> utf16Char;
  auto retval = utf16Char.begin();

  // a
  retval = Utf16::encode(U'\U00000061', utf16Char.begin());
  EXPECT_EQ(&utf16Char[0] + 1, retval);
  EXPECT_EQ(u'\x0061', utf16Char[0]);

  // a with macron
  retval = Utf16::encode(U'\U00000101', utf16Char.begin());
  EXPECT_EQ(&utf16Char[0] + 1, retval);
  EXPECT_EQ(u'\x0101', utf16Char[0]);

  // devanagari short a
  retval = Utf16::encode(U'\U00000904', utf16Char.begin());
  EXPECT_EQ(&utf16Char[0] + 1, retval);
  EXPECT_EQ(u'\x0904', utf16Char[0]);

  // pau cin hau letter pa
  retval = Utf16::encode(U'\U00011AC0', utf16Char.begin());
  EXPECT_EQ(&utf16Char[0] + 2, retval);
  EXPECT_EQ(u'\xD806', utf16Char[0]);
  EXPECT_EQ(u'\xDEC0', utf16Char[1]);
}



TEST_F(TestCharacterEncodings, Utf16Decoding)
{
  std::array<Utf16::CodeUnit, 2u> utf16Char;
  auto retval = utf16Char.begin();
  CodePoint charCode;

  // a
  utf16Char[0] = u'\x0061';
  retval = Utf16::decode(utf16Char.begin(), utf16Char.end(), charCode);
  EXPECT_EQ(U'\U00000061', charCode);
  EXPECT_EQ(&utf16Char[0] + 1, retval);

  // a with macron
  utf16Char[0] = u'\x0101';
  retval = Utf16::decode(utf16Char.begin(), utf16Char.end(), charCode);
  EXPECT_EQ(U'\U00000101', charCode);
  EXPECT_EQ(&utf16Char[0] + 1, retval);

  // devanagari short a
  utf16Char[0] = u'\x0904';
  retval = Utf16::decode(utf16Char.begin(), utf16Char.end(), charCode);
  EXPECT_EQ(U'\U00000904', charCode);
  EXPECT_EQ(&utf16Char[0] + 1, retval);

  // pau cin hau letter pa
  utf16Char[0] = u'\xD806';
  utf16Char[1] = u'\xDEC0';
  retval = Utf16::decode(utf16Char.begin(), utf16Char.end(), charCode);
  EXPECT_EQ(U'\U00011AC0', charCode);
  EXPECT_EQ(&utf16Char[0] + 2, retval);
}




TEST_F(TestCharacterEncodingsDeathTest, Utf16DecodingFailure)
{
  std::array<Utf16::CodeUnit, 2u> utf16Char = {u'\xD806', u'\xDEC0'};
  CodePoint charCode;

  HOU_EXPECT_ERROR(Utf16::decode(utf16Char.end(), utf16Char.begin(), charCode)
    , std::logic_error, getText(CorError::Precondition));
}



TEST_F(TestCharacterEncodings, Utf16Next)
{
  std::array<Utf16::CodeUnit, 2u> utf16Char;
  auto retval = utf16Char.begin();

  // a
  utf16Char[0] = u'\x0061';
  retval = Utf16::next(utf16Char.begin(), utf16Char.end());
  EXPECT_EQ(&utf16Char[0] + 1, retval);

  // a with macron
  utf16Char[0] = u'\x0101';
  retval = Utf16::next(utf16Char.begin(), utf16Char.end());
  EXPECT_EQ(&utf16Char[0] + 1, retval);

  // devanagari short a
  utf16Char[0] = u'\x0904';
  retval = Utf16::next(utf16Char.begin(), utf16Char.end());
  EXPECT_EQ(&utf16Char[0] + 1, retval);

  // pau cin hau letter pa
  utf16Char[0] = u'\xD806';
  utf16Char[1] = u'\xDEC0';
  retval = Utf16::next(utf16Char.begin(), utf16Char.end());
  EXPECT_EQ(&utf16Char[0] + 2, retval);
}



TEST_F(TestCharacterEncodingsDeathTest, Utf16NextFailure)
{
  std::array<Utf16::CodeUnit, 2u> utf16Char;
  HOU_EXPECT_ERROR(Utf16::next(utf16Char.end(), utf16Char.begin())
    , std::logic_error, getText(CorError::Precondition));
}



TEST_F(TestCharacterEncodings, Utf16Count)
{
  std::array<Utf16::CodeUnit, 16u> utf16String;
  auto next = utf16String.begin();

  EXPECT_EQ(0u, Utf16::count(utf16String.begin(), next));

  next = Utf16::encode(U'\U00000061', next);
  EXPECT_EQ(1u, Utf16::count(utf16String.begin(), next));

  next = Utf16::encode(U'\U00011AC0', next);
  EXPECT_EQ(2u, Utf16::count(utf16String.begin(), next));

  next = Utf16::encode(U'\U00000101', next);
  EXPECT_EQ(3u, Utf16::count(utf16String.begin(), next));

  next = Utf16::encode(U'\U00000904', next);
  EXPECT_EQ(4u, Utf16::count(utf16String.begin(), next));

  next = Utf16::encode(U'\U00000061', next);
  EXPECT_EQ(5u, Utf16::count(utf16String.begin(), next));

  next = Utf16::encode(U'\U00000061', next);
  EXPECT_EQ(6u, Utf16::count(utf16String.begin(), next));

  next = Utf16::encode(U'\U00000101', next);
  EXPECT_EQ(7u, Utf16::count(utf16String.begin(), next));

  next = Utf16::encode(U'\U00000101', next);
  EXPECT_EQ(8u, Utf16::count(utf16String.begin(), next));
}



TEST_F(TestCharacterEncodingsDeathTest, Utf16CountDeathTest)
{
  std::array<Utf16::CodeUnit, 16u> utf16String;
  HOU_EXPECT_ERROR(Utf16::count(utf16String.end(), utf16String.begin())
    , std::logic_error, getText(CorError::Precondition));
}



TEST_F(TestCharacterEncodings, Utf32Encoding)
{
  std::array<Utf32::CodeUnit, 1u> utf32Char;
  auto retval = utf32Char.begin();

  // a
  retval = Utf32::encode(U'\U00000061', utf32Char.begin());
  EXPECT_EQ(&utf32Char[0] + 1, retval);
  EXPECT_EQ(U'\U00000061', utf32Char[0]);

  // a with macron
  retval = Utf32::encode(U'\U00000101', utf32Char.begin());
  EXPECT_EQ(&utf32Char[0] + 1, retval);
  EXPECT_EQ(U'\U00000101', utf32Char[0]);

  // devanagari short a
  retval = Utf32::encode(U'\U00000904', utf32Char.begin());
  EXPECT_EQ(&utf32Char[0] + 1, retval);
  EXPECT_EQ(U'\U00000904', utf32Char[0]);

  // pau cin hau letter pa
  retval = Utf32::encode(U'\U00011AC0', utf32Char.begin());
  EXPECT_EQ(&utf32Char[0] + 1, retval);
  EXPECT_EQ(U'\U00011AC0', utf32Char[0]);
}



TEST_F(TestCharacterEncodings, Utf32Decoding)
{
  std::array<Utf32::CodeUnit, 1u> utf32Char;
  auto retval = utf32Char.begin();
  CodePoint charCode;

  // a
  utf32Char[0] = U'\U00000061';
  retval = Utf32::decode(utf32Char.begin(), utf32Char.end(), charCode);
  EXPECT_EQ(U'\U00000061', charCode);
  EXPECT_EQ(&utf32Char[0] + 1, retval);

  // a with macron
  utf32Char[0] = U'\U00000101';
  retval = Utf32::decode(utf32Char.begin(), utf32Char.end(), charCode);
  EXPECT_EQ(U'\U00000101', charCode);
  EXPECT_EQ(&utf32Char[0] + 1, retval);

  // devanagari short a
  utf32Char[0] = U'\U00000904';
  retval = Utf32::decode(utf32Char.begin(), utf32Char.end(), charCode);
  EXPECT_EQ(U'\U00000904', charCode);
  EXPECT_EQ(&utf32Char[0] + 1, retval);

  // pau cin hau letter pa
  utf32Char[0] = U'\U00011AC0';
  retval = Utf32::decode(utf32Char.begin(), utf32Char.end(), charCode);
  EXPECT_EQ(U'\U00011AC0', charCode);
  EXPECT_EQ(&utf32Char[0] + 1, retval);
}



TEST_F(TestCharacterEncodingsDeathTest, Utf32DecodingFailure)
{
  std::array<Utf32::CodeUnit, 1u> utf32Char = {U'\U00000012'};
  CodePoint charCode;

  HOU_EXPECT_ERROR(Utf32::decode(utf32Char.end(), utf32Char.begin(), charCode)
    , std::logic_error, getText(CorError::Precondition));
}



TEST_F(TestCharacterEncodings, Utf32Next)
{
  std::array<Utf32::CodeUnit, 1u> utf32Char;
  auto retval = utf32Char.begin();

  // a
  utf32Char[0] = U'\U00000061';
  retval = Utf32::next(utf32Char.begin(), utf32Char.end());
  EXPECT_EQ(&utf32Char[0] + 1, retval);

  // a with macron
  utf32Char[0] = U'\U00000101';
  retval = Utf32::next(utf32Char.begin(), utf32Char.end());
  EXPECT_EQ(&utf32Char[0] + 1, retval);

  // devanagari short a
  utf32Char[0] = U'\U00000904';
  retval = Utf32::next(utf32Char.begin(), utf32Char.end());
  EXPECT_EQ(&utf32Char[0] + 1, retval);

  // pau cin hau letter pa
  utf32Char[0] = U'\U00011AC0';
  retval = Utf32::next(utf32Char.begin(), utf32Char.end());
  EXPECT_EQ(&utf32Char[0] + 1, retval);
}



TEST_F(TestCharacterEncodingsDeathTest, Utf32NextFaillure)
{
  std::array<Utf32::CodeUnit, 1u> utf32Char;
  HOU_EXPECT_ERROR(Utf32::next(utf32Char.end(), utf32Char.begin())
    , std::logic_error, getText(CorError::Precondition));
}



TEST_F(TestCharacterEncodings, Utf32Count)
{
  std::array<Utf32::CodeUnit, 8u> utf32String;
  auto next = utf32String.begin();

  EXPECT_EQ(0u, Utf32::count(utf32String.begin(), next));

  next = Utf32::encode(U'\U00000061', next);
  EXPECT_EQ(1u, Utf32::count(utf32String.begin(), next));

  next = Utf32::encode(U'\U00011AC0', next);
  EXPECT_EQ(2u, Utf32::count(utf32String.begin(), next));

  next = Utf32::encode(U'\U00000101', next);
  EXPECT_EQ(3u, Utf32::count(utf32String.begin(), next));

  next = Utf32::encode(U'\U00000904', next);
  EXPECT_EQ(4u, Utf32::count(utf32String.begin(), next));

  next = Utf32::encode(U'\U00000061', next);
  EXPECT_EQ(5u, Utf32::count(utf32String.begin(), next));

  next = Utf32::encode(U'\U00000061', next);
  EXPECT_EQ(6u, Utf32::count(utf32String.begin(), next));

  next = Utf32::encode(U'\U00000101', next);
  EXPECT_EQ(7u, Utf32::count(utf32String.begin(), next));

  next = Utf32::encode(U'\U00000101', next);
  EXPECT_EQ(8u, Utf32::count(utf32String.begin(), next));
}



TEST_F(TestCharacterEncodingsDeathTest, Utf32CountFailure)
{
  std::array<Utf32::CodeUnit, 8u> utf32String;
  HOU_EXPECT_ERROR(Utf32::count(utf32String.end(), utf32String.begin())
    , std::logic_error, getText(CorError::Precondition));
}



TEST_F(TestCharacterEncodings, WideEncoding)
{
  std::array<Wide::CodeUnit, 1u> wideChar;
  auto retval = wideChar.begin();

  // a
  retval = Wide::encode(U'\U00000061', wideChar.begin());
  EXPECT_EQ(&wideChar[0] + 1, retval);
  EXPECT_EQ(0x0061, wideChar[0]);

  retval = Wide::encode(U'\U00000101', wideChar.begin());
  EXPECT_EQ(&wideChar[0] + 1, retval);
  EXPECT_EQ(0x0101, wideChar[0]);

  retval = Wide::encode(U'\U00000904', wideChar.begin());
  EXPECT_EQ(&wideChar[0] + 1, retval);
  EXPECT_EQ(0x0904, wideChar[0]);
}



TEST_F(TestCharacterEncodings, WideDecoding)
{
  std::array<Wide::CodeUnit, 1u> wideChar;
  auto retval = wideChar.begin();
  CodePoint charCode;

  // a
  wideChar[0] = 0x0061;
  retval = Wide::decode(wideChar.begin(), wideChar.end(), charCode);
  EXPECT_EQ(U'\U00000061', charCode);
  EXPECT_EQ(&wideChar[0] + 1, retval);

  // a with macron
  wideChar[0] = 0x0101;
  retval = Wide::decode(wideChar.begin(), wideChar.end(), charCode);
  EXPECT_EQ(U'\U00000101', charCode);
  EXPECT_EQ(&wideChar[0] + 1, retval);

  // devanagari short a
  wideChar[0] = 0x0904;
  retval = Wide::decode(wideChar.begin(), wideChar.end(), charCode);
  EXPECT_EQ(U'\U00000904', charCode);
  EXPECT_EQ(&wideChar[0] + 1, retval);
}



TEST_F(TestCharacterEncodingsDeathTest, WideDecodingFailure)
{
  Wide::CodeUnit wideChar;
  CodePoint charCode;

  HOU_EXPECT_ERROR(Wide::decode(&wideChar + 1, &wideChar, charCode)
    , std::logic_error, getText(CorError::Precondition));
}



TEST_F(TestCharacterEncodings, WideNext)
{
  std::array<Wide::CodeUnit, 2u> wideChar;
  auto retval = wideChar.begin();

  // a
  wideChar[0] = u'\x0061';
  retval = Wide::next(wideChar.begin(), wideChar.end());
  EXPECT_EQ(&wideChar[0] + 1, retval);

  // a with macron
  wideChar[0] = u'\x0101';
  retval = Wide::next(wideChar.begin(), wideChar.end());
  EXPECT_EQ(&wideChar[0] + 1, retval);

  // devanagari short a
  wideChar[0] = u'\x0904';
  retval = Wide::next(wideChar.begin(), wideChar.end());
  EXPECT_EQ(&wideChar[0] + 1, retval);
}




TEST_F(TestCharacterEncodingsDeathTest, WideNextFailure)
{
  Wide::CodeUnit wideChar;
  HOU_EXPECT_ERROR(Wide::next(&wideChar + 2, &wideChar + 1)
    , std::logic_error, getText(CorError::Precondition));
}



TEST_F(TestCharacterEncodings, WideCount)
{
  Wide::CodeUnit wideString[] = L"hello!";
  EXPECT_EQ(7u, Wide::count(wideString, wideString + 7));
}



TEST_F(TestCharacterEncodingsDeathTest, WideCountFailure)
{
  Wide::CodeUnit wideString[] = L"hello!";
  HOU_EXPECT_ERROR(Wide::count(wideString + 4, wideString + 3)
    , std::logic_error, getText(CorError::Precondition));
}



TEST_F(TestCharacterEncodings, Utf32Utf16Conversion)
{
  Utf32::CodeUnit utf32Ref[] = {U'\U00000061', U'\U00011AC0', U'\U00000101'
    , U'\U00000904'};
  Utf32::CodeUnit utf32Str[4] = {0};
  Utf16::CodeUnit utf16Ref[] = {u'\x0061', u'\xD806', u'\xDEC0', u'\x0101'
    , u'\x0904'};
  Utf16::CodeUnit utf16Str[5] = {0};

  convertEncoding<Utf32, Utf16>(utf32Ref, utf32Ref + 4, utf16Str);
  convertEncoding<Utf16, Utf32>(utf16Ref, utf16Ref + 5, utf32Str);

  HOU_EXPECT_ARRAY_EQ(utf32Ref, utf32Str, 4);
  HOU_EXPECT_ARRAY_EQ(utf16Ref, utf16Str, 5);
}



TEST_F(TestCharacterEncodings, Utf32Utf8Conversion)
{
  Utf32::CodeUnit utf32Ref[] = {U'\U00000061', U'\U00011AC0', U'\U00000101'
    , U'\U00000904'};
  Utf32::CodeUnit utf32Str[4] = {0};
  Utf8::CodeUnit utf8Ref[] = {'\x61', '\xF0', '\x91', '\xAB', '\x80', '\xC4'
    , '\x81', '\xE0', '\xA4', '\x84'};
  Utf8::CodeUnit utf8Str[10] = {0};

  convertEncoding<Utf32, Utf8>(utf32Ref, utf32Ref + 4, utf8Str);
  convertEncoding<Utf8, Utf32>(utf8Ref, utf8Ref + 10, utf32Str);

  HOU_EXPECT_ARRAY_EQ(utf32Ref, utf32Str, 4);
  HOU_EXPECT_ARRAY_EQ(utf8Ref, utf8Str, 10);
}



TEST_F(TestCharacterEncodings, Utf16Utf8Conversion)
{
  Utf16::CodeUnit utf16Ref[] = {u'\x0061', u'\xD806', u'\xDEC0', u'\x0101'
    , u'\x0904'};
  Utf16::CodeUnit utf16Str[5] = {0};
  Utf8::CodeUnit utf8Ref[] = {'\x61', '\xF0', '\x91', '\xAB', '\x80', '\xC4'
    , '\x81', '\xE0', '\xA4', '\x84'};
  Utf8::CodeUnit utf8Str[10] = {0};

  convertEncoding<Utf16, Utf8>(utf16Ref, utf16Ref + 5, utf8Str);
  convertEncoding<Utf8, Utf16>(utf8Ref, utf8Ref + 10, utf16Str);

  HOU_EXPECT_ARRAY_EQ(utf16Ref, utf16Str, 5);
  HOU_EXPECT_ARRAY_EQ(utf8Ref, utf8Str, 10);
}




TEST_F(TestCharacterEncodings, StringEncodingConversion)
{
  std::string utf8Ref = u8"\U00000061\U00011AC0\U00000101\U00000904";
  std::u16string utf16Ref = u"\U00000061\U00011AC0\U00000101\U00000904";
  std::u32string utf32Ref = U"\U00000061\U00011AC0\U00000101\U00000904";

  std::string u16to8 = convertEncoding<Utf16, Utf8>(utf16Ref);
  EXPECT_EQ(utf8Ref, u16to8);

  std::string u32to8 = convertEncoding<Utf32, Utf8>(utf32Ref);
  EXPECT_EQ(utf8Ref, u32to8);

  std::u16string u8to16 = convertEncoding<Utf8, Utf16>(utf8Ref);
  EXPECT_EQ(utf16Ref, u8to16);

  std::u16string u32to16 = convertEncoding<Utf32, Utf16>(utf32Ref);
  EXPECT_EQ(utf16Ref, u32to16);

  std::u32string u8to32 = convertEncoding<Utf8, Utf32>(utf8Ref);
  EXPECT_EQ(utf32Ref, u8to32);

  std::u32string u16to32 = convertEncoding<Utf16, Utf32>(utf16Ref);
  EXPECT_EQ(utf32Ref, u16to32);

}

