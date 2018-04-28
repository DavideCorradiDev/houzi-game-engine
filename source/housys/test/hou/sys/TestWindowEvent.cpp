// Houzi Game Engine
// Copyright (c) 2018 Davide Corradi
// Licensed under the MIT license.

#include "hou/Test.hpp"

#include "hou/cor/cor_error.hpp"

#include "hou/sys/WindowEvent.hpp"

using namespace hou;
using namespace testing;



namespace
{

class TestWindowEvent : public Test {};
class TestWindowEventDeathTest : public TestWindowEvent {};

}



TEST_F(TestWindowEvent, Empty)
{
  WindowEvent ev = WindowEvent::empty();
  EXPECT_EQ(WindowEventType::Empty, ev.getType());
}



TEST_F(TestWindowEventDeathTest, EmptyWrongData)
{
  WindowEvent ev = WindowEvent::empty();
  HOU_EXPECT_ERROR(ev.getSizeData(), std::logic_error
    , get_text(cor_error::pre_condition));
  HOU_EXPECT_ERROR(ev.getKeyData(), std::logic_error
    , get_text(cor_error::pre_condition));
  HOU_EXPECT_ERROR(ev.getTextData(), std::logic_error
    , get_text(cor_error::pre_condition));
  HOU_EXPECT_ERROR(ev.getMouseMoveData(), std::logic_error
    , get_text(cor_error::pre_condition));
  HOU_EXPECT_ERROR(ev.getMouseButtonData(), std::logic_error
    , get_text(cor_error::pre_condition));
  HOU_EXPECT_ERROR(ev.getMouseWheelData(), std::logic_error
    , get_text(cor_error::pre_condition));
}



TEST_F(TestWindowEvent, Closed)
{
  WindowEvent ev = WindowEvent::closed();
  EXPECT_EQ(WindowEventType::Closed, ev.getType());
}



TEST_F(TestWindowEventDeathTest, ClosedWrongData)
{
  WindowEvent ev = WindowEvent::closed();
  HOU_EXPECT_ERROR(ev.getSizeData(), std::logic_error
    , get_text(cor_error::pre_condition));
  HOU_EXPECT_ERROR(ev.getKeyData(), std::logic_error
    , get_text(cor_error::pre_condition));
  HOU_EXPECT_ERROR(ev.getTextData(), std::logic_error
    , get_text(cor_error::pre_condition));
  HOU_EXPECT_ERROR(ev.getMouseMoveData(), std::logic_error
    , get_text(cor_error::pre_condition));
  HOU_EXPECT_ERROR(ev.getMouseButtonData(), std::logic_error
    , get_text(cor_error::pre_condition));
  HOU_EXPECT_ERROR(ev.getMouseWheelData(), std::logic_error
    , get_text(cor_error::pre_condition));
}



TEST_F(TestWindowEvent, FocusGained)
{
  WindowEvent ev = WindowEvent::focusGained();
  EXPECT_EQ(WindowEventType::FocusGained, ev.getType());
}



TEST_F(TestWindowEventDeathTest, FocusGainedWrongData)
{
  WindowEvent ev = WindowEvent::focusGained();
  HOU_EXPECT_ERROR(ev.getSizeData(), std::logic_error
    , get_text(cor_error::pre_condition));
  HOU_EXPECT_ERROR(ev.getKeyData(), std::logic_error
    , get_text(cor_error::pre_condition));
  HOU_EXPECT_ERROR(ev.getTextData(), std::logic_error
    , get_text(cor_error::pre_condition));
  HOU_EXPECT_ERROR(ev.getMouseMoveData(), std::logic_error
    , get_text(cor_error::pre_condition));
  HOU_EXPECT_ERROR(ev.getMouseButtonData(), std::logic_error
    , get_text(cor_error::pre_condition));
  HOU_EXPECT_ERROR(ev.getMouseWheelData(), std::logic_error
    , get_text(cor_error::pre_condition));
}



TEST_F(TestWindowEvent, FocusLost)
{
  WindowEvent ev = WindowEvent::focusLost();
  EXPECT_EQ(WindowEventType::FocusLost, ev.getType());
}



TEST_F(TestWindowEventDeathTest, FocusLostWrongData)
{
  WindowEvent ev = WindowEvent::focusLost();
  HOU_EXPECT_ERROR(ev.getSizeData(), std::logic_error
    , get_text(cor_error::pre_condition));
  HOU_EXPECT_ERROR(ev.getKeyData(), std::logic_error
    , get_text(cor_error::pre_condition));
  HOU_EXPECT_ERROR(ev.getTextData(), std::logic_error
    , get_text(cor_error::pre_condition));
  HOU_EXPECT_ERROR(ev.getMouseMoveData(), std::logic_error
    , get_text(cor_error::pre_condition));
  HOU_EXPECT_ERROR(ev.getMouseButtonData(), std::logic_error
    , get_text(cor_error::pre_condition));
  HOU_EXPECT_ERROR(ev.getMouseWheelData(), std::logic_error
    , get_text(cor_error::pre_condition));
}



TEST_F(TestWindowEvent, Resized)
{
  WindowEvent ev = WindowEvent::resized(1u, 3u);
  EXPECT_EQ(WindowEventType::Resized, ev.getType());
  EXPECT_EQ(1u, ev.getSizeData().sizeX);
  EXPECT_EQ(3u, ev.getSizeData().sizeY);
}



TEST_F(TestWindowEventDeathTest, ResizedWrongData)
{
  WindowEvent ev = WindowEvent::resized(1, 3);
  HOU_EXPECT_ERROR(ev.getKeyData(), std::logic_error
    , get_text(cor_error::pre_condition));
  HOU_EXPECT_ERROR(ev.getTextData(), std::logic_error
    , get_text(cor_error::pre_condition));
  HOU_EXPECT_ERROR(ev.getMouseMoveData(), std::logic_error
    , get_text(cor_error::pre_condition));
  HOU_EXPECT_ERROR(ev.getMouseButtonData(), std::logic_error
    , get_text(cor_error::pre_condition));
  HOU_EXPECT_ERROR(ev.getMouseWheelData(), std::logic_error
    , get_text(cor_error::pre_condition));
}



TEST_F(TestWindowEvent, KeyPressed)
{
  WindowEvent ev = WindowEvent::keyPressed(KeyCode::A, ScanCode::Q
    , ModifierKeys::Alt | ModifierKeys::Shift);
  EXPECT_EQ(WindowEventType::KeyPressed, ev.getType());
  EXPECT_EQ(KeyCode::A, ev.getKeyData().keyCode);
  EXPECT_EQ(ScanCode::Q, ev.getKeyData().scanCode);
  EXPECT_EQ(ModifierKeys::Alt | ModifierKeys::Shift, ev.getKeyData().modifierKeys);
}



TEST_F(TestWindowEventDeathTest, KeyPressedWrongData)
{
  WindowEvent ev = WindowEvent::keyPressed(KeyCode::A, ScanCode::Q
    , ModifierKeys::Alt | ModifierKeys::Shift);
  HOU_EXPECT_ERROR(ev.getSizeData(), std::logic_error
    , get_text(cor_error::pre_condition));
  HOU_EXPECT_ERROR(ev.getTextData(), std::logic_error
    , get_text(cor_error::pre_condition));
  HOU_EXPECT_ERROR(ev.getMouseMoveData(), std::logic_error
    , get_text(cor_error::pre_condition));
  HOU_EXPECT_ERROR(ev.getMouseButtonData(), std::logic_error
    , get_text(cor_error::pre_condition));
  HOU_EXPECT_ERROR(ev.getMouseWheelData(), std::logic_error
    , get_text(cor_error::pre_condition));
}



TEST_F(TestWindowEvent, KeyReleased)
{
  WindowEvent ev = WindowEvent::keyReleased(KeyCode::A, ScanCode::Q
    , ModifierKeys::Alt | ModifierKeys::Shift);
  EXPECT_EQ(WindowEventType::KeyReleased, ev.getType());
  EXPECT_EQ(KeyCode::A, ev.getKeyData().keyCode);
  EXPECT_EQ(ScanCode::Q, ev.getKeyData().scanCode);
  EXPECT_EQ(ModifierKeys::Alt | ModifierKeys::Shift, ev.getKeyData().modifierKeys);
}



TEST_F(TestWindowEventDeathTest, KeyReleasedWrongData)
{
  WindowEvent ev = WindowEvent::keyReleased(KeyCode::A, ScanCode::Q
    , ModifierKeys::Alt | ModifierKeys::Shift);
  HOU_EXPECT_ERROR(ev.getSizeData(), std::logic_error
    , get_text(cor_error::pre_condition));
  HOU_EXPECT_ERROR(ev.getTextData(), std::logic_error
    , get_text(cor_error::pre_condition));
  HOU_EXPECT_ERROR(ev.getMouseMoveData(), std::logic_error
    , get_text(cor_error::pre_condition));
  HOU_EXPECT_ERROR(ev.getMouseButtonData(), std::logic_error
    , get_text(cor_error::pre_condition));
  HOU_EXPECT_ERROR(ev.getMouseWheelData(), std::logic_error
    , get_text(cor_error::pre_condition));
}



TEST_F(TestWindowEvent, TextEntered)
{
  WindowEvent ev = WindowEvent::textEntered(1234u);
  EXPECT_EQ(WindowEventType::TextEntered, ev.getType());
  EXPECT_EQ(1234u, ev.getTextData().codePoint);
}



TEST_F(TestWindowEventDeathTest, TextEnteredWrongData)
{
  WindowEvent ev = WindowEvent::textEntered(1234u);
  HOU_EXPECT_ERROR(ev.getSizeData(), std::logic_error
    , get_text(cor_error::pre_condition));
  HOU_EXPECT_ERROR(ev.getKeyData(), std::logic_error
    , get_text(cor_error::pre_condition));
  HOU_EXPECT_ERROR(ev.getMouseMoveData(), std::logic_error
    , get_text(cor_error::pre_condition));
  HOU_EXPECT_ERROR(ev.getMouseButtonData(), std::logic_error
    , get_text(cor_error::pre_condition));
  HOU_EXPECT_ERROR(ev.getMouseWheelData(), std::logic_error
    , get_text(cor_error::pre_condition));
}



TEST_F(TestWindowEvent, MouseMoved)
{
  WindowEvent ev = WindowEvent::mouseMoved(1, 3);
  EXPECT_EQ(WindowEventType::MouseMoved, ev.getType());
  EXPECT_EQ(1, ev.getMouseMoveData().posX);
  EXPECT_EQ(3, ev.getMouseMoveData().posY);
}



TEST_F(TestWindowEventDeathTest, MouseMovedWrongData)
{
  WindowEvent ev = WindowEvent::mouseMoved(1, 3);
  HOU_EXPECT_ERROR(ev.getSizeData(), std::logic_error
    , get_text(cor_error::pre_condition));
  HOU_EXPECT_ERROR(ev.getKeyData(), std::logic_error
    , get_text(cor_error::pre_condition));
  HOU_EXPECT_ERROR(ev.getTextData(), std::logic_error
    , get_text(cor_error::pre_condition));
  HOU_EXPECT_ERROR(ev.getMouseButtonData(), std::logic_error
    , get_text(cor_error::pre_condition));
  HOU_EXPECT_ERROR(ev.getMouseWheelData(), std::logic_error
    , get_text(cor_error::pre_condition));
}



