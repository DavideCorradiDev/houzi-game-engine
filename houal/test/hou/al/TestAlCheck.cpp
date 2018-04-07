// Houzi Game Engine
// Copyright (c) 2018 Davide Corradi
// Licensed under the MIT license. See license.md for more details.

#include "hou/Test.hpp"
#include "hou/al/TestAlBase.hpp"

#include "hou/al/AlContext.hpp"
#include "hou/al/AlCheck.hpp"
#include "hou/al/AlError.hpp"
#include "hou/al/AlObjectHandle.hpp"

using namespace hou;



namespace
{

class TestAlCheck : public TestAlBase {};
class TestAlCheckDeathTest : public TestAlCheck {};



class ConcreteDeviceOwnedObjectHandle
  : public al::DeviceOwnedObjectHandle
{
public:
  ConcreteDeviceOwnedObjectHandle(ALuint name)
    : al::DeviceOwnedObjectHandle(name)
  {}
};



class ConcreteContextOwnedObjectHandle
  : public al::ContextOwnedObjectHandle
{
public:
  ConcreteContextOwnedObjectHandle(ALuint name)
    : al::ContextOwnedObjectHandle(name)
  {}
};

}



TEST_F(TestAlCheck, AlCheckErrorFunction)
{
  alGetString(AL_VERSION);
  al::checkError("", 0);
  SUCCEED();
}




TEST_F(TestAlCheckDeathTest, AlCheckErrorFunction)
{
  alGetString(AL_INVERSE_DISTANCE);
  HOU_EXPECT_ERROR(al::checkError("", 0), std::logic_error
    , getText(AlError::InvalidEnum));
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
#if defined(HOU_DISABLE_AL_ERROR_CHECKS)
  HOU_AL_CHECK_ERROR();
  SUCCEED();
#else
  HOU_EXPECT_ERROR(HOU_AL_CHECK_ERROR(), std::logic_error
    , getText(AlError::InvalidEnum));
#endif
}



TEST_F(TestAlCheck, AlCheckContextErrorFunction)
{
  alcGetString(mDevice.getHandle(), ALC_DEVICE_SPECIFIER);
  al::checkContextError(mDevice, "", 0);
  SUCCEED();
}



TEST_F(TestAlCheckDeathTest, AlCheckContextErrorFunction)
{
  alcGetString(mDevice.getHandle(), ALC_MAJOR_VERSION);
  HOU_EXPECT_ERROR(al::checkContextError(mDevice, "", 0), std::logic_error
    , getText(AlError::InvalidEnum));
}



TEST_F(TestAlCheck, AlCheckContextErrorMacro)
{
  alcGetString(mDevice.getHandle(), ALC_DEVICE_SPECIFIER);
  HOU_AL_CHECK_CONTEXT_ERROR(mDevice);
  SUCCEED();
}



TEST_F(TestAlCheckDeathTest, AlCheckContextErrorMacro)
{
  alcGetString(mDevice.getHandle(), ALC_MAJOR_VERSION);
#if defined(HOU_DISABLE_AL_CONTEXT_ERROR_CHECKS)
  HOU_AL_CHECK_CONTEXT_ERROR(mDevice);
  SUCCEED();
#else
  HOU_EXPECT_ERROR(HOU_AL_CHECK_CONTEXT_ERROR(mDevice), std::logic_error
    , getText(AlError::InvalidEnum));
#endif
}



TEST_F(TestAlCheck, AlCheckContextExistenceFunction)
{
  al::checkContextExistence("", 0);
  SUCCEED();
}



TEST_F(TestAlCheckDeathTest, AlCheckContextExistenceFunction)
{
  al::Context::unsetCurrent();
  HOU_EXPECT_ERROR(al::checkContextExistence("", 0), std::logic_error
    , getText(AlError::ContextExistence));
}



TEST_F(TestAlCheck, AlCheckContextExistenceMacro)
{
  HOU_AL_CHECK_CONTEXT_EXISTENCE();
  SUCCEED();
}



TEST_F(TestAlCheckDeathTest, AlCheckContextExistenceMacro)
{
  al::Context::unsetCurrent();
#if defined(HOU_DISABLE_AL_CONTEXT_EXISTENCE_CHECKS)
  HOU_AL_CHECK_CONTEXT_EXISTENCE();
  SUCCEED();
#else
  HOU_EXPECT_ERROR(HOU_AL_CHECK_CONTEXT_EXISTENCE(), std::logic_error
    , getText(AlError::ContextExistence));
#endif
}



