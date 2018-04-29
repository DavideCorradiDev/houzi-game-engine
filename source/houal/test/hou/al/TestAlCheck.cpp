// Houzi Game Engine
// Copyright (c) 2018 Davide Corradi
// Licensed under the MIT license.

#include "hou/Test.hpp"
#include "hou/al/TestAlBase.hpp"

#include "hou/al/al_context.hpp"
#include "hou/al/al_check.hpp"
#include "hou/al/al_error.hpp"
#include "hou/al/al_object_handle.hpp"

using namespace hou;



namespace
{

class TestAlCheck : public TestAlBase {};
class TestAlCheckDeathTest : public TestAlCheck {};



class ConcreteDeviceOwnedObjectHandle
  : public al::device_owned_object_handle
{
public:
  ConcreteDeviceOwnedObjectHandle(ALuint name)
    : al::device_owned_object_handle(name)
  {}
};



class ConcreteContextOwnedObjectHandle
  : public al::context_owned_object_handle
{
public:
  ConcreteContextOwnedObjectHandle(ALuint name)
    : al::context_owned_object_handle(name)
  {}
};

}



TEST_F(TestAlCheck, AlCheckErrorFunction)
{
  alGetString(AL_VERSION);
  al::check_error("", 0);
  SUCCEED();
}




TEST_F(TestAlCheckDeathTest, AlCheckErrorFunction)
{
  alGetString(AL_INVERSE_DISTANCE);
  HOU_EXPECT_ERROR(al::check_error("", 0), std::logic_error
    , get_text(al_error::invalid_enum));
}



TEST_F(TestAlCheck, AlCheckErrorMacro)
{
  alGetString(AL_VERSION);
  HOU_AL_CHECK_ERROR();
  SUCCEED();
}



TEST_F(TestAlCheckDeathTest, AlCheckErrorMacro)
{
  alGetString(AL_INVERSE_DISTANCE);
#ifdef HOU_ENABLE_AL_ERROR_CHECKS
  HOU_EXPECT_ERROR(HOU_AL_CHECK_ERROR(), std::logic_error
    , get_text(al_error::invalid_enum));
#else
  HOU_AL_CHECK_ERROR();
  SUCCEED();
#endif
}



TEST_F(TestAlCheck, AlCheckContextErrorFunction)
{
  alcGetString(m_device.get_handle(), ALC_DEVICE_SPECIFIER);
  al::check_context_error(m_device, "", 0);
  SUCCEED();
}



TEST_F(TestAlCheckDeathTest, AlCheckContextErrorFunction)
{
  alcGetString(m_device.get_handle(), ALC_MAJOR_VERSION);
  HOU_EXPECT_ERROR(al::check_context_error(m_device, "", 0), std::logic_error
    , get_text(al_error::invalid_enum));
}



TEST_F(TestAlCheck, AlCheckContextErrorMacro)
{
  alcGetString(m_device.get_handle(), ALC_DEVICE_SPECIFIER);
  HOU_AL_CHECK_CONTEXT_ERROR(m_device);
  SUCCEED();
}



TEST_F(TestAlCheckDeathTest, AlCheckContextErrorMacro)
{
  alcGetString(m_device.get_handle(), ALC_MAJOR_VERSION);
#ifdef HOU_ENABLE_AL_CONTEXT_ERROR_CHECKS
  HOU_EXPECT_ERROR(HOU_AL_CHECK_CONTEXT_ERROR(m_device), std::logic_error
    , get_text(al_error::invalid_enum));
#else
  HOU_AL_CHECK_CONTEXT_ERROR(m_device);
  SUCCEED();
#endif
}



TEST_F(TestAlCheck, AlCheckContextExistenceFunction)
{
  al::check_context_existence("", 0);
  SUCCEED();
}



TEST_F(TestAlCheckDeathTest, AlCheckContextExistenceFunction)
{
  al::context::unset_current();
  HOU_EXPECT_ERROR(al::check_context_existence("", 0), std::logic_error
    , get_text(al_error::context_existence));
}



TEST_F(TestAlCheck, AlCheckContextExistenceMacro)
{
  HOU_AL_CHECK_CONTEXT_EXISTENCE();
  SUCCEED();
}



TEST_F(TestAlCheckDeathTest, AlCheckContextExistenceMacro)
{
  al::context::unset_current();
#ifdef HOU_ENABLE_AL_CONTEXT_EXISTENCE_CHECKS
  HOU_EXPECT_ERROR(HOU_AL_CHECK_CONTEXT_EXISTENCE(), std::logic_error
    , get_text(al_error::context_existence));
#else
  HOU_AL_CHECK_CONTEXT_EXISTENCE();
  SUCCEED();
#endif
}



