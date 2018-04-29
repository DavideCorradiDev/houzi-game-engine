// Houzi Game Engine
// Copyright (c) 2018 Davide Corradi
// Licensed under the MIT license.

#include "hou/Test.hpp"
#include "hou/gfx/test_data.hpp"
#include "hou/gfx/test_gfx_base.hpp"

#include "hou/gfx/font.hpp"
#include "hou/gfx/formatted_text.hpp"

#include "hou/sys/binary_file_in.hpp"

using namespace hou;



namespace
{

static constexpr float testAcc = 1.e-6f;

class TestFormattedText : public test_gfx_base
{
public:
  font loadFont(const std::string& path);
};

font TestFormattedText::loadFont(const std::string& path)
{
  return font(std::make_unique<binary_file_in>(path));
}

const std::string fontPath = getDataDir() + u8"NotoSans-Regular.ttf";



// void print(const image3R& ph_image)
// {
//   std::cout << "image3R imageRef(vec3u(" << ph_image.get_size().x() << "u, "
//             << ph_image.get_size().y() << "u, " << ph_image.get_size().z() << "u), {";
//   for(size_t i = 0; i < ph_image.get_pixels().size(); ++i)
//   {
//     if(i != 0)
//     {
//       std::cout << ",";
//     }
//     std::cout << static_cast<int>(ph_image.get_pixels()[i].get_r()) << "u";
//   }
//   std::cout << "});" << std::endl;
// }
//
//
//
// void print(float f)
// {
//   std::cout << f;
//   double intPart;
//   double decPart = modf(f, &intPart);
//   if(decPart == 0.f)
//   {
//     std::cout << '.';
//   }
//   std::cout << 'f';
// }
//
//
// void print(const std::vector<text_vertex>& vertices)
// {
//   std::cout << "std::vector<text_vertex> verticesRef{";
//   for(size_t i = 0; i < vertices.size(); ++i)
//   {
//     if(i != 0)
//     {
//       std::cout << ",";
//     }
//     const text_vertex& v = vertices[i];
//     const vec2f& vp = v.get_position();
//     const vec3f& vt = v.get_texture_coordinates();
//     std::cout << "text_vertex(vec2f(";
//     print(vp.x());
//     std::cout << ",";
//     print(vp.y());
//     std::cout << "), vec3f(";
//     print(vt.x());
//     std::cout << ", ";
//     print(vt.y());
//     std::cout << ", ";
//     print(vt.z());
//     std::cout << "))";
//   }
//   std::cout << "};" << std::endl;
// }
//
//
//
// void print(const formatted_text& ft)
// {
//   print(ft.get_atlas().get_image<pixel_format::r>());
//   print(ft.get_mesh().getVertices());
// }

}  // namespace



TEST_F(TestFormattedText, Utf8Constructor)
{
  font f = loadFont(fontPath);
  std::string s = u8"A";
  formatted_text ft(s, f);

  image3R imageRef(vec3u(7u, 7u, 1u),
    {0, 0, 107, 201, 0, 0, 0, 0, 0, 200, 167, 47, 0, 0, 0, 55, 166, 64, 150, 0,
      0, 0, 156, 66, 1, 205, 10, 0, 13, 229, 204, 204, 223, 97, 0, 104, 123, 0,
      0, 38, 198, 0, 202, 28, 0, 0, 0, 193, 45});
  text_mesh::vertex_collection verticesRef{
    text_vertex(vec2f(0.f, -7.f), vec3f(0.f, 0.f, 0.f)),
    text_vertex(vec2f(7.f, -7.f), vec3f(1.f, 0.f, 0.f)),
    text_vertex(vec2f(0.f, 0.f), vec3f(0.f, 1.f, 0.f)),
    text_vertex(vec2f(0.f, 0.f), vec3f(0.f, 1.f, 0.f)),
    text_vertex(vec2f(7.f, -7.f), vec3f(1.f, 0.f, 0.f)),
    text_vertex(vec2f(7.f, 0.f), vec3f(1.f, 1.f, 0.f)),
  };
  rectf rectRef(0.f, -7.f, 7.f, 7.f);

  EXPECT_EQ(imageRef, ft.get_atlas().get_image<pixel_format::r>());
  HOU_EXPECT_CLOSE(verticesRef, ft.get_mesh().getVertices(), testAcc);
  HOU_EXPECT_CLOSE(rectRef, ft.get_bounding_box(), testAcc);
}



