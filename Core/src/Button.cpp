#include "Pch.h"
#include "Button.h"
#include "Window.h"
#include "AssetManager.h"

Button::Button(std::string text, int width, int height)
	: _width(width)
	, _height(height)
{
	_text.setString(text);
}

void Button::Start()
{
	_plate.setSize({ _width * Window::GetPixelsPerUnit(), _height * Window::GetPixelsPerUnit() });
	_plate.setScale({ Window::GetScale(), Window::GetScale() });
	_plate.setOrigin({ _plate.getLocalBounds().width * 0.5f, _plate.getLocalBounds().height * 0.5f });
	_plate.setFillColor(_inactiveColor);

	_text.setFont(*AssetManager::GetFont("default"));
	_text.setCharacterSize(_fontSize);
	_text.setScale(Window::GetScale(), Window::GetScale());
	_text.setFillColor({255, 255, 255, 255});
	_text.setOrigin({ _text.getLocalBounds().width * 0.5f, _text.getLocalBounds().height * 0.5f});

	_hoverSound.setBuffer(*AssetManager::Get().GetSound("menuHover"));
	_selectSound.setBuffer(*AssetManager::Get().GetSound("menuSelect"));
}

void Button::Update(const float& deltaTime)
{
	if (CheckHover())
	{
		_plate.setFillColor(_activeColor);
		if (!_hoverTrigger)_hoverSound.play();
		_hoverTrigger = true;
	}
	else
	{
		_plate.setFillColor(_inactiveColor);
		_hoverTrigger = false;
	}
}

void Button::Draw()
{
	Window::Draw(_plate, transform);
	Window::Draw(_text, transform);
}

void Button::OnDestroy()
{
}

bool Button::GetPressEvent()
{
	if (CheckHover() && xe::InputSystem::MouseEvent(xe::Mouse::Left) == xe::Pressed)
	{
		_selectSound.play();
		sf::Clock soundTimer;
		while (soundTimer.getElapsedTime().asSeconds() < 0.1f) {}
		return true;
	}
	return false;
}

bool Button::CheckHover()
{
	sf::Vector2f mousePosition = (sf::Vector2f)sf::Mouse::getPosition(*Window::UnWrap());
	mousePosition.x = (mousePosition.x / Window::GetPixelsPerUnit() / Window::GetScale()) + Window::GetCameraPosition().x;
	mousePosition.y = ((Window::GetResolution().y - mousePosition.y) / Window::GetPixelsPerUnit() / Window::GetScale()) + Window::GetCameraPosition().y;

	return (mousePosition.x < transform.position.x + (_width * 0.5f) &&
		mousePosition.x > transform.position.x - (_width * 0.5f) &&
		mousePosition.y < transform.position.y + (_height * 0.5f) &&
		mousePosition.y > transform.position.y - (_height * 0.5f));
}
