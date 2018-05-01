// Houzi Game Engine
// Copyright (c) 2018 Davide Corradi
// Licensed under the MIT license.

#include "hou/Test.hpp"
#include "hou/al/test_al_base.hpp"

#include "hou/al/al_check.hpp"
#include "hou/al/al_context.hpp"
#include "hou/al/al_error.hpp"
#include "hou/al/al_object_handle.hpp"

using namespace hou;



namespace
{

class test_al_check : public test_al_base
{};

class test_al_check_death_test : public test_al_check
{};



class concrete_device_owned_object_handle
  : public al::device_owned_object_handle
{
public:
  concrete_device_owned_object_handle(ALuint name)
    : al::device_owned_object_handle(name)
  {}
};



class concrete_context_owned_object_handle
  : public al::context_owned_object_handle
{
public:
  concrete_context_owned_object_handle(ALuint name)
    : al::context_owned_object_handle(name)
  {}
};

}  // namespace



TEST_F(test_al_check, al_check_error_function)
{
  alGetString(AL_VERSION);
  al::check_error("", 0);
  SUCCEED();
}



TEST_F(test_al_check_death_test, al_check_error_function)
{
  alGetString(AL_INVERSE_DISTANCE);
  HOU_EXPECT_ERROR(
    al::check_error("", 0), std::logic_error, get_text(al_error::invalid_enum));
}



TEST_F(test_al_check, al_check_error_macro)
{
  alGetString(AL_VERSION);
  HOU_AL_CHECK_ERROR();
  SUCCEED();
}



TEST_F(test_al_check_death_test, al_check_error_macro)
{
  alGetString(AL_INVERSE_DISTANCE);
#ifdef HOU_ENABLE_AL_ERROR_CHECKS
  HOU_EXPECT_ERROR(
    HOU_AL_CHECK_ERROR(), std::logic_error, get_text(al_error::invalid_enum));
#else
  HOU_AL_CHECK_ERROR();
  SUCCEED();
#endif
}



TEST_F(test_al_check, al_check_context_error_function)
{
  alcGetString(m_device.get_handle(), ALC_DEVICE_SPECIFIER);
  al::check_context_error(m_device, "", 0);
  SUCCEED();
}



TEST_F(test_al_check_death_test, al_check_context_error_function)
{
  alcGetString(m_device.get_handle(), ALC_MAJOR_VERSION);
  HOU_EXPECT_ERROR(al::check_context_error(m_device, "", 0), std::logic_error,
    get_text(al_error::invalid_enum));
}



TEST_F(test_al_check, al_check_context_error_macro)
{
  alcGetString(m_device.get_handle(), ALC_DEVICE_SPECIFIER);
  HOU_AL_CHECK_CONTEXT_ERROR(m_device);
  SUCCEED();
}



TEST_F(test_al_check_death_test, al_check_context_error_macro)
{
  alcGetString(m_device.get_handle(), ALC_MAJOR_VERSION);
#ifdef HOU_ENABLE_AL_CONTEXT_ERROR_CHECKS
  HOU_EXPECT_ERROR(HOU_AL_CHECK_CONTEXT_ERROR(m_device), std::logic_error,
    get_text(al_error::invalid_enum));
#else
  HOU_AL_CHECK_CONTEXT_ERROR(m_device);
  SUCCEED();
#endif
}



TEST_F(test_al_check, al_check_context_existence_function)
{
  al::check_context_existence("", 0);
  SUCCEED();
}



TEST_F(test_al_check_death_test, al_check_context_existence_function)
{
  al::context::unset_current();
  HOU_EXPECT_ERROR(al::check_context_existence("", 0), std::logic_error,
    get_text(al_error::context_existence));
}



TEST_F(test_al_check, al_check_context_existence_macro)
{
  HOU_AL_CHECK_CONTEXT_EXISTENCE();
  SUCCEED();
}



TEST_F(test_al_check_death_test, al_check_context_existence_macro)
{
  al::context::unset_current();
#ifdef HOU_ENABLE_AL_CONTEXT_EXISTENCE_CHECKS
  HOU_EXPECT_ERROR(HOU_AL_CHECK_CONTEXT_EXISTENCE(), std::logic_error,
    get_text(al_error::context_existence));
#else
  HOU_AL_CHECK_CONTEXT_EXISTENCE();
  SUCCEED();
#endif
}



