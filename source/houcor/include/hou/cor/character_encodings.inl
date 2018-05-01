// Houzi Game Engine
// Copyright (c) 2018 Davide Corradi
// Licensed under the MIT license.

namespace hou
{

template <typename OutputIt>
OutputIt utf8::encode(code_point input, OutputIt out_first)
{
  static constexpr std::array<code_unit, 4u> start_signature{
    0b00000000,
    0b11000000,
    0b11100000,
    0b11110000,
  };

  // Determine size of the character in code units based on its code point.
  // a maximum of 4 code units is needed.
  size_t unit_count
    = input < 0x80 ? 1u : input < 0x800 ? 2u : input < 0x10000 ? 3u : 4u;

  std::array<uchar, 4u> units;
  for(size_t i = unit_count - 1; i > 0; --i)
  {
    // For trailing units, the two leftmost bits must be 10.
    units[i] = static_cast<uchar>((input | 0b10000000) & 0b10111111);
    input >>= 6;
  }
  units[0] = static_cast<uchar>(input | start_signature[unit_count - 1]);

  // Copy into the out_first and return iterator the next element.
  return std::copy(units.begin(), units.begin() + unit_count, out_first);
}



template <typename InputIt>
InputIt utf8::decode(InputIt in_first, InputIt in_last, code_point& out)
{
  static constexpr std::array<code_point, 4u> offsets{
    0x00000000,
    0x00003080,
    0x000E2080,
    0x03C82080,
  };

  size_t trailing_unit_count = count_trailing_units(*in_first);

  HOU_EXPECT(in_first + trailing_unit_count < in_last);

  out = 0;
  for(size_t i = 0; i < trailing_unit_count; ++i)
  {
    // The ugly cast is done because char could be signed or unsigned, nut
    // we want to treat it as an unsigned type in all cases.
    out
      += static_cast<code_point>(*reinterpret_cast<const uchar*>(&*in_first++));
    out <<= 6;
  }
  out += static_cast<code_point>(*reinterpret_cast<const uchar*>(&*in_first++));

  // Remove offsets due to the 10... signatures in the trailing bytes.
  out -= offsets[trailing_unit_count];

  return in_first;
}



template <typename InputIt>
InputIt utf8::next(InputIt in_first, InputIt in_last)
{
  InputIt next = in_first + count_trailing_units(*in_first) + 1;
  HOU_EXPECT(next <= in_last);
  return next;
}



template <typename InputIt>
size_t utf8::count(InputIt in_first, InputIt in_last)
{
  HOU_EXPECT(in_first <= in_last);
  size_t count = 0;
  while(in_first < in_last)
  {
    in_first = next(in_first, in_last);
    ++count;
  }
  return count;
}



size_t utf8::count_trailing_units(code_unit cu)
{
  static constexpr std::array<code_unit, 16u> trailing_units{
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    1,
    1,
    2,
    3,
  };
  return trailing_units[(*reinterpret_cast<uchar*>(&cu)) >> 4];
}



template <typename OutputIt>
OutputIt utf16::encode(code_point in, OutputIt out_first)
{
  if(in <= 0xFFFF)
  {
    // one code unit. Direct conversion.
    *out_first++ = static_cast<code_unit>(in);
  }
  else
  {
    // Two code units. Need to take care of masking signature bits.
    in -= 0x00010000;
    *out_first++ = static_cast<code_unit>(in >> 10) + 0xD800;
    *out_first++ = static_cast<code_unit>(in & 0b0000001111111111) + 0xDC00;
  }

  return out_first;
}



template <typename InputIt>
InputIt utf16::decode(InputIt in_first, InputIt in_last, code_point& out)
{
  code_unit e1 = *in_first++;

  if(e1 < 0xD800 || e1 > 0xDBFF)
  {
    // one code unit.
    HOU_EXPECT(in_first <= in_last);
    out = e1;
  }
  else
  {
    // Two code units
    HOU_EXPECT(in_first < in_last);
    code_unit e2 = *in_first++;
    HOU_EXPECT(((e2 >= 0xDC00) && (e2 <= 0xDFFF)));
    out = static_cast<code_point>(
      ((e1 - 0xD800) << 10) + (e2 - 0xDC00) + 0x0010000);
  }

  return in_first;
}



template <typename InputIt>
InputIt utf16::next(InputIt in_first, InputIt in_last)
{
  InputIt next
    = in_first + ((*in_first < 0xD800 || *in_first > 0xDBFF) ? 1 : 2);
  HOU_EXPECT(next <= in_last);
  return next;
}



template <typename InputIt>
size_t utf16::count(InputIt in_first, InputIt in_last)
{
  HOU_EXPECT(in_first <= in_last);
  size_t length = 0;
  while(in_first < in_last)
  {
    in_first = next(in_first, in_last);
    ++length;
  }
  return length;
}



template <typename OutputIt>
OutputIt utf32::encode(code_point in, OutputIt out_first)
{
  *out_first = in;
  return ++out_first;
}



template <typename InputIt>
InputIt utf32::decode(InputIt in_first, InputIt in_last, code_point& out)
{
  HOU_EXPECT(in_first < in_last);
  out = *in_first;
  return ++in_first;
}



template <typename InputIt>
InputIt utf32::next(InputIt in_first, InputIt in_last)
{
  HOU_EXPECT(in_first < in_last);
  return ++in_first;
}



template <typename InputIt>
size_t utf32::count(InputIt in_first, InputIt in_last)
{
  HOU_EXPECT(in_first <= in_last);
  return in_last - in_first;
}



template <typename OutputIt>
OutputIt wide::encode(code_point in, OutputIt out_first)
{
#if defined(HOU_SYSTEM_WINDOWS)
  return utf16::encode(in, out_first);
#else
  return utf32::encode(in, out_first);
#endif
}



template <typename InputIt>
InputIt wide::decode(InputIt in_first, InputIt in_last, code_point& out)
{
#if defined(HOU_SYSTEM_WINDOWS)
  return utf16::decode(in_first, in_last, out);
#else
  return utf32::decode(in_first, in_last, out);
#endif
}



template <typename InputIt>
InputIt wide::next(InputIt in_first, InputIt in_last)
{
#if defined(HOU_SYSTEM_WINDOWS)
  return utf16::next(in_first, in_last);
#else
  return utf32::next(in_first, in_last);
#endif
}



template <typename InputIt>
size_t wide::count(InputIt in_first, InputIt in_last)
{
#if defined(HOU_SYSTEM_WINDOWS)
  return utf16::count(in_first, in_last);
#else
  return utf32::count(in_first, in_last);
#endif
}



template <typename InputEncoding, typename OutputEncoding, typename InputIt,
  typename OutputIt>
OutputIt convert_encoding(InputIt in_first, InputIt in_last, OutputIt out_first)
{
  while(in_first < in_last)
  {
    code_point codepoint;
    in_first = InputEncoding::decode(in_first, in_last, codepoint);
    out_first = OutputEncoding::encode(codepoint, out_first);
  }
  return out_first;
}



template <typename InputEncoding, typename OutputEncoding>
std::basic_string<typename OutputEncoding::code_unit> convert_encoding(
  const std::basic_string<typename InputEncoding::code_unit>& s)
{
  std::basic_string<typename OutputEncoding::code_unit> retval;
  convert_encoding<InputEncoding, OutputEncoding>(
    s.begin(), s.end(), std::back_inserter(retval));
  return retval;
}

}  // namespace hou
