////////////////////////////////////////////////////////////
//
// XEPHENGINE
// Copyright (C) 2022 Jon Bogert (jonbogert@gmail.com)
//
// This software is provided 'as-is', without any express or implied warranty.
// In no event will the authors be held liable for any damages arising from the use of this software.
//
// Permission is granted to anyone to use this software for any purpose,
// including commercial applications, and to alter it and redistribute it freely,
// subject to the following restrictions:
//
// 1. The origin of this software must not be misrepresented;
//    you must not claim that you wrote the original software.
//    If you use this software in a product, an acknowledgment
//    in the product documentation would be appreciated but is not required.
//
// 2. Altered source versions must be plainly marked as such,
//    and must not be misrepresented as being the original software.
//
// 3. This notice may not be removed or altered from any source distribution.
//
////////////////////////////////////////////////////////////

//NOTE: This file has been slightly modified for Compatibility outside of the rest of the engine (Annotated with //*)

//* removed reference to EngineUtils.h
#include "Pch.h"
#include "InputSystem.h"
#include <windows.h>
#include <xinput.h>
#include <vector> //* added
#include <iostream> //* added

sf::Event inputEvent;

std::vector<xe::Key> keyHold;
std::vector<xe::Mouse> mButtonHold;
std::vector<std::pair<int, xe::Button>> buttonHold;
std::vector<std::pair<std::string, sf::Vector2f>> keyAxis2DBuffer; //* xe:Vector2 -> sf::Vector2f
std::vector<std::pair<std::string, float >> keyAxis1DBuffer;
float axisThrow = 15.f;
bool init = true;

//* removed struct XE_CONTROLLER_TRIG
float deadZoneMin = 0.3f;
float deadZoneMax = 1.f;

sf::Vector2f mousePosPrev = { 0,0 }; //* xe:Vector2 -> sf::Vector2f
float mouseSensitivity = 1.f;

sf::Vector2f GetTriggerPosition(int playrIndex) //* XE_CONTROLLER_TRIG -> sf::Vector2f
{
	XINPUT_STATE state{};
	ZeroMemory(&state, sizeof(XINPUT_STATE));
	XInputGetState(0, &state);
	return { (float)state.Gamepad.bLeftTrigger / 255, (float)state.Gamepad.bRightTrigger / 255 };
}

float DeadZone(const float input)
{
	if (fabs(input) < deadZoneMin)
	{
		return 0.f;
	}
	else if (fabs(input) > deadZoneMax)
	{
		if (input >= 0.f) { return 1.f; }
		else { return -1.f; }
	}
	else
	{
		if (input >= 0.f)
		{
			return (input - deadZoneMin) * (1 / (deadZoneMax - deadZoneMin));
		}
		else
		{
			return (input + deadZoneMin) * (1 / (deadZoneMax - deadZoneMin));
		}
	}
}

//* Removed Update and CloseWindow Functions

float xe::InputSystem::KeyAxis1D(const Key pos, const Key neg, float deltaTime) //* Added independant deltaTime param
{
	float target{};
	std::string axisId{};
	//get AxisID
	axisId.append(std::to_string((int)pos));
	axisId.append(std::to_string((int)neg));

	//Find initial direcrions
	if (KeyHold(pos) && !KeyHold(neg))
		target = 1;
	else if (!KeyHold(pos) && KeyHold(neg))
		target = -1;

	//check exist in buffer
	bool inBuffer{};
	int index{};

	for (std::pair<std::string, float> entry : keyAxis1DBuffer)
	{
		if (entry.first == axisId)
		{
			inBuffer = true;
			break;
		}
		else index++;
	}

	//Check to destroy
	if (inBuffer && target == 0 && keyAxis1DBuffer[index].second == 0)
	{
		keyAxis1DBuffer.erase(keyAxis1DBuffer.begin() + index);
	}
	//Buffer needs to exist
	else
	{
		float axisThrowDT = axisThrow * deltaTime; //* Time::DeltaTime() -> deltaTime
		//Create buffer if doesn't exist
		if (!inBuffer)
			keyAxis1DBuffer.push_back({ axisId, 0.f });

		//Apply Throw
		if ((keyAxis1DBuffer[index].second < target) && (keyAxis1DBuffer[index].second + axisThrowDT < target))
		{
			keyAxis1DBuffer[index].second += axisThrowDT;
		}
		else if ((keyAxis1DBuffer[index].second > target) && (keyAxis1DBuffer[index].second - axisThrowDT > target))
		{
			keyAxis1DBuffer[index].second -= axisThrowDT;
		}
		else if (((keyAxis1DBuffer[index].second < target) && (keyAxis1DBuffer[index].second + axisThrowDT >= target))
			|| ((keyAxis1DBuffer[index].second > target) && (keyAxis1DBuffer[index].second - axisThrowDT <= target)))
		{
			keyAxis1DBuffer[index].second = target;
		}

		return keyAxis1DBuffer[index].second;
	}

	return 0.f;
}

