#include "Pch.h"
#include "Background.h"
#include "AssetManager.h"
#include "Window.h"

void Background::Start()
{
	SetupSprite("background", _sprite);
	transform.position = { Window::WidthInUnits() * 0.5f, Window::HeightInUnits() * 0.5f };
	_initPosition = transform.position;
}

void Background::Update(const float& deltaTime)
{
}

void Background::Draw()
{
	Window::Draw(_sprite, transform);
}

void Background::OnDestroy()
{
}

void Background::AddOffset(sf::Vector2f offset)
{
	transform.position += offset;

	//Looping effect
	if (transform.position.x - _initPosition.x <= -8)
	{
		transform.position.x -= 8;
		_initPosition.x -= 16;

	}
	else if (transform.position.x - _initPosition.x >= 8)
	{
		transform.position.x += 8;
		_initPosition.x += 16;
	}

	if (transform.position.y - _initPosition.y <= -4)
	{
		transform.position.y -= 8;
		_initPosition.y -= 16;

	}
	else if (transform.position.y - _initPosition.y >= 4)
	{
		transform.position.y += 8;
		_initPosition.y += 16;
	}
}
