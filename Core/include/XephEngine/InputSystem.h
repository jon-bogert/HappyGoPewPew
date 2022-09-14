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

#pragma once

//* Include directories do not rely on the rest of the engine
#include "SFML/System.hpp"
#include "SFML/Graphics.hpp"
#include "SFML/Window.hpp"

namespace xe
{
    enum Event {None, Pressed, Released};

	enum class Key // NOTE: Can Typecast to sf::Keyboard::Key
	{
        Unkwn = -1, 
        A = 0, B, C, D, E, F, G, H, I, J, K, L, M, N, O, P, Q, R, S, T, U, V, W, X, Y, Z,
        _0, _1, _2, _3, _4, _5, _6, _7, _8, _9,
        Escape, LCtrl, LShift, LAlt, LWin, RCtrl, RShift, RAlt, RWin,
        Menu, LBracket, RBracket, Semicolon, Comma, Period,  Quote,  ForwardSlash, Backslash,
        Tilde,  Equal,  Dash,  Space, Enter,  Backspace, Tab,
        PageUp,  PageDown, End, Home, Insert, Delete,
        NumAdd, NumMinus, NumMultiply, NumDivide,
        Left, Right, Up, Down,
        Num0, Num1, Num2, Num3, Num4, Num5, Num6, Num7, Num8, Num9,
        F1, F2, F3, F4, F5, F6, F7, F8, F9, F10, F11, F12, F13, F14, F15,
        Pause
	};
    enum class Mouse // NOTE Can Typecast sf::Mouse
    {
        Left, Right, Middle, Button4, Button5
    };
    enum class Button // NOTE does NOT Typecast
    {
        A, B, X, Y, LB, RB, Select, Start, LS_Press, RS_Press, LT, RT,
        LS_Up, LS_Down, LS_Left, LS_Right,
        RS_Up, RS_Down, RS_Left, RS_Right,
        DPad_Up, DPad_Down, DPad_Left, DPad_Right
    };
    enum class Axis
    {
        LS, RS, DPad, Trig
    };

	namespace InputSystem
	{
        //* Removed Update and CloseWindow Functions

        float KeyAxis1D(const Key pos, const Key neg, float daltaTime); //* Added independant deltaTime param
        sf::Vector2f KeyAxis2D(const Key posX, const Key negX, const Key posY, const Key negY, float deltaTime); //* xe::Vector2 -> sf::Vector2f / Added independant deltaTime param

		bool KeyHold(const Key key);
        Event KeyEvent(const Key key);

        sf::Vector2f GetAxis(int playerIndex, Axis axis); // For triggers-> X is LT, Y is RT (0.->1. only) //* xe::Vector2 -> sf::Vector2f
        bool ButtonHold(const int playerIndex, const Button button);
        Event ButtonEvent(const int playerIndex, const Button button);

        bool MouseHold(const Mouse mouseButton);
        Event MouseEvent(const Mouse mouseButton);
        int MouseScroll();
        sf::Vector2f MouseDelta(); //* xe::Vector2 -> sf::Vector2f
        sf::Vector2f MousePosition(); //* xe::Vector2 -> sf::Vector2f
        float GetMouseSensitivity();
        void SetMouseSensitivity(const float newSensitivity);

        void Typing(std::string& out_str);
	}
}