TEST_F(TestAlCheck, AlCheckContextOwnershipDeviceOwnedObjectFunction)
{
  al::device d1;
  al::device d2;
  al::context c1(d1);
  al::context c2(d2);

  al::context::set_current(c1);
  ConcreteDeviceOwnedObjectHandle o1(1u);
  al::check_context_ownership(o1, "", 0);

  al::context::set_current(c2);
  ConcreteDeviceOwnedObjectHandle o2(1u);
  al::check_context_ownership(o2, "", 0);

  SUCCEED();
}



TEST_F(TestAlCheckDeathTest, AlCheckContextOwnershipDeviceOwnedObjectFunction)
{
  al::device d1;
  al::device d2;
  al::context c1(d1);
  al::context c2(d2);

  al::context::set_current(c1);
  ConcreteDeviceOwnedObjectHandle o1(1u);

  al::context::set_current(c2);
  HOU_EXPECT_ERROR(al::check_context_ownership(o1, "", 0), std::logic_error
    , get_text(al_error::invalid_ownership));
}



TEST_F(TestAlCheck, AlCheckContextOwnershipDeviceOwnedObjectMacro)
{
  al::device d1;
  al::device d2;
  al::context c1(d1);
  al::context c2(d2);

  al::context::set_current(c1);
  ConcreteDeviceOwnedObjectHandle o1(1u);
  al::check_context_ownership(o1, "", 0);
  HOU_AL_CHECK_CONTEXT_OWNERSHIP(o1);

  al::context::set_current(c2);
  ConcreteDeviceOwnedObjectHandle o2(1u);
  HOU_AL_CHECK_CONTEXT_OWNERSHIP(o2);

  SUCCEED();
}



TEST_F(TestAlCheckDeathTest, AlCheckContextOwnershipDeviceOwnedObjectMacro)
{
  al::device d1;
  al::device d2;
  al::context c1(d1);
  al::context c2(d2);

  al::context::set_current(c1);
  ConcreteDeviceOwnedObjectHandle o1(1u);

  al::context::set_current(c2);

#ifdef HOU_ENABLE_AL_CONTEXT_OWNERSHIP_CHECKS
  HOU_EXPECT_ERROR(HOU_AL_CHECK_CONTEXT_OWNERSHIP(o1), std::logic_error
    , get_text(al_error::invalid_ownership));
#else
  HOU_AL_CHECK_CONTEXT_OWNERSHIP(o1);
  SUCCEED();
#endif
}



TEST_F(TestAlCheck, AlCheckContextOwnershipContextOwnedObjectFunction)
{
  al::device d1;
  al::device d2;
  al::context c1(d1);
  al::context c2(d2);

  al::context::set_current(c1);
  ConcreteContextOwnedObjectHandle o1(1u);
  al::check_context_ownership(o1, "", 0);

  al::context::set_current(c2);
  ConcreteContextOwnedObjectHandle o2(1u);
  al::check_context_ownership(o2, "", 0);

  SUCCEED();
}



TEST_F(TestAlCheckDeathTest, AlCheckContextOwnershipContextOwnedObjectFunction)
{
  al::device d1;
  al::device d2;
  al::context c1(d1);
  al::context c2(d2);

  al::context::set_current(c1);
  ConcreteContextOwnedObjectHandle o1(1u);

  al::context::set_current(c2);
  HOU_EXPECT_ERROR(al::check_context_ownership(o1, "", 0), std::logic_error
    , get_text(al_error::invalid_ownership));
}



TEST_F(TestAlCheck, AlCheckContextOwnershipContextOwnedObjectMacro)
{
  al::device d1;
  al::device d2;
  al::context c1(d1);
  al::context c2(d2);

  al::context::set_current(c1);
  ConcreteContextOwnedObjectHandle o1(1u);
  HOU_AL_CHECK_CONTEXT_OWNERSHIP(o1);

  al::context::set_current(c2);
  ConcreteContextOwnedObjectHandle o2(1u);
  HOU_AL_CHECK_CONTEXT_OWNERSHIP(o2);

  SUCCEED();
}



TEST_F(TestAlCheckDeathTest, AlCheckContextOwnershipContextOwnedObjectMacro)
{
  al::device d1;
  al::device d2;
  al::context c1(d1);
  al::context c2(d2);

  al::context::set_current(c1);
  ConcreteContextOwnedObjectHandle o1(1u);

  al::context::set_current(c2);
#ifdef HOU_ENABLE_AL_CONTEXT_OWNERSHIP_CHECKS
  HOU_EXPECT_ERROR(HOU_AL_CHECK_CONTEXT_OWNERSHIP(o1), std::logic_error
    , get_text(al_error::invalid_ownership));
#else
  HOU_AL_CHECK_CONTEXT_OWNERSHIP(o1);
  SUCCEED();
#endif
}

