// Houzi Game Engine
// Copyright (c) 2018 Davide Corradi
// Licensed under the MIT license. See license.md for more details.

#include "hou/Test.hpp"
#include "hou/gfx/TestGfxBase.hpp"

#include "hou/gfx/Mesh2ShaderProgram.hpp"

#include "hou/mth/Transform2.hpp"

#include "hou/sys/Color.hpp"

using namespace hou;



namespace
{

class TestMesh2ShaderProgram : public TestGfxBase
{};

}  // namespace



TEST_F(TestMesh2ShaderProgram, Creation)
{
  Mesh2ShaderProgram sp;
  SUCCEED();
}



TEST_F(TestMesh2ShaderProgram, MoveConstructor)
{
  Mesh2ShaderProgram spDummy;
  Mesh2ShaderProgram sp(std::move(spDummy));
  SUCCEED();
}



TEST_F(TestMesh2ShaderProgram, SetColor)
{
  Mesh2ShaderProgram sp;
  sp.setColor(Color::Red);
  SUCCEED();
}



TEST_F(TestMesh2ShaderProgram, SetTextureUnit)
{
  Mesh2ShaderProgram sp;
  sp.setTextureUnit(1u);
  SUCCEED();
}



TEST_F(TestMesh2ShaderProgram, SetTransform)
{
  Mesh2ShaderProgram sp;
  sp.setTransform(Trans2f::translation(Vec2f(2.f, 3.f)));
  SUCCEED();
}
