// Houzi Game Engine
// Copyright (c) 2018 Davide Corradi
// Licensed under the MIT license.

#include "hou/Test.hpp"
#include "hou/al/test_al_base.hpp"

#include "hou/al/al_buffer_handle.hpp"
#include "hou/al/al_error.hpp"

using namespace hou;



namespace
{

class test_al_buffer_handle : public test_al_base
{};

class test_al_buffer_handle_death_test : public test_al_buffer_handle
{};

}  // namespace



TEST_F(test_al_buffer_handle, Generation)
{
  al::buffer_handle bh = al::buffer_handle::generate();
  EXPECT_NE(0u, bh.get_name());
}



#ifdef HOU_ENABLE_AL_CONTEXT_EXISTENCE_CHECKS
TEST_F(test_al_buffer_handle_death_test, no_context_creation)
#else
TEST_F(test_al_buffer_handle_death_test, DISABLED_no_context_creation)
#endif
{
  al::context::unset_current();
  DEPRECATED_HOU_EXPECT_ERROR(al::buffer_handle::generate(), std::logic_error,
    get_text(al_error::context_existence));
}
