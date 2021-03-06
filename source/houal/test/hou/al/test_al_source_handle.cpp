// Houzi Game Engine
// Copyright (c) 2018 Davide Corradi
// Licensed under the MIT license.

#include "hou/al/test_al_base.hpp"

#include "hou/al/al_missing_context_error.hpp"
#include "hou/al/al_source_handle.hpp"

using namespace hou;



namespace
{

class test_al_source_handle : public test_al_base
{};

using test_al_source_handle_death_test = test_al_source_handle;

}  // namespace



TEST_F(test_al_source_handle, generation)
{
  al::source_handle sh = al::source_handle::generate();
  EXPECT_NE(0u, sh.get_name());
}



TEST_F(test_al_source_handle_death_test, no_context_creation)
{
#ifndef HOU_ENABLE_AL_ERROR_CHECKS
  SKIP("AL error checks are disabled in this build.");
#endif

  al::context::unset_current();
  EXPECT_ERROR_0(al::source_handle::generate(), al::missing_context_error);
}
