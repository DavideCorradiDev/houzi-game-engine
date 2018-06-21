// Houzi Game Engine
// Copyright (c) 2018 Davide Corradi
// Licensed under the MIT license.

#include "hou/al/test_al_base.hpp"

#include "hou/al/al_buffer_handle.hpp"
#include "hou/al/al_missing_context_error.hpp"

using namespace hou;



namespace
{

class test_al_buffer_handle : public test_al_base
{};

using test_al_buffer_handle_death_test = test_al_buffer_handle;

}  // namespace



TEST_F(test_al_buffer_handle, Generation)
{
  al::buffer_handle bh = al::buffer_handle::generate();
  EXPECT_NE(0u, bh.get_name());
}



#ifdef HOU_ENABLE_AL_ERROR_CHECKS
TEST_F(test_al_buffer_handle_death_test, no_context_creation)
#else
TEST_F(test_al_buffer_handle_death_test, DISABLED_no_context_creation)
#endif
{
  al::context::unset_current();
  EXPECT_ERROR_0(al::buffer_handle::generate(), al::missing_context_error);
}
