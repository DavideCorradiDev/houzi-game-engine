// Houzi Game Engine
// Copyright (c) 2018 Davide Corradi
// Licensed under the MIT license.

#include "hou/Test.hpp"
#include "hou/gfx/TestGfxBase.hpp"

#include "hou/gfx/VertexAttribFormat.hpp"

using namespace hou;



namespace
{

class TestVertexAttribFormat : public TestGfxBase
{};

}  // namespace



TEST_F(TestVertexAttribFormat, Constructor)
{
  VertexAttribFormat vaf(gl_type::float_decimal, 3u, 12u, false);
  EXPECT_EQ(gl_type::float_decimal, vaf.get_type());
  EXPECT_EQ(3u, vaf.getElementCount());
  EXPECT_EQ(12u, vaf.getByteOffset());
  EXPECT_EQ(false, vaf.mustBeNormalized());
}



TEST_F(TestVertexAttribFormat, Comparison)
{
  VertexAttribFormat vaf1(gl_type::float_decimal, 3u, 12u, false);
  VertexAttribFormat vaf2(gl_type::byte, 3u, 12u, false);
  VertexAttribFormat vaf3(gl_type::float_decimal, 4u, 12u, false);
  VertexAttribFormat vaf4(gl_type::float_decimal, 3u, 10u, false);
  VertexAttribFormat vaf5(gl_type::float_decimal, 3u, 12u, true);
  VertexAttribFormat vaf6(gl_type::float_decimal, 3u, 12u, false);

  EXPECT_TRUE(vaf1 != vaf2);
  EXPECT_TRUE(vaf1 != vaf3);
  EXPECT_TRUE(vaf1 != vaf4);
  EXPECT_TRUE(vaf1 != vaf5);
  EXPECT_TRUE(vaf1 == vaf6);

  EXPECT_FALSE(vaf1 == vaf2);
  EXPECT_FALSE(vaf1 == vaf3);
  EXPECT_FALSE(vaf1 == vaf4);
  EXPECT_FALSE(vaf1 == vaf5);
  EXPECT_FALSE(vaf1 != vaf6);
}



TEST_F(TestVertexAttribFormat, OutputStreamOperator)
{
  VertexAttribFormat vaf(gl_type::float_decimal, 3u, 12u, false);
  const char* outRef = "{Type = float_decimal, ElementCount = 3, byte_offset = 12, "
                       "MustBeNormalized = false}";
  HOU_EXPECT_OUTPUT(outRef, vaf);
}