TEST_F(TestFormattedText, Utf32Constructor)
{
  font f = loadFont(fontPath);
  std::u32string s = U"A";
  formatted_text ft(s, f);

  image3R imageRef(vec3u(7u, 7u, 1u),
    {0, 0, 107, 201, 0, 0, 0, 0, 0, 200, 167, 47, 0, 0, 0, 55, 166, 64, 150, 0,
      0, 0, 156, 66, 1, 205, 10, 0, 13, 229, 204, 204, 223, 97, 0, 104, 123, 0,
      0, 38, 198, 0, 202, 28, 0, 0, 0, 193, 45});
  text_mesh::vertex_collection verticesRef{
    text_vertex(vec2f(0.f, -7.f), vec3f(0.f, 0.f, 0.f)),
    text_vertex(vec2f(7.f, -7.f), vec3f(1.f, 0.f, 0.f)),
    text_vertex(vec2f(0.f, 0.f), vec3f(0.f, 1.f, 0.f)),
    text_vertex(vec2f(0.f, 0.f), vec3f(0.f, 1.f, 0.f)),
    text_vertex(vec2f(7.f, -7.f), vec3f(1.f, 0.f, 0.f)),
    text_vertex(vec2f(7.f, 0.f), vec3f(1.f, 1.f, 0.f)),
  };
  rectf rectRef(0.f, -7.f, 7.f, 7.f);

  EXPECT_EQ(imageRef, ft.get_atlas().get_image<pixel_format::r>());
  HOU_EXPECT_CLOSE(verticesRef, ft.get_mesh().getVertices(), testAcc);
  HOU_EXPECT_CLOSE(rectRef, ft.get_bounding_box(), testAcc);
}



TEST_F(TestFormattedText, MoveConstructor)
{
  font f = loadFont(fontPath);
  std::u32string s = U"A";
  formatted_text ftDummy(s, f);
  formatted_text ft(std::move(ftDummy));

  image3R imageRef(vec3u(7u, 7u, 1u),
    {0, 0, 107, 201, 0, 0, 0, 0, 0, 200, 167, 47, 0, 0, 0, 55, 166, 64, 150, 0,
      0, 0, 156, 66, 1, 205, 10, 0, 13, 229, 204, 204, 223, 97, 0, 104, 123, 0,
      0, 38, 198, 0, 202, 28, 0, 0, 0, 193, 45});
  text_mesh::vertex_collection verticesRef{
    text_vertex(vec2f(0.f, -7.f), vec3f(0.f, 0.f, 0.f)),
    text_vertex(vec2f(7.f, -7.f), vec3f(1.f, 0.f, 0.f)),
    text_vertex(vec2f(0.f, 0.f), vec3f(0.f, 1.f, 0.f)),
    text_vertex(vec2f(0.f, 0.f), vec3f(0.f, 1.f, 0.f)),
    text_vertex(vec2f(7.f, -7.f), vec3f(1.f, 0.f, 0.f)),
    text_vertex(vec2f(7.f, 0.f), vec3f(1.f, 1.f, 0.f))
  };
  rectf rectRef(0.f, -7.f, 7.f, 7.f);

  EXPECT_EQ(imageRef, ft.get_atlas().get_image<pixel_format::r>());
  HOU_EXPECT_CLOSE(verticesRef, ft.get_mesh().getVertices(), testAcc);
  HOU_EXPECT_CLOSE(rectRef, ft.get_bounding_box(), testAcc);
}



TEST_F(TestFormattedText, TwoCharacters)
{
  font f = loadFont(fontPath);
  std::u32string s = U"AB";
  formatted_text ft(s, f);
  image3R imageRef(vec3u(14u, 7u, 1u),
    {0u, 0u, 107u, 201u, 0u, 0u, 0u, 8u, 248u, 196u, 195u, 197u, 49u, 0u, 0u,
      0u, 200u, 167u, 47u, 0u, 0u, 8u, 224u, 0u, 0u, 85u, 167u, 0u, 0u, 55u,
      166u, 64u, 150u, 0u, 0u, 8u, 224u, 0u, 7u, 125u, 126u, 0u, 0u, 156u, 66u,
      1u, 205u, 10u, 0u, 8u, 248u, 192u, 199u, 204u, 42u, 0u, 13u, 229u, 204u,
      204u, 223u, 97u, 0u, 8u, 224u, 0u, 0u, 39u, 217u, 0u, 104u, 123u, 0u, 0u,
      38u, 198u, 0u, 8u, 224u, 0u, 0u, 45u, 221u, 0u, 202u, 28u, 0u, 0u, 0u,
      193u, 45u, 8u, 248u, 196u, 198u, 204u, 68u, 0u});
  std::vector<text_vertex> verticesRef{
    text_vertex(vec2f(0.f, -7.f), vec3f(0.f, 0.f, 0.f)),
    text_vertex(vec2f(7.f, -7.f), vec3f(0.5f, 0.f, 0.f)),
    text_vertex(vec2f(0.f, 0.f), vec3f(0.f, 1.f, 0.f)),
    text_vertex(vec2f(0.f, 0.f), vec3f(0.f, 1.f, 0.f)),
    text_vertex(vec2f(7.f, -7.f), vec3f(0.5f, 0.f, 0.f)),
    text_vertex(vec2f(7.f, 0.f), vec3f(0.5f, 1.f, 0.f)),
    text_vertex(vec2f(6.f, -7.f), vec3f(0.5f, 0.f, 0.f)),
    text_vertex(vec2f(12.f, -7.f), vec3f(0.928571f, 0.f, 0.f)),
    text_vertex(vec2f(6.f, 0.f), vec3f(0.5f, 1.f, 0.f)),
    text_vertex(vec2f(6.f, 0.f), vec3f(0.5f, 1.f, 0.f)),
    text_vertex(vec2f(12.f, -7.f), vec3f(0.928571f, 0.f, 0.f)),
    text_vertex(vec2f(12.f, 0.f), vec3f(0.928571f, 1.f, 0.f))};
  rectf rectRef(0.f, -7.f, 12.f, 7.f);

  EXPECT_EQ(imageRef, ft.get_atlas().get_image<pixel_format::r>());
  HOU_EXPECT_CLOSE(verticesRef, ft.get_mesh().getVertices(), testAcc);
  HOU_EXPECT_CLOSE(rectRef, ft.get_bounding_box(), testAcc);
}