TEST_F(TestWindowEvent, MouseEntered)
{
  WindowEvent ev = WindowEvent::mouseEntered();
  EXPECT_EQ(WindowEventType::MouseEntered, ev.getType());
}



TEST_F(TestWindowEventDeathTest, MouseEnteredWrongData)
{
  WindowEvent ev = WindowEvent::mouseEntered();
  HOU_EXPECT_ERROR(ev.getSizeData(), std::logic_error
    , get_text(cor_error::pre_condition));
  HOU_EXPECT_ERROR(ev.getKeyData(), std::logic_error
    , get_text(cor_error::pre_condition));
  HOU_EXPECT_ERROR(ev.getTextData(), std::logic_error
    , get_text(cor_error::pre_condition));
  HOU_EXPECT_ERROR(ev.getMouseMoveData(), std::logic_error
    , get_text(cor_error::pre_condition));
  HOU_EXPECT_ERROR(ev.getMouseButtonData(), std::logic_error
    , get_text(cor_error::pre_condition));
  HOU_EXPECT_ERROR(ev.getMouseWheelData(), std::logic_error
    , get_text(cor_error::pre_condition));
}



TEST_F(TestWindowEvent, MouseLeft)
{
  WindowEvent ev = WindowEvent::mouseLeft();
  EXPECT_EQ(WindowEventType::MouseLeft, ev.getType());
}



TEST_F(TestWindowEventDeathTest, MouseLeftWrongData)
{
  WindowEvent ev = WindowEvent::mouseLeft();
  HOU_EXPECT_ERROR(ev.getSizeData(), std::logic_error
    , get_text(cor_error::pre_condition));
  HOU_EXPECT_ERROR(ev.getKeyData(), std::logic_error
    , get_text(cor_error::pre_condition));
  HOU_EXPECT_ERROR(ev.getTextData(), std::logic_error
    , get_text(cor_error::pre_condition));
  HOU_EXPECT_ERROR(ev.getMouseMoveData(), std::logic_error
    , get_text(cor_error::pre_condition));
  HOU_EXPECT_ERROR(ev.getMouseButtonData(), std::logic_error
    , get_text(cor_error::pre_condition));
  HOU_EXPECT_ERROR(ev.getMouseWheelData(), std::logic_error
    , get_text(cor_error::pre_condition));
}



TEST_F(TestWindowEvent, MouseButtonPressed)
{
  WindowEvent ev = WindowEvent::mouseButtonPressed(MouseButton::LB, 1, 3);
  EXPECT_EQ(WindowEventType::MouseButtonPressed, ev.getType());
  EXPECT_EQ(MouseButton::LB, ev.getMouseButtonData().button);
  EXPECT_EQ(1, ev.getMouseButtonData().posX);
  EXPECT_EQ(3, ev.getMouseButtonData().posY);
}



TEST_F(TestWindowEventDeathTest, MouseButtonPressedWrongData)
{
  WindowEvent ev = WindowEvent::mouseButtonPressed(MouseButton::LB, 1, 3);
  HOU_EXPECT_ERROR(ev.getSizeData(), std::logic_error
    , get_text(cor_error::pre_condition));
  HOU_EXPECT_ERROR(ev.getKeyData(), std::logic_error
    , get_text(cor_error::pre_condition));
  HOU_EXPECT_ERROR(ev.getTextData(), std::logic_error
    , get_text(cor_error::pre_condition));
  HOU_EXPECT_ERROR(ev.getMouseMoveData(), std::logic_error
    , get_text(cor_error::pre_condition));
  HOU_EXPECT_ERROR(ev.getMouseWheelData(), std::logic_error
    , get_text(cor_error::pre_condition));
}



TEST_F(TestWindowEvent, MouseButtonReleased)
{
  WindowEvent ev = WindowEvent::mouseButtonReleased(MouseButton::LB, 1, 3);
  EXPECT_EQ(WindowEventType::MouseButtonReleased, ev.getType());
  EXPECT_EQ(MouseButton::LB, ev.getMouseButtonData().button);
  EXPECT_EQ(1, ev.getMouseButtonData().posX);
  EXPECT_EQ(3, ev.getMouseButtonData().posY);
}



TEST_F(TestWindowEventDeathTest, MouseButtonReleasedWrongData)
{
  WindowEvent ev = WindowEvent::mouseButtonReleased(MouseButton::LB, 1, 3);
  HOU_EXPECT_ERROR(ev.getSizeData(), std::logic_error
    , get_text(cor_error::pre_condition));
  HOU_EXPECT_ERROR(ev.getKeyData(), std::logic_error
    , get_text(cor_error::pre_condition));
  HOU_EXPECT_ERROR(ev.getTextData(), std::logic_error
    , get_text(cor_error::pre_condition));
  HOU_EXPECT_ERROR(ev.getMouseMoveData(), std::logic_error
    , get_text(cor_error::pre_condition));
  HOU_EXPECT_ERROR(ev.getMouseWheelData(), std::logic_error
    , get_text(cor_error::pre_condition));
}



TEST_F(TestWindowEvent, MouseWheelMoved)
{
  WindowEvent ev = WindowEvent::mouseWheelMoved(MouseWheel::Vertical, 5, 1, 3);
  EXPECT_EQ(WindowEventType::MouseWheelMoved, ev.getType());
  EXPECT_EQ(MouseWheel::Vertical, ev.getMouseWheelData().wheel);
  EXPECT_EQ(5, ev.getMouseWheelData().delta);
  EXPECT_EQ(1, ev.getMouseWheelData().posX);
  EXPECT_EQ(3, ev.getMouseWheelData().posY);
}



TEST_F(TestWindowEventDeathTest, MouseWheelMovedWrongData)
{
  WindowEvent ev = WindowEvent::mouseWheelMoved(MouseWheel::Vertical, 5, 1, 3);
  HOU_EXPECT_ERROR(ev.getSizeData(), std::logic_error
    , get_text(cor_error::pre_condition));
  HOU_EXPECT_ERROR(ev.getKeyData(), std::logic_error
    , get_text(cor_error::pre_condition));
  HOU_EXPECT_ERROR(ev.getTextData(), std::logic_error
    , get_text(cor_error::pre_condition));
  HOU_EXPECT_ERROR(ev.getMouseMoveData(), std::logic_error
    , get_text(cor_error::pre_condition));
  HOU_EXPECT_ERROR(ev.getMouseButtonData(), std::logic_error
    , get_text(cor_error::pre_condition));
}


