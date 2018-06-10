// Houzi Game Engine
// Copyright (c) 2018 Davide Corradi
// Licensed under the MIT license.

#include "hou/test.hpp"

#include "hou/cor/std_iostream.hpp"

using namespace hou;
using namespace testing;



namespace
{

class test_std_iostream : public Test
{};

}  // namespace



TEST_F(test_std_iostream, state_saving)
{
  std::stringstream ss;

  std::stringstream::fmtflags flags_bkp = ss.flags();
  std::streamsize precision_bkp = ss.precision();
  std::streamsize width_bkp = ss.width();
  std::stringstream::char_type fill_bkp = ss.fill();

  {
    ios_formatting_saver<std::stringstream> saver(ss);

    ss.setf(std::ios::hex);
    ss.precision(12);
    ss.width(16);
    ss.fill('x');
  }

  EXPECT_EQ(flags_bkp, ss.flags());
  EXPECT_EQ(precision_bkp, ss.precision());
  EXPECT_EQ(width_bkp, ss.width());
  EXPECT_EQ(fill_bkp, ss.fill());
}



TEST_F(test_std_iostream, state_saving_move_constructor)
{
  std::stringstream ss;

  std::stringstream::fmtflags flags_bkp = ss.flags();

  {
    ios_formatting_saver<std::stringstream> saver_dummy(ss);
    ios_formatting_saver<std::stringstream> saver(std::move(saver_dummy));

    ss.setf(std::ios::hex);
  }

  EXPECT_EQ(flags_bkp, ss.flags());
}