sf::Vector2f xe::InputSystem::KeyAxis2D(const Key posX, const Key negX, const Key posY, const Key negY, float deltaTime) //* xe:Vector2 -> sf::Vector2f / Added independant deltaTime param
{
	sf::Vector2f target{}; //* xe:Vector2 -> sf::Vector2f
	std::string axisId{};
	//get AxisID
	axisId.append(std::to_string((int)posX));
	axisId.append(std::to_string((int)negX));
	axisId.append(std::to_string((int)posY));
	axisId.append(std::to_string((int)negY));

	//Find initial direcrions
	if (KeyHold(posX) && !KeyHold(negX))
		target.x = 1;
	else if (!KeyHold(posX) && KeyHold(negX))
		target.x = -1;

	if (KeyHold(posY) && !KeyHold(negY))
		target.y = 1;
	else if (!KeyHold(posY) && KeyHold(negY))
		target.y = -1;

	if (target.x != 0 && target.y != 0)
	{
		target.x = sqrtf(0.5f)* target.x;
		target.y = sqrtf(0.5f)* target.y;
	}

	//check exist in buffer
	bool inBuffer{};
	int index{};

	for (std::pair<std::string, sf::Vector2f> entry : keyAxis2DBuffer) //* xe:Vector2 -> sf::Vector2f
	{
		if (entry.first == axisId)
		{
			inBuffer = true;
			break;
		}
		else index++;
	}

	//Check to destroy
	if (inBuffer && target.x == 0 && target.y == 0
		&& keyAxis2DBuffer[index].second.x == 0
		&& keyAxis2DBuffer[index].second.y == 0)
	{
		keyAxis2DBuffer.erase(keyAxis2DBuffer.begin() + index);
	}
	//Buffer needs to exist
	else
	{
		float axisThrowDT = axisThrow * deltaTime; //* Time::DeltaTime() -> deltaTime
		//Create buffer if doesn't exist
		if (!inBuffer)
			keyAxis2DBuffer.push_back({ axisId, sf::Vector2f() }); //* xe:Vector2 -> sf::Vector2f

		//Apply Throw
		if ((keyAxis2DBuffer[index].second.x < target.x) && (keyAxis2DBuffer[index].second.x + axisThrowDT < target.x))
		{
			keyAxis2DBuffer[index].second.x += axisThrowDT;
		}
		else if ((keyAxis2DBuffer[index].second.x > target.x) && (keyAxis2DBuffer[index].second.x - axisThrowDT > target.x))
		{
			keyAxis2DBuffer[index].second.x -= axisThrowDT;
		}
		else if (((keyAxis2DBuffer[index].second.x < target.x) && (keyAxis2DBuffer[index].second.x + axisThrowDT >= target.x))
			|| ((keyAxis2DBuffer[index].second.x > target.x) && (keyAxis2DBuffer[index].second.x - axisThrowDT <= target.x)))
		{
			keyAxis2DBuffer[index].second.x = target.x;
		}

		if ((keyAxis2DBuffer[index].second.y < target.y) && (keyAxis2DBuffer[index].second.y + axisThrowDT < target.y))
		{
			keyAxis2DBuffer[index].second.y += axisThrowDT;
		}
		else if ((keyAxis2DBuffer[index].second.y > target.y) && (keyAxis2DBuffer[index].second.y - axisThrowDT > target.y))
		{
			keyAxis2DBuffer[index].second.y -= axisThrowDT;
		}
		else if (((keyAxis2DBuffer[index].second.y < target.y) && (keyAxis2DBuffer[index].second.y + axisThrowDT >= target.y))
			|| ((keyAxis2DBuffer[index].second.y > target.y) && (keyAxis2DBuffer[index].second.y - axisThrowDT <= target.y)))
		{
			keyAxis2DBuffer[index].second.y = target.y;
		}

		return keyAxis2DBuffer[index].second;
	}

	return sf::Vector2f(); //* xe:Vector2 -> sf::Vector2f
}