TEST_F(TestWindowEvent, Comparison)
{
  WindowEvent em0 = WindowEvent::empty();
  WindowEvent em1 = WindowEvent::empty();
  WindowEvent cl0 = WindowEvent::closed();
  WindowEvent cl1 = WindowEvent::closed();
  WindowEvent fg0 = WindowEvent::focusGained();
  WindowEvent fg1 = WindowEvent::focusGained();
  WindowEvent fl0 = WindowEvent::focusLost();
  WindowEvent fl1 = WindowEvent::focusLost();
  WindowEvent rs0 = WindowEvent::resized(1, 2);
  WindowEvent rs1 = WindowEvent::resized(1, 2);
  WindowEvent rs2 = WindowEvent::resized(3, 2);
  WindowEvent rs3 = WindowEvent::resized(1, 4);
  WindowEvent kp0 = WindowEvent::keyPressed(KeyCode::A, ScanCode::A
    , ModifierKeys::Alt | ModifierKeys::Ctrl | ModifierKeys::Shift
    | ModifierKeys::System);
  WindowEvent kp1 = WindowEvent::keyPressed(KeyCode::A, ScanCode::A
    , ModifierKeys::Alt | ModifierKeys::Ctrl | ModifierKeys::Shift
    | ModifierKeys::System);
  WindowEvent kp2 = WindowEvent::keyPressed(KeyCode::B, ScanCode::A
    , ModifierKeys::Alt | ModifierKeys::Ctrl | ModifierKeys::Shift
    | ModifierKeys::System);
  WindowEvent kp3 = WindowEvent::keyPressed(KeyCode::A, ScanCode::B
    , ModifierKeys::Alt | ModifierKeys::Ctrl | ModifierKeys::Shift
    | ModifierKeys::System);
  WindowEvent kp4 = WindowEvent::keyPressed(KeyCode::A, ScanCode::A
    , ModifierKeys::Ctrl | ModifierKeys::Shift | ModifierKeys::System);
  WindowEvent kp5 = WindowEvent::keyPressed(KeyCode::A, ScanCode::A
    , ModifierKeys::Alt | ModifierKeys::Shift | ModifierKeys::System);
  WindowEvent kp6 = WindowEvent::keyPressed(KeyCode::A, ScanCode::A
    , ModifierKeys::Alt | ModifierKeys::Ctrl | ModifierKeys::System);
  WindowEvent kp7 = WindowEvent::keyPressed(KeyCode::A, ScanCode::A
    , ModifierKeys::Alt | ModifierKeys::Ctrl | ModifierKeys::Shift);
  WindowEvent kr0 = WindowEvent::keyReleased(KeyCode::A, ScanCode::A
    , ModifierKeys::Alt | ModifierKeys::Ctrl | ModifierKeys::Shift
    | ModifierKeys::System);
  WindowEvent kr1 = WindowEvent::keyReleased(KeyCode::A, ScanCode::A
    , ModifierKeys::Alt | ModifierKeys::Ctrl | ModifierKeys::Shift
    | ModifierKeys::System);
  WindowEvent kr2 = WindowEvent::keyReleased(KeyCode::B, ScanCode::A
    , ModifierKeys::Alt | ModifierKeys::Ctrl | ModifierKeys::Shift
    | ModifierKeys::System);
  WindowEvent kr3 = WindowEvent::keyReleased(KeyCode::A, ScanCode::B
    , ModifierKeys::Alt | ModifierKeys::Ctrl | ModifierKeys::Shift
    | ModifierKeys::System);
  WindowEvent kr4 = WindowEvent::keyReleased(KeyCode::A, ScanCode::A
    , ModifierKeys::Ctrl | ModifierKeys::Shift | ModifierKeys::System);
  WindowEvent kr5 = WindowEvent::keyReleased(KeyCode::A, ScanCode::A
    , ModifierKeys::Alt | ModifierKeys::Shift | ModifierKeys::System);
  WindowEvent kr6 = WindowEvent::keyReleased(KeyCode::A, ScanCode::A
    , ModifierKeys::Alt | ModifierKeys::Ctrl | ModifierKeys::System);
  WindowEvent kr7 = WindowEvent::keyReleased(KeyCode::A, ScanCode::A
    , ModifierKeys::Alt | ModifierKeys::Ctrl | ModifierKeys::Shift);
  WindowEvent te0 = WindowEvent::textEntered(12);
  WindowEvent te1 = WindowEvent::textEntered(12);
  WindowEvent te2 = WindowEvent::textEntered(24);
  WindowEvent mm0 = WindowEvent::mouseMoved(3, 5);
  WindowEvent mm1 = WindowEvent::mouseMoved(3, 5);
  WindowEvent mm2 = WindowEvent::mouseMoved(6, 5);
  WindowEvent mm3 = WindowEvent::mouseMoved(3, 8);
  WindowEvent me0 = WindowEvent::mouseEntered();
  WindowEvent me1 = WindowEvent::mouseEntered();
  WindowEvent ml0 = WindowEvent::mouseLeft();
  WindowEvent ml1 = WindowEvent::mouseLeft();
  WindowEvent mp0 = WindowEvent::mouseButtonPressed(MouseButton::LB, 3, 5);
  WindowEvent mp1 = WindowEvent::mouseButtonPressed(MouseButton::LB, 3, 5);
  WindowEvent mp2 = WindowEvent::mouseButtonPressed(MouseButton::RB, 3, 5);
  WindowEvent mp3 = WindowEvent::mouseButtonPressed(MouseButton::LB, 6, 5);
  WindowEvent mp4 = WindowEvent::mouseButtonPressed(MouseButton::LB, 3, 8);
  WindowEvent mr0 = WindowEvent::mouseButtonReleased(MouseButton::LB, 3, 5);
  WindowEvent mr1 = WindowEvent::mouseButtonReleased(MouseButton::LB, 3, 5);
  WindowEvent mr2 = WindowEvent::mouseButtonReleased(MouseButton::RB, 3, 5);
  WindowEvent mr3 = WindowEvent::mouseButtonReleased(MouseButton::LB, 6, 5);
  WindowEvent mr4 = WindowEvent::mouseButtonReleased(MouseButton::LB, 3, 8);
  WindowEvent mw0 = WindowEvent::mouseWheelMoved(MouseWheel::Vertical, 7, 3, 5);
  WindowEvent mw1 = WindowEvent::mouseWheelMoved(MouseWheel::Vertical, 7, 3, 5);
  WindowEvent mw2 = WindowEvent::mouseWheelMoved(MouseWheel::Vertical, 9, 3, 5);
  WindowEvent mw3 = WindowEvent::mouseWheelMoved(MouseWheel::Vertical, 7, 6, 5);
  WindowEvent mw4 = WindowEvent::mouseWheelMoved(MouseWheel::Vertical, 7, 3, 8);
  WindowEvent mw5 = WindowEvent::mouseWheelMoved(MouseWheel::Horizontal, 7, 3
    , 5);

  EXPECT_TRUE(em0 == em1);
  EXPECT_FALSE(em0 == cl1);
  EXPECT_FALSE(em0 == fg1);
  EXPECT_FALSE(em0 == fl1);
  EXPECT_FALSE(em0 == rs1);
  EXPECT_FALSE(em0 == rs2);
  EXPECT_FALSE(em0 == rs3);
  EXPECT_FALSE(em0 == kp1);
  EXPECT_FALSE(em0 == kp2);
  EXPECT_FALSE(em0 == kp3);
  EXPECT_FALSE(em0 == kp4);
  EXPECT_FALSE(em0 == kp5);
  EXPECT_FALSE(em0 == kp6);
  EXPECT_FALSE(em0 == kp7);
  EXPECT_FALSE(em0 == kr1);
  EXPECT_FALSE(em0 == kr2);
  EXPECT_FALSE(em0 == kr3);
  EXPECT_FALSE(em0 == kr4);
  EXPECT_FALSE(em0 == kr5);
  EXPECT_FALSE(em0 == kr6);
  EXPECT_FALSE(em0 == kr7);
  EXPECT_FALSE(em0 == te1);
  EXPECT_FALSE(em0 == te2);
  EXPECT_FALSE(em0 == mm1);
  EXPECT_FALSE(em0 == mm2);
  EXPECT_FALSE(em0 == mm3);
  EXPECT_FALSE(em0 == me1);
  EXPECT_FALSE(em0 == ml1);
  EXPECT_FALSE(em0 == mp1);
  EXPECT_FALSE(em0 == mp2);
  EXPECT_FALSE(em0 == mp3);
  EXPECT_FALSE(em0 == mp4);
  EXPECT_FALSE(em0 == mr1);
  EXPECT_FALSE(em0 == mr2);
  EXPECT_FALSE(em0 == mr3);
  EXPECT_FALSE(em0 == mr4);
  EXPECT_FALSE(em0 == mw1);
  EXPECT_FALSE(em0 == mw2);
  EXPECT_FALSE(em0 == mw3);
  EXPECT_FALSE(em0 == mw4);
  EXPECT_FALSE(em0 == mw5);

  EXPECT_FALSE(cl0 == em1);
  EXPECT_TRUE(cl0 == cl1);
  EXPECT_FALSE(cl0 == fg1);
  EXPECT_FALSE(cl0 == fl1);
  EXPECT_FALSE(cl0 == rs1);
  EXPECT_FALSE(cl0 == rs2);
  EXPECT_FALSE(cl0 == rs3);
  EXPECT_FALSE(cl0 == kp1);
  EXPECT_FALSE(cl0 == kp2);
  EXPECT_FALSE(cl0 == kp3);
  EXPECT_FALSE(cl0 == kp4);
  EXPECT_FALSE(cl0 == kp5);
  EXPECT_FALSE(cl0 == kp6);
  EXPECT_FALSE(cl0 == kp7);
  EXPECT_FALSE(cl0 == kr1);
  EXPECT_FALSE(cl0 == kr2);
  EXPECT_FALSE(cl0 == kr3);
  EXPECT_FALSE(cl0 == kr4);
  EXPECT_FALSE(cl0 == kr5);
  EXPECT_FALSE(cl0 == kr6);
  EXPECT_FALSE(cl0 == kr7);
  EXPECT_FALSE(cl0 == te1);
  EXPECT_FALSE(cl0 == te2);
  EXPECT_FALSE(cl0 == mm1);
  EXPECT_FALSE(cl0 == mm2);
  EXPECT_FALSE(cl0 == mm3);
  EXPECT_FALSE(cl0 == me1);
  EXPECT_FALSE(cl0 == ml1);
  EXPECT_FALSE(cl0 == mp1);
  EXPECT_FALSE(cl0 == mp2);
  EXPECT_FALSE(cl0 == mp3);
  EXPECT_FALSE(cl0 == mp4);
  EXPECT_FALSE(cl0 == mr1);
  EXPECT_FALSE(cl0 == mr2);
  EXPECT_FALSE(cl0 == mr3);
  EXPECT_FALSE(cl0 == mr4);
  EXPECT_FALSE(cl0 == mw1);
  EXPECT_FALSE(cl0 == mw2);
  EXPECT_FALSE(cl0 == mw3);
  EXPECT_FALSE(cl0 == mw4);
  EXPECT_FALSE(cl0 == mw5);

  EXPECT_FALSE(fg0 == em1);
  EXPECT_FALSE(fg0 == cl1);
  EXPECT_TRUE(fg0 == fg1);
  EXPECT_FALSE(fg0 == fl1);
  EXPECT_FALSE(fg0 == rs1);
  EXPECT_FALSE(fg0 == rs2);
  EXPECT_FALSE(fg0 == rs3);
  EXPECT_FALSE(fg0 == kp1);
  EXPECT_FALSE(fg0 == kp2);
  EXPECT_FALSE(fg0 == kp3);
  EXPECT_FALSE(fg0 == kp4);
  EXPECT_FALSE(fg0 == kp5);
  EXPECT_FALSE(fg0 == kp6);
  EXPECT_FALSE(fg0 == kp7);
  EXPECT_FALSE(fg0 == kr1);
  EXPECT_FALSE(fg0 == kr2);
  EXPECT_FALSE(fg0 == kr3);
  EXPECT_FALSE(fg0 == kr4);
  EXPECT_FALSE(fg0 == kr5);
  EXPECT_FALSE(fg0 == kr6);
  EXPECT_FALSE(fg0 == kr7);
  EXPECT_FALSE(fg0 == te1);
  EXPECT_FALSE(fg0 == te2);
  EXPECT_FALSE(fg0 == mm1);
  EXPECT_FALSE(fg0 == mm2);
  EXPECT_FALSE(fg0 == mm3);
  EXPECT_FALSE(fg0 == me1);
  EXPECT_FALSE(fg0 == ml1);
  EXPECT_FALSE(fg0 == mp1);
  EXPECT_FALSE(fg0 == mp2);
  EXPECT_FALSE(fg0 == mp3);
  EXPECT_FALSE(fg0 == mp4);
  EXPECT_FALSE(fg0 == mr1);
  EXPECT_FALSE(fg0 == mr2);
  EXPECT_FALSE(fg0 == mr3);
  EXPECT_FALSE(fg0 == mr4);
  EXPECT_FALSE(fg0 == mw1);
  EXPECT_FALSE(fg0 == mw2);
  EXPECT_FALSE(fg0 == mw3);
  EXPECT_FALSE(fg0 == mw4);
  EXPECT_FALSE(fg0 == mw5);

  EXPECT_FALSE(fl0 == em1);
  EXPECT_FALSE(fl0 == cl1);
  EXPECT_FALSE(fl0 == fg1);
  EXPECT_TRUE(fl0 == fl1);
  EXPECT_FALSE(fl0 == rs1);
  EXPECT_FALSE(fl0 == rs2);
  EXPECT_FALSE(fl0 == rs3);
  EXPECT_FALSE(fl0 == kp1);
  EXPECT_FALSE(fl0 == kp2);
  EXPECT_FALSE(fl0 == kp3);
  EXPECT_FALSE(fl0 == kp4);
  EXPECT_FALSE(fl0 == kp5);
  EXPECT_FALSE(fl0 == kp6);
  EXPECT_FALSE(fl0 == kp7);
  EXPECT_FALSE(fl0 == kr1);
  EXPECT_FALSE(fl0 == kr2);
  EXPECT_FALSE(fl0 == kr3);
  EXPECT_FALSE(fl0 == kr4);
  EXPECT_FALSE(fl0 == kr5);
  EXPECT_FALSE(fl0 == kr6);
  EXPECT_FALSE(fl0 == kr7);
  EXPECT_FALSE(fl0 == te1);
  EXPECT_FALSE(fl0 == te2);
  EXPECT_FALSE(fl0 == mm1);
  EXPECT_FALSE(fl0 == mm2);
  EXPECT_FALSE(fl0 == mm3);
  EXPECT_FALSE(fl0 == me1);
  EXPECT_FALSE(fl0 == ml1);
  EXPECT_FALSE(fl0 == mp1);
  EXPECT_FALSE(fl0 == mp2);
  EXPECT_FALSE(fl0 == mp3);
  EXPECT_FALSE(fl0 == mp4);
  EXPECT_FALSE(fl0 == mr1);
  EXPECT_FALSE(fl0 == mr2);
  EXPECT_FALSE(fl0 == mr3);
  EXPECT_FALSE(fl0 == mr4);
  EXPECT_FALSE(fl0 == mw1);
  EXPECT_FALSE(fl0 == mw2);
  EXPECT_FALSE(fl0 == mw3);
  EXPECT_FALSE(fl0 == mw4);
  EXPECT_FALSE(fl0 == mw5);

  EXPECT_FALSE(rs0 == em1);
  EXPECT_FALSE(rs0 == cl1);
  EXPECT_FALSE(rs0 == fg1);
  EXPECT_FALSE(rs0 == fl1);
  EXPECT_TRUE(rs0 == rs1);
  EXPECT_FALSE(rs0 == rs2);
  EXPECT_FALSE(rs0 == rs3);
  EXPECT_FALSE(rs0 == kp1);
  EXPECT_FALSE(rs0 == kp2);
  EXPECT_FALSE(rs0 == kp3);
  EXPECT_FALSE(rs0 == kp4);
  EXPECT_FALSE(rs0 == kp5);
  EXPECT_FALSE(rs0 == kp6);
  EXPECT_FALSE(rs0 == kp7);
  EXPECT_FALSE(rs0 == kr1);
  EXPECT_FALSE(rs0 == kr2);
  EXPECT_FALSE(rs0 == kr3);
  EXPECT_FALSE(rs0 == kr4);
  EXPECT_FALSE(rs0 == kr5);
  EXPECT_FALSE(rs0 == kr6);
  EXPECT_FALSE(rs0 == kr7);
  EXPECT_FALSE(rs0 == te1);
  EXPECT_FALSE(rs0 == te2);
  EXPECT_FALSE(rs0 == mm1);
  EXPECT_FALSE(rs0 == mm2);
  EXPECT_FALSE(rs0 == mm3);
  EXPECT_FALSE(rs0 == me1);
  EXPECT_FALSE(rs0 == ml1);
  EXPECT_FALSE(rs0 == mp1);
  EXPECT_FALSE(rs0 == mp2);
  EXPECT_FALSE(rs0 == mp3);
  EXPECT_FALSE(rs0 == mp4);
  EXPECT_FALSE(rs0 == mr1);
  EXPECT_FALSE(rs0 == mr2);
  EXPECT_FALSE(rs0 == mr3);
  EXPECT_FALSE(rs0 == mr4);
  EXPECT_FALSE(rs0 == mw1);
  EXPECT_FALSE(rs0 == mw2);
  EXPECT_FALSE(rs0 == mw3);
  EXPECT_FALSE(rs0 == mw4);
  EXPECT_FALSE(rs0 == mw5);

  EXPECT_FALSE(kp0 == em1);
  EXPECT_FALSE(kp0 == cl1);
  EXPECT_FALSE(kp0 == fg1);
  EXPECT_FALSE(kp0 == fl1);
  EXPECT_FALSE(kp0 == rs1);
  EXPECT_FALSE(kp0 == rs2);
  EXPECT_FALSE(kp0 == rs3);
  EXPECT_TRUE(kp0 == kp1);
  EXPECT_FALSE(kp0 == kp2);
  EXPECT_FALSE(kp0 == kp3);
  EXPECT_FALSE(kp0 == kp4);
  EXPECT_FALSE(kp0 == kp5);
  EXPECT_FALSE(kp0 == kp6);
  EXPECT_FALSE(kp0 == kp7);
  EXPECT_FALSE(kp0 == kr1);
  EXPECT_FALSE(kp0 == kr2);
  EXPECT_FALSE(kp0 == kr3);
  EXPECT_FALSE(kp0 == kr4);
  EXPECT_FALSE(kp0 == kr5);
  EXPECT_FALSE(kp0 == kr6);
  EXPECT_FALSE(kp0 == kr7);
  EXPECT_FALSE(kp0 == te1);
  EXPECT_FALSE(kp0 == te2);
  EXPECT_FALSE(kp0 == mm1);
  EXPECT_FALSE(kp0 == mm2);
  EXPECT_FALSE(kp0 == mm3);
  EXPECT_FALSE(kp0 == me1);
  EXPECT_FALSE(kp0 == ml1);
  EXPECT_FALSE(kp0 == mp1);
  EXPECT_FALSE(kp0 == mp2);
  EXPECT_FALSE(kp0 == mp3);
  EXPECT_FALSE(kp0 == mp4);
  EXPECT_FALSE(kp0 == mr1);
  EXPECT_FALSE(kp0 == mr2);
  EXPECT_FALSE(kp0 == mr3);
  EXPECT_FALSE(kp0 == mr4);
  EXPECT_FALSE(kp0 == mw1);
  EXPECT_FALSE(kp0 == mw2);
  EXPECT_FALSE(kp0 == mw3);
  EXPECT_FALSE(kp0 == mw4);
  EXPECT_FALSE(kp0 == mw5);

  EXPECT_FALSE(kr0 == em1);
  EXPECT_FALSE(kr0 == cl1);
  EXPECT_FALSE(kr0 == fg1);
  EXPECT_FALSE(kr0 == fl1);
  EXPECT_FALSE(kr0 == rs1);
  EXPECT_FALSE(kr0 == rs2);
  EXPECT_FALSE(kr0 == rs3);
  EXPECT_FALSE(kr0 == kp1);
  EXPECT_FALSE(kr0 == kp2);
  EXPECT_FALSE(kr0 == kp3);
  EXPECT_FALSE(kr0 == kp4);
  EXPECT_FALSE(kr0 == kp5);
  EXPECT_FALSE(kr0 == kp6);
  EXPECT_FALSE(kr0 == kp7);
  EXPECT_TRUE(kr0 == kr1);
  EXPECT_FALSE(kr0 == kr2);
  EXPECT_FALSE(kr0 == kr3);
  EXPECT_FALSE(kr0 == kr4);
  EXPECT_FALSE(kr0 == kr5);
  EXPECT_FALSE(kr0 == kr6);
  EXPECT_FALSE(kr0 == kr7);
  EXPECT_FALSE(kr0 == te1);
  EXPECT_FALSE(kr0 == te2);
  EXPECT_FALSE(kr0 == mm1);
  EXPECT_FALSE(kr0 == mm2);
  EXPECT_FALSE(kr0 == mm3);
  EXPECT_FALSE(kr0 == me1);
  EXPECT_FALSE(kr0 == ml1);
  EXPECT_FALSE(kr0 == mp1);
  EXPECT_FALSE(kr0 == mp2);
  EXPECT_FALSE(kr0 == mp3);
  EXPECT_FALSE(kr0 == mp4);
  EXPECT_FALSE(kr0 == mr1);
  EXPECT_FALSE(kr0 == mr2);
  EXPECT_FALSE(kr0 == mr3);
  EXPECT_FALSE(kr0 == mr4);
  EXPECT_FALSE(kr0 == mw1);
  EXPECT_FALSE(kr0 == mw2);
  EXPECT_FALSE(kr0 == mw3);
  EXPECT_FALSE(kr0 == mw4);
  EXPECT_FALSE(kr0 == mw5);

  EXPECT_FALSE(te0 == em1);
  EXPECT_FALSE(te0 == cl1);
  EXPECT_FALSE(te0 == fg1);
  EXPECT_FALSE(te0 == fl1);
  EXPECT_FALSE(te0 == rs1);
  EXPECT_FALSE(te0 == rs2);
  EXPECT_FALSE(te0 == rs3);
  EXPECT_FALSE(te0 == kp1);
  EXPECT_FALSE(te0 == kp2);
  EXPECT_FALSE(te0 == kp3);
  EXPECT_FALSE(te0 == kp4);
  EXPECT_FALSE(te0 == kp5);
  EXPECT_FALSE(te0 == kp6);
  EXPECT_FALSE(te0 == kp7);
  EXPECT_FALSE(te0 == kr1);
  EXPECT_FALSE(te0 == kr2);
  EXPECT_FALSE(te0 == kr3);
  EXPECT_FALSE(te0 == kr4);
  EXPECT_FALSE(te0 == kr5);
  EXPECT_FALSE(te0 == kr6);
  EXPECT_FALSE(te0 == kr7);
  EXPECT_TRUE(te0 == te1);
  EXPECT_FALSE(te0 == te2);
  EXPECT_FALSE(te0 == mm1);
  EXPECT_FALSE(te0 == mm2);
  EXPECT_FALSE(te0 == mm3);
  EXPECT_FALSE(te0 == me1);
  EXPECT_FALSE(te0 == ml1);
  EXPECT_FALSE(te0 == mp1);
  EXPECT_FALSE(te0 == mp2);
  EXPECT_FALSE(te0 == mp3);
  EXPECT_FALSE(te0 == mp4);
  EXPECT_FALSE(te0 == mr1);
  EXPECT_FALSE(te0 == mr2);
  EXPECT_FALSE(te0 == mr3);
  EXPECT_FALSE(te0 == mr4);
  EXPECT_FALSE(te0 == mw1);
  EXPECT_FALSE(te0 == mw2);
  EXPECT_FALSE(te0 == mw3);
  EXPECT_FALSE(te0 == mw4);
  EXPECT_FALSE(te0 == mw5);

  EXPECT_FALSE(mm0 == em1);
  EXPECT_FALSE(mm0 == cl1);
  EXPECT_FALSE(mm0 == fg1);
  EXPECT_FALSE(mm0 == fl1);
  EXPECT_FALSE(mm0 == rs1);
  EXPECT_FALSE(mm0 == rs2);
  EXPECT_FALSE(mm0 == rs3);
  EXPECT_FALSE(mm0 == kp1);
  EXPECT_FALSE(mm0 == kp2);
  EXPECT_FALSE(mm0 == kp3);
  EXPECT_FALSE(mm0 == kp4);
  EXPECT_FALSE(mm0 == kp5);
  EXPECT_FALSE(mm0 == kp6);
  EXPECT_FALSE(mm0 == kp7);
  EXPECT_FALSE(mm0 == kr1);
  EXPECT_FALSE(mm0 == kr2);
  EXPECT_FALSE(mm0 == kr3);
  EXPECT_FALSE(mm0 == kr4);
  EXPECT_FALSE(mm0 == kr5);
  EXPECT_FALSE(mm0 == kr6);
  EXPECT_FALSE(mm0 == kr7);
  EXPECT_FALSE(mm0 == te1);
  EXPECT_FALSE(mm0 == te2);
  EXPECT_TRUE(mm0 == mm1);
  EXPECT_FALSE(mm0 == mm2);
  EXPECT_FALSE(mm0 == mm3);
  EXPECT_FALSE(mm0 == me1);
  EXPECT_FALSE(mm0 == ml1);
  EXPECT_FALSE(mm0 == mp1);
  EXPECT_FALSE(mm0 == mp2);
  EXPECT_FALSE(mm0 == mp3);
  EXPECT_FALSE(mm0 == mp4);
  EXPECT_FALSE(mm0 == mr1);
  EXPECT_FALSE(mm0 == mr2);
  EXPECT_FALSE(mm0 == mr3);
  EXPECT_FALSE(mm0 == mr4);
  EXPECT_FALSE(mm0 == mw1);
  EXPECT_FALSE(mm0 == mw2);
  EXPECT_FALSE(mm0 == mw3);
  EXPECT_FALSE(mm0 == mw4);
  EXPECT_FALSE(mm0 == mw5);

  EXPECT_FALSE(me0 == em1);
  EXPECT_FALSE(me0 == cl1);
  EXPECT_FALSE(me0 == fg1);
  EXPECT_FALSE(me0 == fl1);
  EXPECT_FALSE(me0 == rs1);
  EXPECT_FALSE(me0 == rs2);
  EXPECT_FALSE(me0 == rs3);
  EXPECT_FALSE(me0 == kp1);
  EXPECT_FALSE(me0 == kp2);
  EXPECT_FALSE(me0 == kp3);
  EXPECT_FALSE(me0 == kp4);
  EXPECT_FALSE(me0 == kp5);
  EXPECT_FALSE(me0 == kp6);
  EXPECT_FALSE(me0 == kp7);
  EXPECT_FALSE(me0 == kr1);
  EXPECT_FALSE(me0 == kr2);
  EXPECT_FALSE(me0 == kr3);
  EXPECT_FALSE(me0 == kr4);
  EXPECT_FALSE(me0 == kr5);
  EXPECT_FALSE(me0 == kr6);
  EXPECT_FALSE(me0 == kr7);
  EXPECT_FALSE(me0 == te1);
  EXPECT_FALSE(me0 == te2);
  EXPECT_FALSE(me0 == mm1);
  EXPECT_FALSE(me0 == mm2);
  EXPECT_FALSE(me0 == mm3);
  EXPECT_TRUE(me0 == me1);
  EXPECT_FALSE(me0 == ml1);
  EXPECT_FALSE(me0 == mp1);
  EXPECT_FALSE(me0 == mp2);
  EXPECT_FALSE(me0 == mp3);
  EXPECT_FALSE(me0 == mp4);
  EXPECT_FALSE(me0 == mr1);
  EXPECT_FALSE(me0 == mr2);
  EXPECT_FALSE(me0 == mr3);
  EXPECT_FALSE(me0 == mr4);
  EXPECT_FALSE(me0 == mw1);
  EXPECT_FALSE(me0 == mw2);
  EXPECT_FALSE(me0 == mw3);
  EXPECT_FALSE(me0 == mw4);
  EXPECT_FALSE(me0 == mw5);

  EXPECT_FALSE(ml0 == em1);
  EXPECT_FALSE(ml0 == cl1);
  EXPECT_FALSE(ml0 == fg1);
  EXPECT_FALSE(ml0 == fl1);
  EXPECT_FALSE(ml0 == rs1);
  EXPECT_FALSE(ml0 == rs2);
  EXPECT_FALSE(ml0 == rs3);
  EXPECT_FALSE(ml0 == kp1);
  EXPECT_FALSE(ml0 == kp2);
  EXPECT_FALSE(ml0 == kp3);
  EXPECT_FALSE(ml0 == kp4);
  EXPECT_FALSE(ml0 == kp5);
  EXPECT_FALSE(ml0 == kp6);
  EXPECT_FALSE(ml0 == kp7);
  EXPECT_FALSE(ml0 == kr1);
  EXPECT_FALSE(ml0 == kr2);
  EXPECT_FALSE(ml0 == kr3);
  EXPECT_FALSE(ml0 == kr4);
  EXPECT_FALSE(ml0 == kr5);
  EXPECT_FALSE(ml0 == kr6);
  EXPECT_FALSE(ml0 == kr7);
  EXPECT_FALSE(ml0 == te1);
  EXPECT_FALSE(ml0 == te2);
  EXPECT_FALSE(ml0 == mm1);
  EXPECT_FALSE(ml0 == mm2);
  EXPECT_FALSE(ml0 == mm3);
  EXPECT_FALSE(ml0 == me1);
  EXPECT_TRUE(ml0 == ml1);
  EXPECT_FALSE(ml0 == mp1);
  EXPECT_FALSE(ml0 == mp2);
  EXPECT_FALSE(ml0 == mp3);
  EXPECT_FALSE(ml0 == mp4);
  EXPECT_FALSE(ml0 == mr1);
  EXPECT_FALSE(ml0 == mr2);
  EXPECT_FALSE(ml0 == mr3);
  EXPECT_FALSE(ml0 == mr4);
  EXPECT_FALSE(ml0 == mw1);
  EXPECT_FALSE(ml0 == mw2);
  EXPECT_FALSE(ml0 == mw3);
  EXPECT_FALSE(ml0 == mw4);
  EXPECT_FALSE(ml0 == mw5);

  EXPECT_FALSE(mp0 == em1);
  EXPECT_FALSE(mp0 == cl1);
  EXPECT_FALSE(mp0 == fg1);
  EXPECT_FALSE(mp0 == fl1);
  EXPECT_FALSE(mp0 == rs1);
  EXPECT_FALSE(mp0 == rs2);
  EXPECT_FALSE(mp0 == rs3);
  EXPECT_FALSE(mp0 == kp1);
  EXPECT_FALSE(mp0 == kp2);
  EXPECT_FALSE(mp0 == kp3);
  EXPECT_FALSE(mp0 == kp4);
  EXPECT_FALSE(mp0 == kp5);
  EXPECT_FALSE(mp0 == kp6);
  EXPECT_FALSE(mp0 == kp7);
  EXPECT_FALSE(mp0 == kr1);
  EXPECT_FALSE(mp0 == kr2);
  EXPECT_FALSE(mp0 == kr3);
  EXPECT_FALSE(mp0 == kr4);
  EXPECT_FALSE(mp0 == kr5);
  EXPECT_FALSE(mp0 == kr6);
  EXPECT_FALSE(mp0 == kr7);
  EXPECT_FALSE(mp0 == te1);
  EXPECT_FALSE(mp0 == te2);
  EXPECT_FALSE(mp0 == mm1);
  EXPECT_FALSE(mp0 == mm2);
  EXPECT_FALSE(mp0 == mm3);
  EXPECT_FALSE(mp0 == me1);
  EXPECT_FALSE(mp0 == ml1);
  EXPECT_TRUE(mp0 == mp1);
  EXPECT_FALSE(mp0 == mp2);
  EXPECT_FALSE(mp0 == mp3);
  EXPECT_FALSE(mp0 == mp4);
  EXPECT_FALSE(mp0 == mr1);
  EXPECT_FALSE(mp0 == mr2);
  EXPECT_FALSE(mp0 == mr3);
  EXPECT_FALSE(mp0 == mr4);
  EXPECT_FALSE(mp0 == mw1);
  EXPECT_FALSE(mp0 == mw2);
  EXPECT_FALSE(mp0 == mw3);
  EXPECT_FALSE(mp0 == mw4);
  EXPECT_FALSE(mp0 == mw5);

  EXPECT_FALSE(mr0 == em1);
  EXPECT_FALSE(mr0 == cl1);
  EXPECT_FALSE(mr0 == fg1);
  EXPECT_FALSE(mr0 == fl1);
  EXPECT_FALSE(mr0 == rs1);
  EXPECT_FALSE(mr0 == rs2);
  EXPECT_FALSE(mr0 == rs3);
  EXPECT_FALSE(mr0 == kp1);
  EXPECT_FALSE(mr0 == kp2);
  EXPECT_FALSE(mr0 == kp3);
  EXPECT_FALSE(mr0 == kp4);
  EXPECT_FALSE(mr0 == kp5);
  EXPECT_FALSE(mr0 == kp6);
  EXPECT_FALSE(mr0 == kp7);
  EXPECT_FALSE(mr0 == kr1);
  EXPECT_FALSE(mr0 == kr2);
  EXPECT_FALSE(mr0 == kr3);
  EXPECT_FALSE(mr0 == kr4);
  EXPECT_FALSE(mr0 == kr5);
  EXPECT_FALSE(mr0 == kr6);
  EXPECT_FALSE(mr0 == kr7);
  EXPECT_FALSE(mr0 == te1);
  EXPECT_FALSE(mr0 == te2);
  EXPECT_FALSE(mr0 == mm1);
  EXPECT_FALSE(mr0 == mm2);
  EXPECT_FALSE(mr0 == mm3);
  EXPECT_FALSE(mr0 == me1);
  EXPECT_FALSE(mr0 == ml1);
  EXPECT_FALSE(mr0 == mp1);
  EXPECT_FALSE(mr0 == mp2);
  EXPECT_FALSE(mr0 == mp3);
  EXPECT_FALSE(mr0 == mp4);
  EXPECT_TRUE(mr0 == mr1);
  EXPECT_FALSE(mr0 == mr2);
  EXPECT_FALSE(mr0 == mr3);
  EXPECT_FALSE(mr0 == mr4);
  EXPECT_FALSE(mr0 == mw1);
  EXPECT_FALSE(mr0 == mw2);
  EXPECT_FALSE(mr0 == mw3);
  EXPECT_FALSE(mr0 == mw4);
  EXPECT_FALSE(mr0 == mw5);

  EXPECT_FALSE(mw0 == em1);
  EXPECT_FALSE(mw0 == cl1);
  EXPECT_FALSE(mw0 == fg1);
  EXPECT_FALSE(mw0 == fl1);
  EXPECT_FALSE(mw0 == rs1);
  EXPECT_FALSE(mw0 == rs2);
  EXPECT_FALSE(mw0 == rs3);
  EXPECT_FALSE(mw0 == kp1);
  EXPECT_FALSE(mw0 == kp2);
  EXPECT_FALSE(mw0 == kp3);
  EXPECT_FALSE(mw0 == kp4);
  EXPECT_FALSE(mw0 == kp5);
  EXPECT_FALSE(mw0 == kp6);
  EXPECT_FALSE(mw0 == kp7);
  EXPECT_FALSE(mw0 == kr1);
  EXPECT_FALSE(mw0 == kr2);
  EXPECT_FALSE(mw0 == kr3);
  EXPECT_FALSE(mw0 == kr4);
  EXPECT_FALSE(mw0 == kr5);
  EXPECT_FALSE(mw0 == kr6);
  EXPECT_FALSE(mw0 == kr7);
  EXPECT_FALSE(mw0 == te1);
  EXPECT_FALSE(mw0 == te2);
  EXPECT_FALSE(mw0 == mm1);
  EXPECT_FALSE(mw0 == mm2);
  EXPECT_FALSE(mw0 == mm3);
  EXPECT_FALSE(mw0 == me1);
  EXPECT_FALSE(mw0 == ml1);
  EXPECT_FALSE(mw0 == mp1);
  EXPECT_FALSE(mw0 == mp2);
  EXPECT_FALSE(mw0 == mp3);
  EXPECT_FALSE(mw0 == mp4);
  EXPECT_FALSE(mw0 == mr1);
  EXPECT_FALSE(mw0 == mr2);
  EXPECT_FALSE(mw0 == mr3);
  EXPECT_FALSE(mw0 == mr4);
  EXPECT_TRUE(mw0 == mw1);
  EXPECT_FALSE(mw0 == mw2);
  EXPECT_FALSE(mw0 == mw3);
  EXPECT_FALSE(mw0 == mw4);
  EXPECT_FALSE(mw0 == mw5);

  EXPECT_FALSE(em0 != em1);
  EXPECT_TRUE(em0 != cl1);
  EXPECT_TRUE(em0 != fg1);
  EXPECT_TRUE(em0 != fl1);
  EXPECT_TRUE(em0 != rs1);
  EXPECT_TRUE(em0 != rs2);
  EXPECT_TRUE(em0 != rs3);
  EXPECT_TRUE(em0 != kp1);
  EXPECT_TRUE(em0 != kp2);
  EXPECT_TRUE(em0 != kp3);
  EXPECT_TRUE(em0 != kp4);
  EXPECT_TRUE(em0 != kp5);
  EXPECT_TRUE(em0 != kp6);
  EXPECT_TRUE(em0 != kp7);
  EXPECT_TRUE(em0 != kr1);
  EXPECT_TRUE(em0 != kr2);
  EXPECT_TRUE(em0 != kr3);
  EXPECT_TRUE(em0 != kr4);
  EXPECT_TRUE(em0 != kr5);
  EXPECT_TRUE(em0 != kr6);
  EXPECT_TRUE(em0 != kr7);
  EXPECT_TRUE(em0 != te1);
  EXPECT_TRUE(em0 != te2);
  EXPECT_TRUE(em0 != mm1);
  EXPECT_TRUE(em0 != mm2);
  EXPECT_TRUE(em0 != mm3);
  EXPECT_TRUE(em0 != me1);
  EXPECT_TRUE(em0 != ml1);
  EXPECT_TRUE(em0 != mp1);
  EXPECT_TRUE(em0 != mp2);
  EXPECT_TRUE(em0 != mp3);
  EXPECT_TRUE(em0 != mp4);
  EXPECT_TRUE(em0 != mr1);
  EXPECT_TRUE(em0 != mr2);
  EXPECT_TRUE(em0 != mr3);
  EXPECT_TRUE(em0 != mr4);
  EXPECT_TRUE(em0 != mw1);
  EXPECT_TRUE(em0 != mw2);
  EXPECT_TRUE(em0 != mw3);
  EXPECT_TRUE(em0 != mw4);
  EXPECT_TRUE(em0 != mw5);

  EXPECT_TRUE(cl0 != em1);
  EXPECT_FALSE(cl0 != cl1);
  EXPECT_TRUE(cl0 != fg1);
  EXPECT_TRUE(cl0 != fl1);
  EXPECT_TRUE(cl0 != rs1);
  EXPECT_TRUE(cl0 != rs2);
  EXPECT_TRUE(cl0 != rs3);
  EXPECT_TRUE(cl0 != kp1);
  EXPECT_TRUE(cl0 != kp2);
  EXPECT_TRUE(cl0 != kp3);
  EXPECT_TRUE(cl0 != kp4);
  EXPECT_TRUE(cl0 != kp5);
  EXPECT_TRUE(cl0 != kp6);
  EXPECT_TRUE(cl0 != kp7);
  EXPECT_TRUE(cl0 != kr1);
  EXPECT_TRUE(cl0 != kr2);
  EXPECT_TRUE(cl0 != kr3);
  EXPECT_TRUE(cl0 != kr4);
  EXPECT_TRUE(cl0 != kr5);
  EXPECT_TRUE(cl0 != kr6);
  EXPECT_TRUE(cl0 != kr7);
  EXPECT_TRUE(cl0 != te1);
  EXPECT_TRUE(cl0 != te2);
  EXPECT_TRUE(cl0 != mm1);
  EXPECT_TRUE(cl0 != mm2);
  EXPECT_TRUE(cl0 != mm3);
  EXPECT_TRUE(cl0 != me1);
  EXPECT_TRUE(cl0 != ml1);
  EXPECT_TRUE(cl0 != mp1);
  EXPECT_TRUE(cl0 != mp2);
  EXPECT_TRUE(cl0 != mp3);
  EXPECT_TRUE(cl0 != mp4);
  EXPECT_TRUE(cl0 != mr1);
  EXPECT_TRUE(cl0 != mr2);
  EXPECT_TRUE(cl0 != mr3);
  EXPECT_TRUE(cl0 != mr4);
  EXPECT_TRUE(cl0 != mw1);
  EXPECT_TRUE(cl0 != mw2);
  EXPECT_TRUE(cl0 != mw3);
  EXPECT_TRUE(cl0 != mw4);
  EXPECT_TRUE(cl0 != mw5);

  EXPECT_TRUE(fg0 != em1);
  EXPECT_TRUE(fg0 != cl1);
  EXPECT_FALSE(fg0 != fg1);
  EXPECT_TRUE(fg0 != fl1);
  EXPECT_TRUE(fg0 != rs1);
  EXPECT_TRUE(fg0 != rs2);
  EXPECT_TRUE(fg0 != rs3);
  EXPECT_TRUE(fg0 != kp1);
  EXPECT_TRUE(fg0 != kp2);
  EXPECT_TRUE(fg0 != kp3);
  EXPECT_TRUE(fg0 != kp4);
  EXPECT_TRUE(fg0 != kp5);
  EXPECT_TRUE(fg0 != kp6);
  EXPECT_TRUE(fg0 != kp7);
  EXPECT_TRUE(fg0 != kr1);
  EXPECT_TRUE(fg0 != kr2);
  EXPECT_TRUE(fg0 != kr3);
  EXPECT_TRUE(fg0 != kr4);
  EXPECT_TRUE(fg0 != kr5);
  EXPECT_TRUE(fg0 != kr6);
  EXPECT_TRUE(fg0 != kr7);
  EXPECT_TRUE(fg0 != te1);
  EXPECT_TRUE(fg0 != te2);
  EXPECT_TRUE(fg0 != mm1);
  EXPECT_TRUE(fg0 != mm2);
  EXPECT_TRUE(fg0 != mm3);
  EXPECT_TRUE(fg0 != me1);
  EXPECT_TRUE(fg0 != ml1);
  EXPECT_TRUE(fg0 != mp1);
  EXPECT_TRUE(fg0 != mp2);
  EXPECT_TRUE(fg0 != mp3);
  EXPECT_TRUE(fg0 != mp4);
  EXPECT_TRUE(fg0 != mr1);
  EXPECT_TRUE(fg0 != mr2);
  EXPECT_TRUE(fg0 != mr3);
  EXPECT_TRUE(fg0 != mr4);
  EXPECT_TRUE(fg0 != mw1);
  EXPECT_TRUE(fg0 != mw2);
  EXPECT_TRUE(fg0 != mw3);
  EXPECT_TRUE(fg0 != mw4);
  EXPECT_TRUE(fg0 != mw5);

  EXPECT_TRUE(fl0 != em1);
  EXPECT_TRUE(fl0 != cl1);
  EXPECT_TRUE(fl0 != fg1);
  EXPECT_FALSE(fl0 != fl1);
  EXPECT_TRUE(fl0 != rs1);
  EXPECT_TRUE(fl0 != rs2);
  EXPECT_TRUE(fl0 != rs3);
  EXPECT_TRUE(fl0 != kp1);
  EXPECT_TRUE(fl0 != kp2);
  EXPECT_TRUE(fl0 != kp3);
  EXPECT_TRUE(fl0 != kp4);
  EXPECT_TRUE(fl0 != kp5);
  EXPECT_TRUE(fl0 != kp6);
  EXPECT_TRUE(fl0 != kp7);
  EXPECT_TRUE(fl0 != kr1);
  EXPECT_TRUE(fl0 != kr2);
  EXPECT_TRUE(fl0 != kr3);
  EXPECT_TRUE(fl0 != kr4);
  EXPECT_TRUE(fl0 != kr5);
  EXPECT_TRUE(fl0 != kr6);
  EXPECT_TRUE(fl0 != kr7);
  EXPECT_TRUE(fl0 != te1);
  EXPECT_TRUE(fl0 != te2);
  EXPECT_TRUE(fl0 != mm1);
  EXPECT_TRUE(fl0 != mm2);
  EXPECT_TRUE(fl0 != mm3);
  EXPECT_TRUE(fl0 != me1);
  EXPECT_TRUE(fl0 != ml1);
  EXPECT_TRUE(fl0 != mp1);
  EXPECT_TRUE(fl0 != mp2);
  EXPECT_TRUE(fl0 != mp3);
  EXPECT_TRUE(fl0 != mp4);
  EXPECT_TRUE(fl0 != mr1);
  EXPECT_TRUE(fl0 != mr2);
  EXPECT_TRUE(fl0 != mr3);
  EXPECT_TRUE(fl0 != mr4);
  EXPECT_TRUE(fl0 != mw1);
  EXPECT_TRUE(fl0 != mw2);
  EXPECT_TRUE(fl0 != mw3);
  EXPECT_TRUE(fl0 != mw4);
  EXPECT_TRUE(fl0 != mw5);

  EXPECT_TRUE(rs0 != em1);
  EXPECT_TRUE(rs0 != cl1);
  EXPECT_TRUE(rs0 != fg1);
  EXPECT_TRUE(rs0 != fl1);
  EXPECT_FALSE(rs0 != rs1);
  EXPECT_TRUE(rs0 != rs2);
  EXPECT_TRUE(rs0 != rs3);
  EXPECT_TRUE(rs0 != kp1);
  EXPECT_TRUE(rs0 != kp2);
  EXPECT_TRUE(rs0 != kp3);
  EXPECT_TRUE(rs0 != kp4);
  EXPECT_TRUE(rs0 != kp5);
  EXPECT_TRUE(rs0 != kp6);
  EXPECT_TRUE(rs0 != kp7);
  EXPECT_TRUE(rs0 != kr1);
  EXPECT_TRUE(rs0 != kr2);
  EXPECT_TRUE(rs0 != kr3);
  EXPECT_TRUE(rs0 != kr4);
  EXPECT_TRUE(rs0 != kr5);
  EXPECT_TRUE(rs0 != kr6);
  EXPECT_TRUE(rs0 != kr7);
  EXPECT_TRUE(rs0 != te1);
  EXPECT_TRUE(rs0 != te2);
  EXPECT_TRUE(rs0 != mm1);
  EXPECT_TRUE(rs0 != mm2);
  EXPECT_TRUE(rs0 != mm3);
  EXPECT_TRUE(rs0 != me1);
  EXPECT_TRUE(rs0 != ml1);
  EXPECT_TRUE(rs0 != mp1);
  EXPECT_TRUE(rs0 != mp2);
  EXPECT_TRUE(rs0 != mp3);
  EXPECT_TRUE(rs0 != mp4);
  EXPECT_TRUE(rs0 != mr1);
  EXPECT_TRUE(rs0 != mr2);
  EXPECT_TRUE(rs0 != mr3);
  EXPECT_TRUE(rs0 != mr4);
  EXPECT_TRUE(rs0 != mw1);
  EXPECT_TRUE(rs0 != mw2);
  EXPECT_TRUE(rs0 != mw3);
  EXPECT_TRUE(rs0 != mw4);
  EXPECT_TRUE(rs0 != mw5);

  EXPECT_TRUE(kp0 != em1);
  EXPECT_TRUE(kp0 != cl1);
  EXPECT_TRUE(kp0 != fg1);
  EXPECT_TRUE(kp0 != fl1);
  EXPECT_TRUE(kp0 != rs1);
  EXPECT_TRUE(kp0 != rs2);
  EXPECT_TRUE(kp0 != rs3);
  EXPECT_FALSE(kp0 != kp1);
  EXPECT_TRUE(kp0 != kp2);
  EXPECT_TRUE(kp0 != kp3);
  EXPECT_TRUE(kp0 != kp4);
  EXPECT_TRUE(kp0 != kp5);
  EXPECT_TRUE(kp0 != kp6);
  EXPECT_TRUE(kp0 != kp7);
  EXPECT_TRUE(kp0 != kr1);
  EXPECT_TRUE(kp0 != kr2);
  EXPECT_TRUE(kp0 != kr3);
  EXPECT_TRUE(kp0 != kr4);
  EXPECT_TRUE(kp0 != kr5);
  EXPECT_TRUE(kp0 != kr6);
  EXPECT_TRUE(kp0 != kr7);
  EXPECT_TRUE(kp0 != te1);
  EXPECT_TRUE(kp0 != te2);
  EXPECT_TRUE(kp0 != mm1);
  EXPECT_TRUE(kp0 != mm2);
  EXPECT_TRUE(kp0 != mm3);
  EXPECT_TRUE(kp0 != me1);
  EXPECT_TRUE(kp0 != ml1);
  EXPECT_TRUE(kp0 != mp1);
  EXPECT_TRUE(kp0 != mp2);
  EXPECT_TRUE(kp0 != mp3);
  EXPECT_TRUE(kp0 != mp4);
  EXPECT_TRUE(kp0 != mr1);
  EXPECT_TRUE(kp0 != mr2);
  EXPECT_TRUE(kp0 != mr3);
  EXPECT_TRUE(kp0 != mr4);
  EXPECT_TRUE(kp0 != mw1);
  EXPECT_TRUE(kp0 != mw2);
  EXPECT_TRUE(kp0 != mw3);
  EXPECT_TRUE(kp0 != mw4);
  EXPECT_TRUE(kp0 != mw5);

  EXPECT_TRUE(kr0 != em1);
  EXPECT_TRUE(kr0 != cl1);
  EXPECT_TRUE(kr0 != fg1);
  EXPECT_TRUE(kr0 != fl1);
  EXPECT_TRUE(kr0 != rs1);
  EXPECT_TRUE(kr0 != rs2);
  EXPECT_TRUE(kr0 != rs3);
  EXPECT_TRUE(kr0 != kp1);
  EXPECT_TRUE(kr0 != kp2);
  EXPECT_TRUE(kr0 != kp3);
  EXPECT_TRUE(kr0 != kp4);
  EXPECT_TRUE(kr0 != kp5);
  EXPECT_TRUE(kr0 != kp6);
  EXPECT_TRUE(kr0 != kp7);
  EXPECT_FALSE(kr0 != kr1);
  EXPECT_TRUE(kr0 != kr2);
  EXPECT_TRUE(kr0 != kr3);
  EXPECT_TRUE(kr0 != kr4);
  EXPECT_TRUE(kr0 != kr5);
  EXPECT_TRUE(kr0 != kr6);
  EXPECT_TRUE(kr0 != kr7);
  EXPECT_TRUE(kr0 != te1);
  EXPECT_TRUE(kr0 != te2);
  EXPECT_TRUE(kr0 != mm1);
  EXPECT_TRUE(kr0 != mm2);
  EXPECT_TRUE(kr0 != mm3);
  EXPECT_TRUE(kr0 != me1);
  EXPECT_TRUE(kr0 != ml1);
  EXPECT_TRUE(kr0 != mp1);
  EXPECT_TRUE(kr0 != mp2);
  EXPECT_TRUE(kr0 != mp3);
  EXPECT_TRUE(kr0 != mp4);
  EXPECT_TRUE(kr0 != mr1);
  EXPECT_TRUE(kr0 != mr2);
  EXPECT_TRUE(kr0 != mr3);
  EXPECT_TRUE(kr0 != mr4);
  EXPECT_TRUE(kr0 != mw1);
  EXPECT_TRUE(kr0 != mw2);
  EXPECT_TRUE(kr0 != mw3);
  EXPECT_TRUE(kr0 != mw4);
  EXPECT_TRUE(kr0 != mw5);

  EXPECT_TRUE(te0 != em1);
  EXPECT_TRUE(te0 != cl1);
  EXPECT_TRUE(te0 != fg1);
  EXPECT_TRUE(te0 != fl1);
  EXPECT_TRUE(te0 != rs1);
  EXPECT_TRUE(te0 != rs2);
  EXPECT_TRUE(te0 != rs3);
  EXPECT_TRUE(te0 != kp1);
  EXPECT_TRUE(te0 != kp2);
  EXPECT_TRUE(te0 != kp3);
  EXPECT_TRUE(te0 != kp4);
  EXPECT_TRUE(te0 != kp5);
  EXPECT_TRUE(te0 != kp6);
  EXPECT_TRUE(te0 != kp7);
  EXPECT_TRUE(te0 != kr1);
  EXPECT_TRUE(te0 != kr2);
  EXPECT_TRUE(te0 != kr3);
  EXPECT_TRUE(te0 != kr4);
  EXPECT_TRUE(te0 != kr5);
  EXPECT_TRUE(te0 != kr6);
  EXPECT_TRUE(te0 != kr7);
  EXPECT_FALSE(te0 != te1);
  EXPECT_TRUE(te0 != te2);
  EXPECT_TRUE(te0 != mm1);
  EXPECT_TRUE(te0 != mm2);
  EXPECT_TRUE(te0 != mm3);
  EXPECT_TRUE(te0 != me1);
  EXPECT_TRUE(te0 != ml1);
  EXPECT_TRUE(te0 != mp1);
  EXPECT_TRUE(te0 != mp2);
  EXPECT_TRUE(te0 != mp3);
  EXPECT_TRUE(te0 != mp4);
  EXPECT_TRUE(te0 != mr1);
  EXPECT_TRUE(te0 != mr2);
  EXPECT_TRUE(te0 != mr3);
  EXPECT_TRUE(te0 != mr4);
  EXPECT_TRUE(te0 != mw1);
  EXPECT_TRUE(te0 != mw2);
  EXPECT_TRUE(te0 != mw3);
  EXPECT_TRUE(te0 != mw4);
  EXPECT_TRUE(te0 != mw5);

  EXPECT_TRUE(mm0 != em1);
  EXPECT_TRUE(mm0 != cl1);
  EXPECT_TRUE(mm0 != fg1);
  EXPECT_TRUE(mm0 != fl1);
  EXPECT_TRUE(mm0 != rs1);
  EXPECT_TRUE(mm0 != rs2);
  EXPECT_TRUE(mm0 != rs3);
  EXPECT_TRUE(mm0 != kp1);
  EXPECT_TRUE(mm0 != kp2);
  EXPECT_TRUE(mm0 != kp3);
  EXPECT_TRUE(mm0 != kp4);
  EXPECT_TRUE(mm0 != kp5);
  EXPECT_TRUE(mm0 != kp6);
  EXPECT_TRUE(mm0 != kp7);
  EXPECT_TRUE(mm0 != kr1);
  EXPECT_TRUE(mm0 != kr2);
  EXPECT_TRUE(mm0 != kr3);
  EXPECT_TRUE(mm0 != kr4);
  EXPECT_TRUE(mm0 != kr5);
  EXPECT_TRUE(mm0 != kr6);
  EXPECT_TRUE(mm0 != kr7);
  EXPECT_TRUE(mm0 != te1);
  EXPECT_TRUE(mm0 != te2);
  EXPECT_FALSE(mm0 != mm1);
  EXPECT_TRUE(mm0 != mm2);
  EXPECT_TRUE(mm0 != mm3);
  EXPECT_TRUE(mm0 != me1);
  EXPECT_TRUE(mm0 != ml1);
  EXPECT_TRUE(mm0 != mp1);
  EXPECT_TRUE(mm0 != mp2);
  EXPECT_TRUE(mm0 != mp3);
  EXPECT_TRUE(mm0 != mp4);
  EXPECT_TRUE(mm0 != mr1);
  EXPECT_TRUE(mm0 != mr2);
  EXPECT_TRUE(mm0 != mr3);
  EXPECT_TRUE(mm0 != mr4);
  EXPECT_TRUE(mm0 != mw1);
  EXPECT_TRUE(mm0 != mw2);
  EXPECT_TRUE(mm0 != mw3);
  EXPECT_TRUE(mm0 != mw4);
  EXPECT_TRUE(mm0 != mw5);

  EXPECT_TRUE(me0 != em1);
  EXPECT_TRUE(me0 != cl1);
  EXPECT_TRUE(me0 != fg1);
  EXPECT_TRUE(me0 != fl1);
  EXPECT_TRUE(me0 != rs1);
  EXPECT_TRUE(me0 != rs2);
  EXPECT_TRUE(me0 != rs3);
  EXPECT_TRUE(me0 != kp1);
  EXPECT_TRUE(me0 != kp2);
  EXPECT_TRUE(me0 != kp3);
  EXPECT_TRUE(me0 != kp4);
  EXPECT_TRUE(me0 != kp5);
  EXPECT_TRUE(me0 != kp6);
  EXPECT_TRUE(me0 != kp7);
  EXPECT_TRUE(me0 != kr1);
  EXPECT_TRUE(me0 != kr2);
  EXPECT_TRUE(me0 != kr3);
  EXPECT_TRUE(me0 != kr4);
  EXPECT_TRUE(me0 != kr5);
  EXPECT_TRUE(me0 != kr6);
  EXPECT_TRUE(me0 != kr7);
  EXPECT_TRUE(me0 != te1);
  EXPECT_TRUE(me0 != te2);
  EXPECT_TRUE(me0 != mm1);
  EXPECT_TRUE(me0 != mm2);
  EXPECT_TRUE(me0 != mm3);
  EXPECT_FALSE(me0 != me1);
  EXPECT_TRUE(me0 != ml1);
  EXPECT_TRUE(me0 != mp1);
  EXPECT_TRUE(me0 != mp2);
  EXPECT_TRUE(me0 != mp3);
  EXPECT_TRUE(me0 != mp4);
  EXPECT_TRUE(me0 != mr1);
  EXPECT_TRUE(me0 != mr2);
  EXPECT_TRUE(me0 != mr3);
  EXPECT_TRUE(me0 != mr4);
  EXPECT_TRUE(me0 != mw1);
  EXPECT_TRUE(me0 != mw2);
  EXPECT_TRUE(me0 != mw3);
  EXPECT_TRUE(me0 != mw4);
  EXPECT_TRUE(me0 != mw5);

  EXPECT_TRUE(ml0 != em1);
  EXPECT_TRUE(ml0 != cl1);
  EXPECT_TRUE(ml0 != fg1);
  EXPECT_TRUE(ml0 != fl1);
  EXPECT_TRUE(ml0 != rs1);
  EXPECT_TRUE(ml0 != rs2);
  EXPECT_TRUE(ml0 != rs3);
  EXPECT_TRUE(ml0 != kp1);
  EXPECT_TRUE(ml0 != kp2);
  EXPECT_TRUE(ml0 != kp3);
  EXPECT_TRUE(ml0 != kp4);
  EXPECT_TRUE(ml0 != kp5);
  EXPECT_TRUE(ml0 != kp6);
  EXPECT_TRUE(ml0 != kp7);
  EXPECT_TRUE(ml0 != kr1);
  EXPECT_TRUE(ml0 != kr2);
  EXPECT_TRUE(ml0 != kr3);
  EXPECT_TRUE(ml0 != kr4);
  EXPECT_TRUE(ml0 != kr5);
  EXPECT_TRUE(ml0 != kr6);
  EXPECT_TRUE(ml0 != kr7);
  EXPECT_TRUE(ml0 != te1);
  EXPECT_TRUE(ml0 != te2);
  EXPECT_TRUE(ml0 != mm1);
  EXPECT_TRUE(ml0 != mm2);
  EXPECT_TRUE(ml0 != mm3);
  EXPECT_TRUE(ml0 != me1);
  EXPECT_FALSE(ml0 != ml1);
  EXPECT_TRUE(ml0 != mp1);
  EXPECT_TRUE(ml0 != mp2);
  EXPECT_TRUE(ml0 != mp3);
  EXPECT_TRUE(ml0 != mp4);
  EXPECT_TRUE(ml0 != mr1);
  EXPECT_TRUE(ml0 != mr2);
  EXPECT_TRUE(ml0 != mr3);
  EXPECT_TRUE(ml0 != mr4);
  EXPECT_TRUE(ml0 != mw1);
  EXPECT_TRUE(ml0 != mw2);
  EXPECT_TRUE(ml0 != mw3);
  EXPECT_TRUE(ml0 != mw4);
  EXPECT_TRUE(ml0 != mw5);

  EXPECT_TRUE(mp0 != em1);
  EXPECT_TRUE(mp0 != cl1);
  EXPECT_TRUE(mp0 != fg1);
  EXPECT_TRUE(mp0 != fl1);
  EXPECT_TRUE(mp0 != rs1);
  EXPECT_TRUE(mp0 != rs2);
  EXPECT_TRUE(mp0 != rs3);
  EXPECT_TRUE(mp0 != kp1);
  EXPECT_TRUE(mp0 != kp2);
  EXPECT_TRUE(mp0 != kp3);
  EXPECT_TRUE(mp0 != kp4);
  EXPECT_TRUE(mp0 != kp5);
  EXPECT_TRUE(mp0 != kp6);
  EXPECT_TRUE(mp0 != kp7);
  EXPECT_TRUE(mp0 != kr1);
  EXPECT_TRUE(mp0 != kr2);
  EXPECT_TRUE(mp0 != kr3);
  EXPECT_TRUE(mp0 != kr4);
  EXPECT_TRUE(mp0 != kr5);
  EXPECT_TRUE(mp0 != kr6);
  EXPECT_TRUE(mp0 != kr7);
  EXPECT_TRUE(mp0 != te1);
  EXPECT_TRUE(mp0 != te2);
  EXPECT_TRUE(mp0 != mm1);
  EXPECT_TRUE(mp0 != mm2);
  EXPECT_TRUE(mp0 != mm3);
  EXPECT_TRUE(mp0 != me1);
  EXPECT_TRUE(mp0 != ml1);
  EXPECT_FALSE(mp0 != mp1);
  EXPECT_TRUE(mp0 != mp2);
  EXPECT_TRUE(mp0 != mp3);
  EXPECT_TRUE(mp0 != mp4);
  EXPECT_TRUE(mp0 != mr1);
  EXPECT_TRUE(mp0 != mr2);
  EXPECT_TRUE(mp0 != mr3);
  EXPECT_TRUE(mp0 != mr4);
  EXPECT_TRUE(mp0 != mw1);
  EXPECT_TRUE(mp0 != mw2);
  EXPECT_TRUE(mp0 != mw3);
  EXPECT_TRUE(mp0 != mw4);
  EXPECT_TRUE(mp0 != mw5);

  EXPECT_TRUE(mr0 != em1);
  EXPECT_TRUE(mr0 != cl1);
  EXPECT_TRUE(mr0 != fg1);
  EXPECT_TRUE(mr0 != fl1);
  EXPECT_TRUE(mr0 != rs1);
  EXPECT_TRUE(mr0 != rs2);
  EXPECT_TRUE(mr0 != rs3);
  EXPECT_TRUE(mr0 != kp1);
  EXPECT_TRUE(mr0 != kp2);
  EXPECT_TRUE(mr0 != kp3);
  EXPECT_TRUE(mr0 != kp4);
  EXPECT_TRUE(mr0 != kp5);
  EXPECT_TRUE(mr0 != kp6);
  EXPECT_TRUE(mr0 != kp7);
  EXPECT_TRUE(mr0 != kr1);
  EXPECT_TRUE(mr0 != kr2);
  EXPECT_TRUE(mr0 != kr3);
  EXPECT_TRUE(mr0 != kr4);
  EXPECT_TRUE(mr0 != kr5);
  EXPECT_TRUE(mr0 != kr6);
  EXPECT_TRUE(mr0 != kr7);
  EXPECT_TRUE(mr0 != te1);
  EXPECT_TRUE(mr0 != te2);
  EXPECT_TRUE(mr0 != mm1);
  EXPECT_TRUE(mr0 != mm2);
  EXPECT_TRUE(mr0 != mm3);
  EXPECT_TRUE(mr0 != me1);
  EXPECT_TRUE(mr0 != ml1);
  EXPECT_TRUE(mr0 != mp1);
  EXPECT_TRUE(mr0 != mp2);
  EXPECT_TRUE(mr0 != mp3);
  EXPECT_TRUE(mr0 != mp4);
  EXPECT_FALSE(mr0 != mr1);
  EXPECT_TRUE(mr0 != mr2);
  EXPECT_TRUE(mr0 != mr3);
  EXPECT_TRUE(mr0 != mr4);
  EXPECT_TRUE(mr0 != mw1);
  EXPECT_TRUE(mr0 != mw2);
  EXPECT_TRUE(mr0 != mw3);
  EXPECT_TRUE(mr0 != mw4);
  EXPECT_TRUE(mr0 != mw5);

  EXPECT_TRUE(mw0 != em1);
  EXPECT_TRUE(mw0 != cl1);
  EXPECT_TRUE(mw0 != fg1);
  EXPECT_TRUE(mw0 != fl1);
  EXPECT_TRUE(mw0 != rs1);
  EXPECT_TRUE(mw0 != rs2);
  EXPECT_TRUE(mw0 != rs3);
  EXPECT_TRUE(mw0 != kp1);
  EXPECT_TRUE(mw0 != kp2);
  EXPECT_TRUE(mw0 != kp3);
  EXPECT_TRUE(mw0 != kp4);
  EXPECT_TRUE(mw0 != kp5);
  EXPECT_TRUE(mw0 != kp6);
  EXPECT_TRUE(mw0 != kp7);
  EXPECT_TRUE(mw0 != kr1);
  EXPECT_TRUE(mw0 != kr2);
  EXPECT_TRUE(mw0 != kr3);
  EXPECT_TRUE(mw0 != kr4);
  EXPECT_TRUE(mw0 != kr5);
  EXPECT_TRUE(mw0 != kr6);
  EXPECT_TRUE(mw0 != kr7);
  EXPECT_TRUE(mw0 != te1);
  EXPECT_TRUE(mw0 != te2);
  EXPECT_TRUE(mw0 != mm1);
  EXPECT_TRUE(mw0 != mm2);
  EXPECT_TRUE(mw0 != mm3);
  EXPECT_TRUE(mw0 != me1);
  EXPECT_TRUE(mw0 != ml1);
  EXPECT_TRUE(mw0 != mp1);
  EXPECT_TRUE(mw0 != mp2);
  EXPECT_TRUE(mw0 != mp3);
  EXPECT_TRUE(mw0 != mp4);
  EXPECT_TRUE(mw0 != mr1);
  EXPECT_TRUE(mw0 != mr2);
  EXPECT_TRUE(mw0 != mr3);
  EXPECT_TRUE(mw0 != mr4);
  EXPECT_FALSE(mw0 != mw1);
  EXPECT_TRUE(mw0 != mw2);
  EXPECT_TRUE(mw0 != mw3);
  EXPECT_TRUE(mw0 != mw4);
  EXPECT_TRUE(mw0 != mw5);
}



