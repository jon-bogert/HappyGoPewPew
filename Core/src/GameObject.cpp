#include "Pch.h"
#include "GameObject.h"
#include "AssetManager.h"

GameObject::GameObject()
{

}
GameObject::~GameObject()
{

}

sf::Vector2f GameObject::GetDimensions() const
{
	return _dimensions;
}

void GameObject::SetDimensions(const sf::Vector2f dimensions)
{
	_dimensions = dimensions;
}

float GameObject::GetLeft() const
{
	return transform.position.x - (_dimensions.x * 0.5f * transform.scale.x);
}

float GameObject::GetTop() const
{
	return transform.position.y + (_dimensions.y * 0.5f * transform.scale.y);
}

float GameObject::GetRight() const
{
	return transform.position.x + (_dimensions.x * 0.5f * transform.scale.x);
}

float GameObject::GetBottom() const
{
	return transform.position.y - (_dimensions.y * 0.5f * transform.scale.y);
}

std::string GameObject::GetTag() const
{
	return _tag;
}

bool GameObject::GetIsActive() const
{
	return _isActive;
}


void GameObject::SetupSprite(std::string key, sf::Sprite& sprite)
{
	sprite.setTexture(*AssetManager::GetTexture(key));
	sprite.setOrigin(sprite.getLocalBounds().width * 0.5f, sprite.getLocalBounds().height * 0.5f);
}

void GameObject::SetupSprite(std::string key, sf::Sprite& sprite, int pixelWidth, int pixelHeight)
{
	sprite.setTexture(*AssetManager::GetTexture(key));
	sprite.setOrigin(pixelWidth * 0.5f, pixelHeight * 0.5f);
}
