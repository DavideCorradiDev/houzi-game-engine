// Houzi Game Engine
// Copyright (c) 2018 Davide Corradi
// Licensed under the MIT license.

#include "hou/test.hpp"

#include "hou/gl/gl_version.hpp"

using namespace hou;
using namespace testing;



namespace
{

class test_gl_version : public Test
{};

}  // namespace



TEST_F(test_gl_version, constructor)
{
  gl::version glv(4u, 5u);

  EXPECT_EQ(4u, glv.get_major());
  EXPECT_EQ(5u, glv.get_minor());
}



TEST_F(test_gl_version, comparison)
{
  gl::version v(3u, 3u);
  gl::version v44(4u, 4u);
  gl::version v43(4u, 3u);
  gl::version v42(4u, 2u);
  gl::version v34(3u, 4u);
  gl::version v33(3u, 3u);
  gl::version v32(3u, 2u);
  gl::version v24(2u, 4u);
  gl::version v23(2u, 3u);
  gl::version v22(2u, 2u);

  EXPECT_FALSE(v == v22);
  EXPECT_FALSE(v == v23);
  EXPECT_FALSE(v == v24);
  EXPECT_FALSE(v == v32);
  EXPECT_TRUE(v == v33);
  EXPECT_FALSE(v == v34);
  EXPECT_FALSE(v == v42);
  EXPECT_FALSE(v == v43);
  EXPECT_FALSE(v == v44);

  EXPECT_TRUE(v != v22);
  EXPECT_TRUE(v != v23);
  EXPECT_TRUE(v != v24);
  EXPECT_TRUE(v != v32);
  EXPECT_FALSE(v != v33);
  EXPECT_TRUE(v != v34);
  EXPECT_TRUE(v != v42);
  EXPECT_TRUE(v != v43);
  EXPECT_TRUE(v != v44);

  EXPECT_TRUE(v > v22);
  EXPECT_TRUE(v > v23);
  EXPECT_TRUE(v > v24);
  EXPECT_TRUE(v > v32);
  EXPECT_FALSE(v > v33);
  EXPECT_FALSE(v > v34);
  EXPECT_FALSE(v > v42);
  EXPECT_FALSE(v > v43);
  EXPECT_FALSE(v > v44);

  EXPECT_TRUE(v >= v22);
  EXPECT_TRUE(v >= v23);
  EXPECT_TRUE(v >= v24);
  EXPECT_TRUE(v >= v32);
  EXPECT_TRUE(v >= v33);
  EXPECT_FALSE(v >= v34);
  EXPECT_FALSE(v >= v42);
  EXPECT_FALSE(v >= v43);
  EXPECT_FALSE(v >= v44);

  EXPECT_FALSE(v < v22);
  EXPECT_FALSE(v < v23);
  EXPECT_FALSE(v < v24);
  EXPECT_FALSE(v < v32);
  EXPECT_FALSE(v < v33);
  EXPECT_TRUE(v < v34);
  EXPECT_TRUE(v < v42);
  EXPECT_TRUE(v < v43);
  EXPECT_TRUE(v < v44);

  EXPECT_FALSE(v <= v22);
  EXPECT_FALSE(v <= v23);
  EXPECT_FALSE(v <= v24);
  EXPECT_FALSE(v <= v32);
  EXPECT_TRUE(v <= v33);
  EXPECT_TRUE(v <= v34);
  EXPECT_TRUE(v <= v42);
  EXPECT_TRUE(v <= v43);
  EXPECT_TRUE(v <= v44);
}



TEST_F(test_gl_version, output_stream_operator)
{
  gl::version glv(4u, 5u);
  EXPECT_OUTPUT("4.5", glv);
}