TEST_F(TestWindowEvent, EmptyOutputStreamOperator)
{
  WindowEvent ev = WindowEvent::empty();
  const char* osRef = "{Type = Empty, Data = {}}";
  HOU_EXPECT_OUTPUT(osRef, ev);
}



TEST_F(TestWindowEvent, ClosedOutputStreamOperator)
{
  WindowEvent ev = WindowEvent::closed();
  const char* osRef = "{Type = Closed, Data = {}}";
  HOU_EXPECT_OUTPUT(osRef, ev);
}



TEST_F(TestWindowEvent, FocusGainedOutputStreamOperator)
{
  WindowEvent ev = WindowEvent::focusGained();
  const char* osRef = "{Type = FocusGained, Data = {}}";
  HOU_EXPECT_OUTPUT(osRef, ev);
}



TEST_F(TestWindowEvent, FocusLostOutputStreamOperator)
{
  WindowEvent ev = WindowEvent::focusLost();
  const char* osRef = "{Type = FocusLost, Data = {}}";
  HOU_EXPECT_OUTPUT(osRef, ev);
}



TEST_F(TestWindowEvent, ResizedOutputStreamOperator)
{
  WindowEvent ev = WindowEvent::resized(1u, 3u);
  const char* osRef = "{Type = Resized, Data = {Size = (1, 3)}}";
  HOU_EXPECT_OUTPUT(osRef, ev);
}