TEST_F(TestFormattedText, StringWithSpace)
{
  font f = loadFont(fontPath);
  std::u32string s = U"I love cakes";
  formatted_text ft(s, f);
  image3R imageRef(vec3u(60u, 7u, 1u),
    {0u, 0u, 0u, 0u, 0u, 0u, 89u, 237u, 169u, 0u, 0u, 0u, 0u, 152u, 180u, 199u,
      87u, 0u, 0u, 129u, 200u, 208u, 70u, 0u, 0u, 130u, 187u, 193u, 88u, 0u,
      40u, 184u, 0u, 0u, 0u, 0u, 40u, 188u, 0u, 0u, 0u, 0u, 0u, 130u, 193u,
      194u, 137u, 0u, 40u, 188u, 183u, 195u, 18u, 0u, 202u, 34u, 0u, 20u, 215u,
      1u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 196u, 36u, 0u, 0u, 0u, 0u, 4u, 0u, 30u,
      195u, 0u, 63u, 181u, 1u, 0u, 0u, 0u, 61u, 169u, 0u, 6u, 220u, 5u, 40u,
      184u, 0u, 0u, 0u, 0u, 40u, 188u, 0u, 0u, 0u, 0u, 64u, 177u, 0u, 0u, 168u,
      77u, 102u, 147u, 4u, 1u, 0u, 0u, 100u, 132u, 0u, 113u, 120u, 0u, 0u, 0u,
      0u, 0u, 0u, 0u, 0u, 196u, 36u, 0u, 0u, 0u, 26u, 168u, 160u, 162u, 204u,
      0u, 106u, 123u, 0u, 0u, 0u, 0u, 106u, 216u, 180u, 180u, 180u, 21u, 40u,
      184u, 0u, 113u, 144u, 1u, 40u, 188u, 0u, 0u, 0u, 0u, 108u, 123u, 0u, 0u,
      112u, 121u, 3u, 113u, 193u, 130u, 4u, 0u, 11u, 213u, 3u, 206u, 22u, 0u,
      0u, 0u, 0u, 0u, 0u, 0u, 0u, 196u, 36u, 0u, 0u, 0u, 125u, 120u, 0u, 54u,
      204u, 0u, 67u, 177u, 0u, 0u, 1u, 0u, 62u, 181u, 2u, 0u, 4u, 0u, 40u, 182u,
      120u, 133u, 0u, 0u, 40u, 188u, 0u, 0u, 0u, 0u, 66u, 180u, 1u, 0u, 171u,
      78u, 6u, 0u, 1u, 169u, 70u, 0u, 0u, 148u, 121u, 168u, 0u, 0u, 0u, 0u, 0u,
      0u, 0u, 0u, 0u, 196u, 36u, 0u, 0u, 0u, 51u, 208u, 177u, 142u, 191u, 0u,
      0u, 136u, 198u, 195u, 73u, 0u, 0u, 123u, 199u, 191u, 168u, 0u, 40u, 237u,
      223u, 73u, 0u, 0u, 40u, 188u, 0u, 0u, 0u, 0u, 0u, 117u, 199u, 194u, 139u,
      0u, 92u, 191u, 179u, 176u, 15u, 0u, 0u, 44u, 248u, 64u, 0u, 0u, 0u, 0u,
      0u, 0u, 0u, 0u, 0u, 196u, 36u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u,
      0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 40u, 188u, 24u, 212u, 34u, 0u,
      40u, 188u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u,
      0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 88u, 236u, 167u, 0u, 0u,
      0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u,
      0u, 40u, 184u, 0u, 58u, 203u, 10u, 40u, 188u, 0u, 0u, 0u, 0u, 0u, 0u, 0u,
      0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u});
  std::vector<text_vertex> verticesRef{
    text_vertex(vec2f(0.f, -7.f), vec3f(0.1f, 0.f, 0.f)),
    text_vertex(vec2f(3.f, -7.f), vec3f(0.15f, 0.f, 0.f)),
    text_vertex(vec2f(0.f, 0.f), vec3f(0.1f, 1.f, 0.f)),
    text_vertex(vec2f(0.f, 0.f), vec3f(0.1f, 1.f, 0.f)),
    text_vertex(vec2f(3.f, -7.f), vec3f(0.15f, 0.f, 0.f)),
    text_vertex(vec2f(3.f, 0.f), vec3f(0.15f, 1.f, 0.f)),
    text_vertex(vec2f(3.f, 0.f), vec3f(0.f, 0.f, 0.f)),
    text_vertex(vec2f(3.f, 0.f), vec3f(0.f, 0.f, 0.f)),
    text_vertex(vec2f(3.f, 0.f), vec3f(0.f, 0.f, 0.f)),
    text_vertex(vec2f(3.f, 0.f), vec3f(0.f, 0.f, 0.f)),
    text_vertex(vec2f(3.f, 0.f), vec3f(0.f, 0.f, 0.f)),
    text_vertex(vec2f(3.f, 0.f), vec3f(0.f, 0.f, 0.f)),
    text_vertex(vec2f(6.f, -7.f), vec3f(0.6f, 0.f, 0.f)),
    text_vertex(vec2f(8.f, -7.f), vec3f(0.633333f, 0.f, 0.f)),
    text_vertex(vec2f(6.f, 0.f), vec3f(0.6f, 1.f, 0.f)),
    text_vertex(vec2f(6.f, 0.f), vec3f(0.6f, 1.f, 0.f)),
    text_vertex(vec2f(8.f, -7.f), vec3f(0.633333f, 0.f, 0.f)),
    text_vertex(vec2f(8.f, 0.f), vec3f(0.633333f, 1.f, 0.f)),
    text_vertex(vec2f(9.f, -5.f), vec3f(0.7f, 0.f, 0.f)),
    text_vertex(vec2f(15.f, -5.f), vec3f(0.8f, 0.f, 0.f)),
    text_vertex(vec2f(9.f, 0.f), vec3f(0.7f, 0.714286f, 0.f)),
    text_vertex(vec2f(9.f, 0.f), vec3f(0.7f, 0.714286f, 0.f)),
    text_vertex(vec2f(15.f, -5.f), vec3f(0.8f, 0.f, 0.f)),
    text_vertex(vec2f(15.f, 0.f), vec3f(0.8f, 0.714286f, 0.f)),
    text_vertex(vec2f(15.f, -5.f), vec3f(0.9f, 0.f, 0.f)),
    text_vertex(vec2f(21.f, -5.f), vec3f(1.f, 0.f, 0.f)),
    text_vertex(vec2f(15.f, 0.f), vec3f(0.9f, 0.714286f, 0.f)),
    text_vertex(vec2f(15.f, 0.f), vec3f(0.9f, 0.714286f, 0.f)),
    text_vertex(vec2f(21.f, -5.f), vec3f(1.f, 0.f, 0.f)),
    text_vertex(vec2f(21.f, 0.f), vec3f(1.f, 0.714286f, 0.f)),
    text_vertex(vec2f(20.f, -5.f), vec3f(0.4f, 0.f, 0.f)),
    text_vertex(vec2f(26.f, -5.f), vec3f(0.5f, 0.f, 0.f)),
    text_vertex(vec2f(20.f, 0.f), vec3f(0.4f, 0.714286f, 0.f)),
    text_vertex(vec2f(20.f, 0.f), vec3f(0.4f, 0.714286f, 0.f)),
    text_vertex(vec2f(26.f, -5.f), vec3f(0.5f, 0.f, 0.f)),
    text_vertex(vec2f(26.f, 0.f), vec3f(0.5f, 0.714286f, 0.f)),
    text_vertex(vec2f(26.f, 0.f), vec3f(0.f, 0.f, 0.f)),
    text_vertex(vec2f(26.f, 0.f), vec3f(0.f, 0.f, 0.f)),
    text_vertex(vec2f(26.f, 0.f), vec3f(0.f, 0.f, 0.f)),
    text_vertex(vec2f(26.f, 0.f), vec3f(0.f, 0.f, 0.f)),
    text_vertex(vec2f(26.f, 0.f), vec3f(0.f, 0.f, 0.f)),
    text_vertex(vec2f(26.f, 0.f), vec3f(0.f, 0.f, 0.f)),
    text_vertex(vec2f(29.f, -5.f), vec3f(0.3f, 0.f, 0.f)),
    text_vertex(vec2f(34.f, -5.f), vec3f(0.383333f, 0.f, 0.f)),
    text_vertex(vec2f(29.f, 0.f), vec3f(0.3f, 0.714286f, 0.f)),
    text_vertex(vec2f(29.f, 0.f), vec3f(0.3f, 0.714286f, 0.f)),
    text_vertex(vec2f(34.f, -5.f), vec3f(0.383333f, 0.f, 0.f)),
    text_vertex(vec2f(34.f, 0.f), vec3f(0.383333f, 0.714286f, 0.f)),
    text_vertex(vec2f(34.f, -5.f), vec3f(0.2f, 0.f, 0.f)),
    text_vertex(vec2f(39.f, -5.f), vec3f(0.283333f, 0.f, 0.f)),
    text_vertex(vec2f(34.f, 0.f), vec3f(0.2f, 0.714286f, 0.f)),
    text_vertex(vec2f(34.f, 0.f), vec3f(0.2f, 0.714286f, 0.f)),
    text_vertex(vec2f(39.f, -5.f), vec3f(0.283333f, 0.f, 0.f)),
    text_vertex(vec2f(39.f, 0.f), vec3f(0.283333f, 0.714286f, 0.f)),
    text_vertex(vec2f(40.f, -7.f), vec3f(0.5f, 0.f, 0.f)),
    text_vertex(vec2f(46.f, -7.f), vec3f(0.6f, 0.f, 0.f)),
    text_vertex(vec2f(40.f, 0.f), vec3f(0.5f, 1.f, 0.f)),
    text_vertex(vec2f(40.f, 0.f), vec3f(0.5f, 1.f, 0.f)),
    text_vertex(vec2f(46.f, -7.f), vec3f(0.6f, 0.f, 0.f)),
    text_vertex(vec2f(46.f, 0.f), vec3f(0.6f, 1.f, 0.f)),
    text_vertex(vec2f(45.f, -5.f), vec3f(0.4f, 0.f, 0.f)),
    text_vertex(vec2f(51.f, -5.f), vec3f(0.5f, 0.f, 0.f)),
    text_vertex(vec2f(45.f, 0.f), vec3f(0.4f, 0.714286f, 0.f)),
    text_vertex(vec2f(45.f, 0.f), vec3f(0.4f, 0.714286f, 0.f)),
    text_vertex(vec2f(51.f, -5.f), vec3f(0.5f, 0.f, 0.f)),
    text_vertex(vec2f(51.f, 0.f), vec3f(0.5f, 0.714286f, 0.f)),
    text_vertex(vec2f(51.f, -5.f), vec3f(0.8f, 0.f, 0.f)),
    text_vertex(vec2f(56.f, -5.f), vec3f(0.883333f, 0.f, 0.f)),
    text_vertex(vec2f(51.f, 0.f), vec3f(0.8f, 0.714286f, 0.f)),
    text_vertex(vec2f(51.f, 0.f), vec3f(0.8f, 0.714286f, 0.f)),
    text_vertex(vec2f(56.f, -5.f), vec3f(0.883333f, 0.f, 0.f)),
    text_vertex(vec2f(56.f, 0.f), vec3f(0.883333f, 0.714286f, 0.f))};
  rectf rectRef(0.f, -7.f, 56.f, 7.f);

  EXPECT_EQ(imageRef, ft.get_atlas().get_image<pixel_format::r>());
  HOU_EXPECT_CLOSE(verticesRef, ft.get_mesh().getVertices(), testAcc);
  HOU_EXPECT_CLOSE(rectRef, ft.get_bounding_box(), testAcc);
}



