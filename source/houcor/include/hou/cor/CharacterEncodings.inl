// Houzi Game Engine
// Copyright (c) 2018 Davide Corradi
// Licensed under the MIT license.

namespace hou
{

template <typename OutputIt>
  OutputIt Utf8::encode(CodePoint input, OutputIt outFirst)
{
  static constexpr std::array<CodeUnit, 4u> sStartSignatures
  {
    0b00000000,
    0b11000000,
    0b11100000,
    0b11110000,
  };

  // Determine size of the character in code units based on its code point.
  // A maximum of 4 code units is needed.
  size_t nUnits =  input < 0x80 ? 1u
  : input < 0x800 ? 2u
  : input < 0x10000 ? 3u
  : 4u;

  std::array<uchar, 4u> units;
  for(size_t i = nUnits - 1; i > 0; --i)
  {
    // For trailing units, the two leftmost bits must be 10.
    units[i] = static_cast<uchar>((input | 0b10000000) & 0b10111111);
    input >>= 6;
  }
  units[0] = static_cast<uchar>(input | sStartSignatures[nUnits - 1]);

  // Copy into the outFirst and return iterator the next element.
  return std::copy(units.begin(), units.begin() + nUnits, outFirst);
}



template <typename InputIt>
  InputIt Utf8::decode(InputIt inFirst, InputIt inLast, CodePoint& out)
{
  static constexpr std::array<CodePoint, 4u> offsets
  {
    0x00000000,
    0x00003080,
    0x000E2080,
    0x03C82080,
  };

  size_t nTrailingUnits = countTrailingUnits(*inFirst);

  HOU_EXPECT(inFirst + nTrailingUnits < inLast);

  out = 0;
  for(size_t i = 0; i < nTrailingUnits; ++i)
  {
    // The ugly cast is done because char could be signed or unsigned, nut
    // we want to treat it as an unsigned type in all cases.
    out += static_cast<CodePoint>(*reinterpret_cast<const uchar*>(&*inFirst++));
    out <<= 6;
  }
  out += static_cast<CodePoint>(*reinterpret_cast<const uchar*>(&*inFirst++));

  // Remove offsets due to the 10... signatures in the trailing bytes.
  out -= offsets[nTrailingUnits];

  return inFirst;
}



template <typename InputIt>
  InputIt Utf8::next(InputIt inFirst, InputIt inLast)
{
  InputIt next = inFirst + countTrailingUnits(*inFirst) + 1;
  HOU_EXPECT(next <= inLast);
  return next;
}



template <typename InputIt>
  size_t Utf8::count(InputIt inFirst, InputIt inLast)
{
  HOU_EXPECT(inFirst <= inLast);
  size_t count = 0;
  while(inFirst < inLast)
  {
    inFirst = next(inFirst, inLast);
    ++count;
  }
  return count;
}



size_t Utf8::countTrailingUnits(CodeUnit cu)
{
  static constexpr std::array<CodeUnit, 16u> sTrailingUnits
  {
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 1, 1, 2, 3,
  };
  return sTrailingUnits[(*reinterpret_cast<uchar*>(&cu)) >> 4];
}



template <typename OutputIt>
  OutputIt Utf16::encode(CodePoint in, OutputIt outFirst)
{
  if(in <= 0xFFFF)
  {
    // One code unit. Direct conversion.
    *outFirst++ = static_cast<CodeUnit>(in);
  }
  else
  {
    // Two code units. Need to take care of masking signature bits.
    in -= 0x00010000;
    *outFirst++ = static_cast<CodeUnit>(in >> 10) + 0xD800;
    *outFirst++ = static_cast<CodeUnit>(in & 0b0000001111111111) + 0xDC00;
  }

  return outFirst;
}



template <typename InputIt>
  InputIt Utf16::decode(InputIt inFirst, InputIt inLast, CodePoint& out)
{
  CodeUnit e1 = *inFirst++;

  if(e1 < 0xD800 || e1 > 0xDBFF)
  {
    // One code unit.
    HOU_EXPECT(inFirst <= inLast);
    out = e1;
  }
  else
  {
    // Two code units
    HOU_EXPECT(inFirst < inLast);
    CodeUnit e2 = *inFirst++;
    HOU_EXPECT(((e2 >= 0xDC00) && (e2 <= 0xDFFF)));
    out = static_cast<CodePoint>(((e1 - 0xD800) << 10) + (e2 - 0xDC00)
      + 0x0010000);
  }

  return inFirst;
}



template <typename InputIt>
  InputIt Utf16::next(InputIt inFirst, InputIt inLast)
{
  InputIt next = inFirst + ((*inFirst < 0xD800 || *inFirst > 0xDBFF) ? 1 : 2);
  HOU_EXPECT(next <= inLast);
  return next;
}



template <typename InputIt>
  size_t Utf16::count(InputIt inFirst, InputIt inLast)
{
  HOU_EXPECT(inFirst <= inLast);
  size_t length = 0;
  while(inFirst < inLast)
  {
    inFirst = next(inFirst, inLast);
    ++length;
  }
  return length;
}



template <typename OutputIt>
  OutputIt Utf32::encode(CodePoint in, OutputIt outFirst)
{
  *outFirst = in;
  return ++outFirst;
}



template <typename InputIt>
  InputIt Utf32::decode(InputIt inFirst, InputIt inLast, CodePoint& out)
{
  HOU_EXPECT(inFirst < inLast);
  out = *inFirst;
  return ++inFirst;
}



template <typename InputIt>
  InputIt Utf32::next(InputIt inFirst, InputIt inLast)
{
  HOU_EXPECT(inFirst < inLast);
  return ++inFirst;
}



template <typename InputIt>
  size_t Utf32::count(InputIt inFirst, InputIt inLast)
{
  HOU_EXPECT(inFirst <= inLast);
  return inLast - inFirst;
}



template <typename OutputIt>
  OutputIt Wide::encode(CodePoint in, OutputIt outFirst)
{
#if defined(HOU_SYSTEM_WINDOWS)
  return Utf16::encode(in, outFirst);
#else
  return Utf32::encode(in, outFirst);
#endif
}



template <typename InputIt>
  InputIt Wide::decode(InputIt inFirst, InputIt inLast, CodePoint& out)
{
#if defined(HOU_SYSTEM_WINDOWS)
  return Utf16::decode(inFirst, inLast, out);
#else
  return Utf32::decode(inFirst, inLast, out);
#endif
}



template <typename InputIt>
  InputIt Wide::next(InputIt inFirst, InputIt inLast)
{
#if defined(HOU_SYSTEM_WINDOWS)
  return Utf16::next(inFirst, inLast);
#else
  return Utf32::next(inFirst, inLast);
#endif
}



template <typename InputIt>
  size_t Wide::count(InputIt inFirst, InputIt inLast)
{
#if defined(HOU_SYSTEM_WINDOWS)
  return Utf16::count(inFirst, inLast);
#else
  return Utf32::count(inFirst, inLast);
#endif
}



template <typename InputEncoding, typename OutputEncoding
  , typename InputIt, typename OutputIt>
  OutputIt convertEncoding(InputIt inFirst, InputIt inLast, OutputIt outFirst)
{
  while(inFirst < inLast)
  {
    CodePoint codepoint;
    inFirst = InputEncoding::decode(inFirst, inLast, codepoint);
    outFirst = OutputEncoding::encode(codepoint, outFirst);
  }
  return outFirst;
}



template <typename InputEncoding, typename OutputEncoding>
  std::basic_string<typename OutputEncoding::CodeUnit> convertEncoding
  (const std::basic_string<typename InputEncoding::CodeUnit>& s)
{
  std::basic_string<typename OutputEncoding::CodeUnit> retval;
  convertEncoding<InputEncoding, OutputEncoding>(s.begin(), s.end()
    , std::back_inserter(retval));
  return retval;
}

}