TEST_F(TestWindowEvent, KeyPressedOutputStreamOperator)
{
  WindowEvent ev = WindowEvent::keyPressed(KeyCode::A, ScanCode::Q
    , ModifierKeys::Alt | ModifierKeys::Shift);
  const char* osRef = "{Type = KeyPressed, Data = {KeyCode = A, ScanCode = Q, "
    "ModifierKeys = Alt | 0 | Shift | 0}}";
  HOU_EXPECT_OUTPUT(osRef, ev);
}



TEST_F(TestWindowEvent, KeyReleasedOutputStreamOperator)
{
  WindowEvent ev = WindowEvent::keyReleased(KeyCode::A, ScanCode::Q
    , ModifierKeys::Alt | ModifierKeys::Ctrl | ModifierKeys::System);
  const char* osRef = "{Type = KeyReleased, Data = {KeyCode = A, ScanCode = Q, "
    "ModifierKeys = Alt | Ctrl | 0 | System}}";
  HOU_EXPECT_OUTPUT(osRef, ev);
}



TEST_F(TestWindowEvent, TextEnteredOutputStreamOperator)
{
  WindowEvent ev = WindowEvent::textEntered(0x13fa);
  const char* osRef = "{Type = TextEntered, Data = {CodePoint = 0x000013fa}}";
  HOU_EXPECT_OUTPUT(osRef, ev);
}



