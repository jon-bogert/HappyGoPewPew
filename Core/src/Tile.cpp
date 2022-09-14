#include "Pch.h"
#include "Tile.h"
#include "Window.h"

Tile::Tile(int id)
	: _id(id)
{
	_tag = "tile";
}

void Tile::Start()
{
	SetupSprite("spritesheet", _sprite, 32, 32);
	_sprite.setTextureRect(sf::IntRect(_id * 32, 0, 32, 32));
}

void Tile::Update(const float& deltaTime)
{
}

void Tile::Draw()
{
	Window::Draw(_sprite, transform);
}

void Tile::OnDestroy()
{
}

int Tile::GetID() const
{
	return _id;
}