bool xe::InputSystem::KeyHold(const Key key)
{
	return sf::Keyboard::isKeyPressed((sf::Keyboard::Key)key);
}

xe::Event xe::InputSystem::KeyEvent(const Key key)
{
	bool keyFound{};
	int index{};
	for (xe::Key k : keyHold)
	{
		if (k == key)
		{
			keyFound = true;
			break;
		}
		else index++;
	}

	if (sf::Keyboard::isKeyPressed((sf::Keyboard::Key)key))
	{
		if (!keyFound)
		{
			keyHold.push_back(key);
			return Pressed;
		}
	}
	else if (keyFound)
	{
		keyHold.erase(keyHold.begin() + index);
		return Released;
	}

	return None;
}

sf::Vector2f xe::InputSystem::GetAxis(int playerIndex, Axis axis) //* xe:Vector2 -> sf::Vector2f
{
	sf::Vector2f result{};//* xe:Vector2 -> sf::Vector2f

	switch (axis)
	{
	case Axis::LS:
		result.x = DeadZone(sf::Joystick::getAxisPosition(playerIndex, sf::Joystick::X) / 100.f);
		result.y = DeadZone(sf::Joystick::getAxisPosition(playerIndex, sf::Joystick::Y) / -100.f);
		break;
	case Axis::RS:
		result.x = DeadZone(sf::Joystick::getAxisPosition(playerIndex, sf::Joystick::U) / 100.f);
		result.y = DeadZone(sf::Joystick::getAxisPosition(playerIndex, sf::Joystick::V) / -100.f);
		break;
	case Axis::DPad:
		result.x = DeadZone(sf::Joystick::getAxisPosition(playerIndex, sf::Joystick::PovX) / 100.f);
		result.y = DeadZone(sf::Joystick::getAxisPosition(playerIndex, sf::Joystick::PovY) / 100.f);
		break;
	case Axis::Trig:
		//result = { GetTriggerPosition(playerIndex).LT, GetTriggerPosition(playerIndex).RT };
		result = GetTriggerPosition(playerIndex); //* changed from above
		break;
	}

	return result;
}

bool xe::InputSystem::ButtonHold(const int playerIndex, const Button button)
{
	if (button <= Button::RS_Press)
	{
		return sf::Joystick::isButtonPressed(playerIndex, (int)button);
	}

	switch (button)
	{
	case Button::LT:
		return (GetAxis(playerIndex, Axis::Trig).x > 0);
		break;
	case Button::RT:
		return (GetAxis(playerIndex, Axis::Trig).y > 0);
		break;

	case Button::LS_Up:
		return (GetAxis(playerIndex, Axis::LS).y > 0);
		break;
	case Button::LS_Down:
		return (GetAxis(playerIndex, Axis::LS).y < 0);
		break;
	case Button::LS_Left:
		return (GetAxis(playerIndex, Axis::LS).x < 0);
		break;
	case Button::LS_Right:
		return (GetAxis(playerIndex, Axis::LS).x > 0);
		break;

	case Button::RS_Up:
		return (GetAxis(playerIndex, Axis::RS).y > 0);
		break;
	case Button::RS_Down:
		return (GetAxis(playerIndex, Axis::RS).y < 0);
		break;
	case Button::RS_Left:
		return (GetAxis(playerIndex, Axis::RS).x < 0);
		break;
	case Button::RS_Right:
		return (GetAxis(playerIndex, Axis::RS).x > 0);
		break;

	case Button::DPad_Up:
		return (GetAxis(playerIndex, Axis::DPad).y > 0);
		break;
	case Button::DPad_Down:
		return (GetAxis(playerIndex, Axis::DPad).y < 0);
		break;
	case Button::DPad_Left:
		return (GetAxis(playerIndex, Axis::DPad).x < 0);
		break;
	case Button::DPad_Right:
		return (GetAxis(playerIndex, Axis::DPad).x > 0);
		break;
	}
	return false;
}

xe::Event xe::InputSystem::ButtonEvent(const int playerIndex, const Button button)
{
	bool buttonFound{};
	int index{};
	for (std::pair<int, Button> b : buttonHold)
	{
		if (b.first == playerIndex && b.second == button)
		{
			buttonFound = true;
			break;
		}
		else index++;
	}

	if (ButtonHold(playerIndex, button))
	{
		if (!buttonFound)
		{
			buttonHold.push_back({ playerIndex, button });
			return Pressed;
		}
	}
	else if (buttonFound)
	{
		buttonHold.erase(buttonHold.begin() + index);
		return Released;
	}

	return None;
}