TEST_F(TestWindowEvent, MouseMovedOutputStreamOperator)
{
  WindowEvent ev = WindowEvent::mouseMoved(1, 3);
  const char* osRef = "{Type = MouseMoved, Data = {Position = (1, 3)}}";
  HOU_EXPECT_OUTPUT(osRef, ev);
}



TEST_F(TestWindowEvent, MouseEnteredOutputStreamOperator)
{
  WindowEvent ev = WindowEvent::mouseEntered();
  const char* osRef = "{Type = MouseEntered, Data = {}}";
  HOU_EXPECT_OUTPUT(osRef, ev);
}



TEST_F(TestWindowEvent, MouseLeftOutputStreamOperator)
{
  WindowEvent ev = WindowEvent::mouseLeft();
  const char* osRef = "{Type = MouseLeft, Data = {}}";
  HOU_EXPECT_OUTPUT(osRef, ev);
}



TEST_F(TestWindowEvent, MouseButtonPressedOutputStreamOperator)
{
  WindowEvent ev = WindowEvent::mouseButtonPressed(MouseButton::LB, 1, 3);
  const char* osRef = "{Type = MouseButtonPressed, Data = {Button = LB, "
    "Position = (1, 3)}}";
  HOU_EXPECT_OUTPUT(osRef, ev);
}



TEST_F(TestWindowEvent, MouseButtonReleasedOutputStreamOperator)
{
  WindowEvent ev = WindowEvent::mouseButtonReleased(MouseButton::LB, 1, 3);
  const char* osRef = "{Type = MouseButtonReleased, Data = {Button = LB, "
    "Position = (1, 3)}}";
  HOU_EXPECT_OUTPUT(osRef, ev);
}



TEST_F(TestWindowEvent, MouseWheelMovedOutputStreamOperator)
{
  WindowEvent ev = WindowEvent::mouseWheelMoved(MouseWheel::Vertical, 5, 1, 3);
  const char* osRef = "{Type = MouseWheelMoved, Data = {Wheel = Vertical, "
    "Delta = 5, Position = (1, 3)}}";
  HOU_EXPECT_OUTPUT(osRef, ev);
}

