#pragma once
#include "GameObject.h"
class Background : public GameObject
{
	sf::Vector2f _initPosition;

	sf::Sprite _sprite;

public:
	void Start() override;
	void Update(const float& deltaTime) override;
	void Draw() override;
	void OnDestroy() override;

	void AddOffset(sf::Vector2f offset);
};