bool xe::InputSystem::MouseHold(const Mouse mouseButton)
{
	return sf::Mouse::isButtonPressed((sf::Mouse::Button)mouseButton);
}

xe::Event xe::InputSystem::MouseEvent(const Mouse mouseButton)
{
	bool buttonFound{};
	int index{};
	for (Mouse b : mButtonHold)
	{
		if (b == mouseButton)
		{
			buttonFound = true;
			break;
		}
		else index++;
	}

	if (MouseHold(mouseButton))
	{
		if (!buttonFound)
		{
			mButtonHold.push_back(mouseButton);
			return Pressed;
		}
	}
	else if (buttonFound)
	{
		mButtonHold.erase(mButtonHold.begin() + index);
		return Released;
	}

	return None;
}

int xe::InputSystem::MouseScroll()
{
	return (int)inputEvent.mouseWheelScroll.delta;
}

sf::Vector2f xe::InputSystem::MouseDelta() //* xe:Vector2 -> sf::Vector2f
{ 
	sf::Vector2f delta = { MousePosition().x - mousePosPrev.x, MousePosition().y - mousePosPrev.y }; //* xe:Vector2 -> sf::Vector2f
	mousePosPrev = MousePosition();
	return delta;
}

sf::Vector2f xe::InputSystem::MousePosition() //* xe:Vector2 -> sf::Vector2f
{
	//return sf::Vector2f((float)sf::Mouse::getPosition(*Engine::GetWindow()->UnWrap()).x, (float)sf::Mouse::getPosition(*Engine::GetWindow()->UnWrap()).y);
	std::cout << "INCOMPATIBLE FUNCTION: MousePosition" << std::endl; //* removed implementation for Engine reference
	return sf::Vector2f();
}

float xe::InputSystem::GetMouseSensitivity()
{
	return mouseSensitivity;
}

void xe::InputSystem::SetMouseSensitivity(const float newSensitivity)
{
	mouseSensitivity = newSensitivity;
}

void xe::InputSystem::Typing(std::string& out_str)
{
	if (KeyEvent(Key::Backspace) == Pressed && out_str.size() > 0)
	{
		out_str.pop_back();
		return;
	}

	if (KeyEvent(Key::Enter) == Pressed)
	{
		out_str.push_back('\n');
		return;
	}

	char c = 0;
	if (KeyEvent(Key::A) == Pressed) c = 'a';
	else if (KeyEvent(Key::B) == Pressed) c = 'b';
	else if (KeyEvent(Key::C) == Pressed) c = 'c';
	else if (KeyEvent(Key::D) == Pressed) c = 'd';
	else if (KeyEvent(Key::E) == Pressed) c = 'e';
	else if (KeyEvent(Key::F) == Pressed) c = 'f';
	else if (KeyEvent(Key::G) == Pressed) c = 'g';
	else if (KeyEvent(Key::H) == Pressed) c = 'h';
	else if (KeyEvent(Key::I) == Pressed) c = 'i';
	else if (KeyEvent(Key::J) == Pressed) c = 'j';
	else if (KeyEvent(Key::K) == Pressed) c = 'k';
	else if (KeyEvent(Key::L) == Pressed) c = 'l';
	else if (KeyEvent(Key::M) == Pressed) c = 'm';
	else if (KeyEvent(Key::N) == Pressed) c = 'n';
	else if (KeyEvent(Key::O) == Pressed) c = 'o';
	else if (KeyEvent(Key::P) == Pressed) c = 'p';
	else if (KeyEvent(Key::Q) == Pressed) c = 'q';
	else if (KeyEvent(Key::R) == Pressed) c = 'r';
	else if (KeyEvent(Key::S) == Pressed) c = 's';
	else if (KeyEvent(Key::T) == Pressed) c = 't';
	else if (KeyEvent(Key::U) == Pressed) c = 'u';
	else if (KeyEvent(Key::V) == Pressed) c = 'v';
	else if (KeyEvent(Key::W) == Pressed) c = 'w';
	else if (KeyEvent(Key::X) == Pressed) c = 'x';
	else if (KeyEvent(Key::Y) == Pressed) c = 'y';
	else if (KeyEvent(Key::Z) == Pressed) c = 'z';

	if (c != 0 && (KeyHold(Key::LShift) || KeyHold(Key::RShift)))
	{
		c -= 32;
	}
	if (KeyEvent(Key::Space) == Pressed) c = ' ';

	if (c != 0) out_str.push_back(c);
}
