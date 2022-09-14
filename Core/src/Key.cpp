#include "Pch.h"
#include "Key.h"
#include "Window.h"

DoorKey::DoorKey()
{
}

void DoorKey::Start()
{
	_tag = "key";
	SetupSprite("spritesheet", _sprite, 32, 32);
	_sprite.setTextureRect(sf::IntRect(4 * 32, 0, 32, 32));
}

void DoorKey::Update(const float& deltaTime)
{
}

void DoorKey::Draw()
{
	Window::Draw(_sprite, transform);
}

void DoorKey::OnDestroy()
{
}