TEST_F(TestAlCheck, AlCheckContextOwnershipDeviceOwnedObjectFunction)
{
  al::Device d1;
  al::Device d2;
  al::Context c1(d1);
  al::Context c2(d2);

  al::Context::setCurrent(c1);
  ConcreteDeviceOwnedObjectHandle o1(1u);
  al::checkContextOwnership(o1, "", 0);

  al::Context::setCurrent(c2);
  ConcreteDeviceOwnedObjectHandle o2(1u);
  al::checkContextOwnership(o2, "", 0);

  SUCCEED();
}



TEST_F(TestAlCheckDeathTest, AlCheckContextOwnershipDeviceOwnedObjectFunction)
{
  al::Device d1;
  al::Device d2;
  al::Context c1(d1);
  al::Context c2(d2);

  al::Context::setCurrent(c1);
  ConcreteDeviceOwnedObjectHandle o1(1u);

  al::Context::setCurrent(c2);
  HOU_EXPECT_ERROR(al::checkContextOwnership(o1, "", 0), std::logic_error
    , getText(AlError::InvalidOwnership));
}



TEST_F(TestAlCheck, AlCheckContextOwnershipDeviceOwnedObjectMacro)
{
  al::Device d1;
  al::Device d2;
  al::Context c1(d1);
  al::Context c2(d2);

  al::Context::setCurrent(c1);
  ConcreteDeviceOwnedObjectHandle o1(1u);
  al::checkContextOwnership(o1, "", 0);
  HOU_AL_CHECK_CONTEXT_OWNERSHIP(o1);

  al::Context::setCurrent(c2);
  ConcreteDeviceOwnedObjectHandle o2(1u);
  HOU_AL_CHECK_CONTEXT_OWNERSHIP(o2);

  SUCCEED();
}



TEST_F(TestAlCheckDeathTest, AlCheckContextOwnershipDeviceOwnedObjectMacro)
{
  al::Device d1;
  al::Device d2;
  al::Context c1(d1);
  al::Context c2(d2);

  al::Context::setCurrent(c1);
  ConcreteDeviceOwnedObjectHandle o1(1u);

  al::Context::setCurrent(c2);

#if defined(HOU_DISABLE_AL_CONTEXT_OWNERSHIP_CHECKS)
  HOU_AL_CHECK_CONTEXT_OWNERSHIP(o1);
  SUCCEED();
#else
  HOU_EXPECT_ERROR(HOU_AL_CHECK_CONTEXT_OWNERSHIP(o1), std::logic_error
    , getText(AlError::InvalidOwnership));
#endif
}



TEST_F(TestAlCheck, AlCheckContextOwnershipContextOwnedObjectFunction)
{
  al::Device d1;
  al::Device d2;
  al::Context c1(d1);
  al::Context c2(d2);

  al::Context::setCurrent(c1);
  ConcreteContextOwnedObjectHandle o1(1u);
  al::checkContextOwnership(o1, "", 0);

  al::Context::setCurrent(c2);
  ConcreteContextOwnedObjectHandle o2(1u);
  al::checkContextOwnership(o2, "", 0);

  SUCCEED();
}



TEST_F(TestAlCheckDeathTest, AlCheckContextOwnershipContextOwnedObjectFunction)
{
  al::Device d1;
  al::Device d2;
  al::Context c1(d1);
  al::Context c2(d2);

  al::Context::setCurrent(c1);
  ConcreteContextOwnedObjectHandle o1(1u);

  al::Context::setCurrent(c2);
  HOU_EXPECT_ERROR(al::checkContextOwnership(o1, "", 0), std::logic_error
    , getText(AlError::InvalidOwnership));
}



TEST_F(TestAlCheck, AlCheckContextOwnershipContextOwnedObjectMacro)
{
  al::Device d1;
  al::Device d2;
  al::Context c1(d1);
  al::Context c2(d2);

  al::Context::setCurrent(c1);
  ConcreteContextOwnedObjectHandle o1(1u);
  HOU_AL_CHECK_CONTEXT_OWNERSHIP(o1);

  al::Context::setCurrent(c2);
  ConcreteContextOwnedObjectHandle o2(1u);
  HOU_AL_CHECK_CONTEXT_OWNERSHIP(o2);

  SUCCEED();
}



TEST_F(TestAlCheckDeathTest, AlCheckContextOwnershipContextOwnedObjectMacro)
{
  al::Device d1;
  al::Device d2;
  al::Context c1(d1);
  al::Context c2(d2);

  al::Context::setCurrent(c1);
  ConcreteContextOwnedObjectHandle o1(1u);

  al::Context::setCurrent(c2);
#if defined(HOU_DISABLE_AL_CONTEXT_OWNERSHIP_CHECKS)
  HOU_AL_CHECK_CONTEXT_OWNERSHIP(o1);
  SUCCEED();
#else
  HOU_EXPECT_ERROR(HOU_AL_CHECK_CONTEXT_OWNERSHIP(o1), std::logic_error
    , getText(AlError::InvalidOwnership));
#endif
}