TEST_F(TestFormattedText, StringWithNewLine)
{
  font f = loadFont(fontPath);
  std::u32string s = U"I love\n cheese \ncakes";

  formatted_text ft(s, f);
  image3R imageRef(vec3u(72u, 7u, 1u),
    {16u, 188u, 132u, 132u, 188u, 12u, 0u, 0u, 0u, 0u, 0u, 0u, 89u, 237u, 169u,
      0u, 0u, 0u, 0u, 152u, 180u, 199u, 87u, 0u, 0u, 129u, 200u, 208u, 70u, 0u,
      0u, 130u, 187u, 193u, 88u, 0u, 40u, 188u, 0u, 0u, 0u, 0u, 40u, 184u, 0u,
      0u, 0u, 0u, 40u, 188u, 0u, 0u, 0u, 0u, 0u, 130u, 193u, 194u, 137u, 0u,
      40u, 188u, 183u, 195u, 18u, 0u, 202u, 34u, 0u, 20u, 215u, 1u, 16u, 116u,
      0u, 0u, 116u, 12u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 196u, 36u, 0u, 0u, 0u, 0u,
      4u, 0u, 30u, 195u, 0u, 63u, 181u, 1u, 0u, 0u, 0u, 61u, 169u, 0u, 6u, 220u,
      5u, 40u, 188u, 0u, 0u, 0u, 0u, 40u, 184u, 0u, 0u, 0u, 0u, 40u, 188u, 0u,
      0u, 0u, 0u, 64u, 177u, 0u, 0u, 168u, 77u, 102u, 147u, 4u, 1u, 0u, 0u,
      100u, 132u, 0u, 113u, 120u, 0u, 16u, 116u, 0u, 0u, 116u, 12u, 0u, 0u, 0u,
      0u, 0u, 0u, 0u, 196u, 36u, 0u, 0u, 0u, 26u, 168u, 160u, 162u, 204u, 0u,
      106u, 123u, 0u, 0u, 0u, 0u, 106u, 216u, 180u, 180u, 180u, 21u, 40u, 206u,
      168u, 189u, 188u, 12u, 40u, 184u, 0u, 113u, 144u, 1u, 40u, 188u, 0u, 0u,
      0u, 0u, 108u, 123u, 0u, 0u, 112u, 121u, 3u, 113u, 193u, 130u, 4u, 0u, 11u,
      213u, 3u, 206u, 22u, 0u, 16u, 116u, 0u, 0u, 116u, 12u, 0u, 0u, 0u, 0u, 0u,
      0u, 0u, 196u, 36u, 0u, 0u, 0u, 125u, 120u, 0u, 54u, 204u, 0u, 67u, 177u,
      0u, 0u, 1u, 0u, 62u, 181u, 2u, 0u, 4u, 0u, 40u, 233u, 12u, 0u, 152u, 83u,
      40u, 182u, 120u, 133u, 0u, 0u, 40u, 188u, 0u, 0u, 0u, 0u, 66u, 180u, 1u,
      0u, 171u, 78u, 6u, 0u, 1u, 169u, 70u, 0u, 0u, 148u, 121u, 168u, 0u, 0u,
      16u, 116u, 0u, 0u, 116u, 12u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 196u, 36u, 0u,
      0u, 0u, 51u, 208u, 177u, 142u, 191u, 0u, 0u, 136u, 198u, 195u, 73u, 0u,
      0u, 123u, 199u, 191u, 168u, 0u, 40u, 191u, 0u, 0u, 128u, 96u, 40u, 237u,
      223u, 73u, 0u, 0u, 40u, 188u, 0u, 0u, 0u, 0u, 0u, 117u, 199u, 194u, 139u,
      0u, 92u, 191u, 179u, 176u, 15u, 0u, 0u, 44u, 248u, 64u, 0u, 0u, 16u, 116u,
      0u, 0u, 116u, 12u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 196u, 36u, 0u, 0u, 0u, 0u,
      0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 40u,
      188u, 0u, 0u, 128u, 96u, 40u, 188u, 24u, 212u, 34u, 0u, 40u, 188u, 0u, 0u,
      0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u,
      0u, 0u, 16u, 188u, 132u, 132u, 188u, 12u, 0u, 0u, 0u, 0u, 0u, 0u, 88u,
      236u, 167u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u,
      0u, 0u, 0u, 0u, 0u, 0u, 40u, 188u, 0u, 0u, 128u, 96u, 40u, 184u, 0u, 58u,
      203u, 10u, 40u, 188u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u,
      0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u});
  std::vector<text_vertex> verticesRef{
    text_vertex(vec2f(0.f, -7.f), vec3f(0.166667f, 0.f, 0.f)),
    text_vertex(vec2f(3.f, -7.f), vec3f(0.208333f, 0.f, 0.f)),
    text_vertex(vec2f(0.f, 0.f), vec3f(0.166667f, 1.f, 0.f)),
    text_vertex(vec2f(0.f, 0.f), vec3f(0.166667f, 1.f, 0.f)),
    text_vertex(vec2f(3.f, -7.f), vec3f(0.208333f, 0.f, 0.f)),
    text_vertex(vec2f(3.f, 0.f), vec3f(0.208333f, 1.f, 0.f)),
    text_vertex(vec2f(3.f, 0.f), vec3f(0.0833333f, 0.f, 0.f)),
    text_vertex(vec2f(3.f, 0.f), vec3f(0.0833333f, 0.f, 0.f)),
    text_vertex(vec2f(3.f, 0.f), vec3f(0.0833333f, 0.f, 0.f)),
    text_vertex(vec2f(3.f, 0.f), vec3f(0.0833333f, 0.f, 0.f)),
    text_vertex(vec2f(3.f, 0.f), vec3f(0.0833333f, 0.f, 0.f)),
    text_vertex(vec2f(3.f, 0.f), vec3f(0.0833333f, 0.f, 0.f)),
    text_vertex(vec2f(6.f, -7.f), vec3f(0.666667f, 0.f, 0.f)),
    text_vertex(vec2f(8.f, -7.f), vec3f(0.694444f, 0.f, 0.f)),
    text_vertex(vec2f(6.f, 0.f), vec3f(0.666667f, 1.f, 0.f)),
    text_vertex(vec2f(6.f, 0.f), vec3f(0.666667f, 1.f, 0.f)),
    text_vertex(vec2f(8.f, -7.f), vec3f(0.694444f, 0.f, 0.f)),
    text_vertex(vec2f(8.f, 0.f), vec3f(0.694444f, 1.f, 0.f)),
    text_vertex(vec2f(9.f, -5.f), vec3f(0.75f, 0.f, 0.f)),
    text_vertex(vec2f(15.f, -5.f), vec3f(0.833333f, 0.f, 0.f)),
    text_vertex(vec2f(9.f, 0.f), vec3f(0.75f, 0.714286f, 0.f)),
    text_vertex(vec2f(9.f, 0.f), vec3f(0.75f, 0.714286f, 0.f)),
    text_vertex(vec2f(15.f, -5.f), vec3f(0.833333f, 0.f, 0.f)),
    text_vertex(vec2f(15.f, 0.f), vec3f(0.833333f, 0.714286f, 0.f)),
    text_vertex(vec2f(15.f, -5.f), vec3f(0.916667f, 0.f, 0.f)),
    text_vertex(vec2f(21.f, -5.f), vec3f(1.f, 0.f, 0.f)),
    text_vertex(vec2f(15.f, 0.f), vec3f(0.916667f, 0.714286f, 0.f)),
    text_vertex(vec2f(15.f, 0.f), vec3f(0.916667f, 0.714286f, 0.f)),
    text_vertex(vec2f(21.f, -5.f), vec3f(1.f, 0.f, 0.f)),
    text_vertex(vec2f(21.f, 0.f), vec3f(1.f, 0.714286f, 0.f)),
    text_vertex(vec2f(20.f, -5.f), vec3f(0.416667f, 0.f, 0.f)),
    text_vertex(vec2f(26.f, -5.f), vec3f(0.5f, 0.f, 0.f)),
    text_vertex(vec2f(20.f, 0.f), vec3f(0.416667f, 0.714286f, 0.f)),
    text_vertex(vec2f(20.f, 0.f), vec3f(0.416667f, 0.714286f, 0.f)),
    text_vertex(vec2f(26.f, -5.f), vec3f(0.5f, 0.f, 0.f)),
    text_vertex(vec2f(26.f, 0.f), vec3f(0.5f, 0.714286f, 0.f)),
    text_vertex(vec2f(0.f, 0.f), vec3f(0.f, 0.f, 0.f)),
    text_vertex(vec2f(0.f, 0.f), vec3f(0.f, 0.f, 0.f)),
    text_vertex(vec2f(0.f, 0.f), vec3f(0.f, 0.f, 0.f)),
    text_vertex(vec2f(0.f, 0.f), vec3f(0.f, 0.f, 0.f)),
    text_vertex(vec2f(0.f, 0.f), vec3f(0.f, 0.f, 0.f)),
    text_vertex(vec2f(0.f, 0.f), vec3f(0.f, 0.f, 0.f)),
    text_vertex(vec2f(0.f, 14.f), vec3f(0.0833333f, 0.f, 0.f)),
    text_vertex(vec2f(0.f, 14.f), vec3f(0.0833333f, 0.f, 0.f)),
    text_vertex(vec2f(0.f, 14.f), vec3f(0.0833333f, 0.f, 0.f)),
    text_vertex(vec2f(0.f, 14.f), vec3f(0.0833333f, 0.f, 0.f)),
    text_vertex(vec2f(0.f, 14.f), vec3f(0.0833333f, 0.f, 0.f)),
    text_vertex(vec2f(0.f, 14.f), vec3f(0.0833333f, 0.f, 0.f)),
    text_vertex(vec2f(3.f, 9.f), vec3f(0.333333f, 0.f, 0.f)),
    text_vertex(vec2f(8.f, 9.f), vec3f(0.402778f, 0.f, 0.f)),
    text_vertex(vec2f(3.f, 14.f), vec3f(0.333333f, 0.714286f, 0.f)),
    text_vertex(vec2f(3.f, 14.f), vec3f(0.333333f, 0.714286f, 0.f)),
    text_vertex(vec2f(8.f, 9.f), vec3f(0.402778f, 0.f, 0.f)),
    text_vertex(vec2f(8.f, 14.f), vec3f(0.402778f, 0.714286f, 0.f)),
    text_vertex(vec2f(8.f, 7.f), vec3f(0.5f, 0.f, 0.f)),
    text_vertex(vec2f(14.f, 7.f), vec3f(0.583333f, 0.f, 0.f)),
    text_vertex(vec2f(8.f, 14.f), vec3f(0.5f, 1.f, 0.f)),
    text_vertex(vec2f(8.f, 14.f), vec3f(0.5f, 1.f, 0.f)),
    text_vertex(vec2f(14.f, 7.f), vec3f(0.583333f, 0.f, 0.f)),
    text_vertex(vec2f(14.f, 14.f), vec3f(0.583333f, 1.f, 0.f)),
    text_vertex(vec2f(14.f, 9.f), vec3f(0.416667f, 0.f, 0.f)),
    text_vertex(vec2f(20.f, 9.f), vec3f(0.5f, 0.f, 0.f)),
    text_vertex(vec2f(14.f, 14.f), vec3f(0.416667f, 0.714286f, 0.f)),
    text_vertex(vec2f(14.f, 14.f), vec3f(0.416667f, 0.714286f, 0.f)),
    text_vertex(vec2f(20.f, 9.f), vec3f(0.5f, 0.f, 0.f)),
    text_vertex(vec2f(20.f, 14.f), vec3f(0.5f, 0.714286f, 0.f)),
    text_vertex(vec2f(20.f, 9.f), vec3f(0.416667f, 0.f, 0.f)),
    text_vertex(vec2f(26.f, 9.f), vec3f(0.5f, 0.f, 0.f)),
    text_vertex(vec2f(20.f, 14.f), vec3f(0.416667f, 0.714286f, 0.f)),
    text_vertex(vec2f(20.f, 14.f), vec3f(0.416667f, 0.714286f, 0.f)),
    text_vertex(vec2f(26.f, 9.f), vec3f(0.5f, 0.f, 0.f)),
    text_vertex(vec2f(26.f, 14.f), vec3f(0.5f, 0.714286f, 0.f)),
    text_vertex(vec2f(26.f, 9.f), vec3f(0.833333f, 0.f, 0.f)),
    text_vertex(vec2f(31.f, 9.f), vec3f(0.902778f, 0.f, 0.f)),
    text_vertex(vec2f(26.f, 14.f), vec3f(0.833333f, 0.714286f, 0.f)),
    text_vertex(vec2f(26.f, 14.f), vec3f(0.833333f, 0.714286f, 0.f)),
    text_vertex(vec2f(31.f, 9.f), vec3f(0.902778f, 0.f, 0.f)),
    text_vertex(vec2f(31.f, 14.f), vec3f(0.902778f, 0.714286f, 0.f)),
    text_vertex(vec2f(31.f, 9.f), vec3f(0.416667f, 0.f, 0.f)),
    text_vertex(vec2f(37.f, 9.f), vec3f(0.5f, 0.f, 0.f)),
    text_vertex(vec2f(31.f, 14.f), vec3f(0.416667f, 0.714286f, 0.f)),
    text_vertex(vec2f(31.f, 14.f), vec3f(0.416667f, 0.714286f, 0.f)),
    text_vertex(vec2f(37.f, 9.f), vec3f(0.5f, 0.f, 0.f)),
    text_vertex(vec2f(37.f, 14.f), vec3f(0.5f, 0.714286f, 0.f)),
    text_vertex(vec2f(37.f, 14.f), vec3f(0.0833333f, 0.f, 0.f)),
    text_vertex(vec2f(37.f, 14.f), vec3f(0.0833333f, 0.f, 0.f)),
    text_vertex(vec2f(37.f, 14.f), vec3f(0.0833333f, 0.f, 0.f)),
    text_vertex(vec2f(37.f, 14.f), vec3f(0.0833333f, 0.f, 0.f)),
    text_vertex(vec2f(37.f, 14.f), vec3f(0.0833333f, 0.f, 0.f)),
    text_vertex(vec2f(37.f, 14.f), vec3f(0.0833333f, 0.f, 0.f)),
    text_vertex(vec2f(0.f, 0.f), vec3f(0.f, 0.f, 0.f)),
    text_vertex(vec2f(0.f, 0.f), vec3f(0.f, 0.f, 0.f)),
    text_vertex(vec2f(0.f, 0.f), vec3f(0.f, 0.f, 0.f)),
    text_vertex(vec2f(0.f, 0.f), vec3f(0.f, 0.f, 0.f)),
    text_vertex(vec2f(0.f, 0.f), vec3f(0.f, 0.f, 0.f)),
    text_vertex(vec2f(0.f, 0.f), vec3f(0.f, 0.f, 0.f)),
    text_vertex(vec2f(0.f, 23.f), vec3f(0.333333f, 0.f, 0.f)),
    text_vertex(vec2f(5.f, 23.f), vec3f(0.402778f, 0.f, 0.f)),
    text_vertex(vec2f(0.f, 28.f), vec3f(0.333333f, 0.714286f, 0.f)),
    text_vertex(vec2f(0.f, 28.f), vec3f(0.333333f, 0.714286f, 0.f)),
    text_vertex(vec2f(5.f, 23.f), vec3f(0.402778f, 0.f, 0.f)),
    text_vertex(vec2f(5.f, 28.f), vec3f(0.402778f, 0.714286f, 0.f)),
    text_vertex(vec2f(5.f, 23.f), vec3f(0.25f, 0.f, 0.f)),
    text_vertex(vec2f(10.f, 23.f), vec3f(0.319444f, 0.f, 0.f)),
    text_vertex(vec2f(5.f, 28.f), vec3f(0.25f, 0.714286f, 0.f)),
    text_vertex(vec2f(5.f, 28.f), vec3f(0.25f, 0.714286f, 0.f)),
    text_vertex(vec2f(10.f, 23.f), vec3f(0.319444f, 0.f, 0.f)),
    text_vertex(vec2f(10.f, 28.f), vec3f(0.319444f, 0.714286f, 0.f)),
    text_vertex(vec2f(11.f, 21.f), vec3f(0.583333f, 0.f, 0.f)),
    text_vertex(vec2f(17.f, 21.f), vec3f(0.666667f, 0.f, 0.f)),
    text_vertex(vec2f(11.f, 28.f), vec3f(0.583333f, 1.f, 0.f)),
    text_vertex(vec2f(11.f, 28.f), vec3f(0.583333f, 1.f, 0.f)),
    text_vertex(vec2f(17.f, 21.f), vec3f(0.666667f, 0.f, 0.f)),
    text_vertex(vec2f(17.f, 28.f), vec3f(0.666667f, 1.f, 0.f)),
    text_vertex(vec2f(16.f, 23.f), vec3f(0.416667f, 0.f, 0.f)),
    text_vertex(vec2f(22.f, 23.f), vec3f(0.5f, 0.f, 0.f)),
    text_vertex(vec2f(16.f, 28.f), vec3f(0.416667f, 0.714286f, 0.f)),
    text_vertex(vec2f(16.f, 28.f), vec3f(0.416667f, 0.714286f, 0.f)),
    text_vertex(vec2f(22.f, 23.f), vec3f(0.5f, 0.f, 0.f)),
    text_vertex(vec2f(22.f, 28.f), vec3f(0.5f, 0.714286f, 0.f)),
    text_vertex(vec2f(22.f, 23.f), vec3f(0.833333f, 0.f, 0.f)),
    text_vertex(vec2f(27.f, 23.f), vec3f(0.902778f, 0.f, 0.f)),
    text_vertex(vec2f(22.f, 28.f), vec3f(0.833333f, 0.714286f, 0.f)),
    text_vertex(vec2f(22.f, 28.f), vec3f(0.833333f, 0.714286f, 0.f)),
    text_vertex(vec2f(27.f, 23.f), vec3f(0.902778f, 0.f, 0.f)),
    text_vertex(vec2f(27.f, 28.f), vec3f(0.902778f, 0.714286f, 0.f))};
  rectf rectRef(0.f, -7.f, 37.f, 35.f);

  EXPECT_EQ(imageRef, ft.get_atlas().get_image<pixel_format::r>());
  HOU_EXPECT_CLOSE(verticesRef, ft.get_mesh().getVertices(), testAcc);
  HOU_EXPECT_CLOSE(rectRef, ft.get_bounding_box(), testAcc);
}
