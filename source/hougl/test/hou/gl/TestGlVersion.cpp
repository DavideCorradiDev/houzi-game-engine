// Houzi Game Engine
// Copyright (c) 2018 Davide Corradi
// Licensed under the MIT license.

#include "hou/Test.hpp"
#include "hou/gl/TestGlSingleContext.hpp"
#include "hou/gl/gl_version.hpp"

using namespace hou;



namespace
{

class TestGlVersion
  : public TestGlSingleContext {};

}



TEST_F(TestGlVersion, Creation)
{
  gl::version glv(4u, 5u);

  EXPECT_EQ(4u, glv.get_major());
  EXPECT_EQ(5u, glv.get_minor());
}



TEST_F(TestGlVersion, Comparison)
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



TEST_F(TestGlVersion, OutputStreamOperator)
{
  gl::version glv(4u, 5u);
  HOU_EXPECT_OUTPUT("4.5", glv);
}



TEST_F(TestGlVersion, IsSupported)
{
  gl::version v1(4u, 5u);
  gl::version v2(4u, 4u);

  EXPECT_TRUE(v1.is_supported());
  EXPECT_FALSE(v2.is_supported());
}



TEST_F(TestGlVersion, default)
{
  EXPECT_EQ(gl::version(4u, 5u), gl::version::default);
}