TEST_F(test_al_check, al_check_context_ownership_device_owned_object_function)
{
  al::device d1;
  al::device d2;
  al::context c1(d1);
  al::context c2(d2);

  al::context::set_current(c1);
  concrete_device_owned_object_handle o1(1u);
  al::check_context_ownership(o1, "", 0);

  al::context::set_current(c2);
  concrete_device_owned_object_handle o2(1u);
  al::check_context_ownership(o2, "", 0);

  SUCCEED();
}



TEST_F(test_al_check_death_test,
  al_check_context_ownership_device_owned_object_function)
{
  al::device d1;
  al::device d2;
  al::context c1(d1);
  al::context c2(d2);

  al::context::set_current(c1);
  concrete_device_owned_object_handle o1(1u);

  al::context::set_current(c2);
  HOU_EXPECT_ERROR(al::check_context_ownership(o1, "", 0), std::logic_error,
    get_text(al_error::invalid_ownership));
}



TEST_F(test_al_check, al_check_context_ownership_device_owned_object_macro)
{
  al::device d1;
  al::device d2;
  al::context c1(d1);
  al::context c2(d2);

  al::context::set_current(c1);
  concrete_device_owned_object_handle o1(1u);
  al::check_context_ownership(o1, "", 0);
  HOU_AL_CHECK_CONTEXT_OWNERSHIP(o1);

  al::context::set_current(c2);
  concrete_device_owned_object_handle o2(1u);
  HOU_AL_CHECK_CONTEXT_OWNERSHIP(o2);

  SUCCEED();
}



TEST_F(test_al_check_death_test,
  al_check_context_ownership_device_owned_object_macro)
{
  al::device d1;
  al::device d2;
  al::context c1(d1);
  al::context c2(d2);

  al::context::set_current(c1);
  concrete_device_owned_object_handle o1(1u);

  al::context::set_current(c2);

#ifdef HOU_ENABLE_AL_CONTEXT_OWNERSHIP_CHECKS
  HOU_EXPECT_ERROR(HOU_AL_CHECK_CONTEXT_OWNERSHIP(o1), std::logic_error,
    get_text(al_error::invalid_ownership));
#else
  HOU_AL_CHECK_CONTEXT_OWNERSHIP(o1);
  SUCCEED();
#endif
}



TEST_F(test_al_check, al_check_context_ownership_context_owned_object_function)
{
  al::device d1;
  al::device d2;
  al::context c1(d1);
  al::context c2(d2);

  al::context::set_current(c1);
  concrete_context_owned_object_handle o1(1u);
  al::check_context_ownership(o1, "", 0);

  al::context::set_current(c2);
  concrete_context_owned_object_handle o2(1u);
  al::check_context_ownership(o2, "", 0);

  SUCCEED();
}



TEST_F(test_al_check_death_test,
  al_check_context_ownership_context_owned_object_function)
{
  al::device d1;
  al::device d2;
  al::context c1(d1);
  al::context c2(d2);

  al::context::set_current(c1);
  concrete_context_owned_object_handle o1(1u);

  al::context::set_current(c2);
  HOU_EXPECT_ERROR(al::check_context_ownership(o1, "", 0), std::logic_error,
    get_text(al_error::invalid_ownership));
}



TEST_F(test_al_check, al_check_context_ownership_context_owned_object_macro)
{
  al::device d1;
  al::device d2;
  al::context c1(d1);
  al::context c2(d2);

  al::context::set_current(c1);
  concrete_context_owned_object_handle o1(1u);
  HOU_AL_CHECK_CONTEXT_OWNERSHIP(o1);

  al::context::set_current(c2);
  concrete_context_owned_object_handle o2(1u);
  HOU_AL_CHECK_CONTEXT_OWNERSHIP(o2);

  SUCCEED();
}



TEST_F(test_al_check_death_test,
  al_check_context_ownership_context_owned_object_macro)
{
  al::device d1;
  al::device d2;
  al::context c1(d1);
  al::context c2(d2);

  al::context::set_current(c1);
  concrete_context_owned_object_handle o1(1u);

  al::context::set_current(c2);
#ifdef HOU_ENABLE_AL_CONTEXT_OWNERSHIP_CHECKS
  HOU_EXPECT_ERROR(HOU_AL_CHECK_CONTEXT_OWNERSHIP(o1), std::logic_error,
    get_text(al_error::invalid_ownership));
#else
  HOU_AL_CHECK_CONTEXT_OWNERSHIP(o1);
  SUCCEED();
#endif
}
