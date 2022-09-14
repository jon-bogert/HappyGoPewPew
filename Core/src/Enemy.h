#pragma once
#include "GameObject.h"

class Enemy : public GameObject
{
	sf::Sprite _sprite;
	sf::Clock _shotClock;

	float _shotTimeMin = 0.5f;
	float _shotTimeMax = 2.f;
	float _shotTime = 2.f;
	int _health = 7;
	float _range = 25.f;

	sf::Sound _shotSound;

public:
	Enemy();

	void Start() override;
	void Update(const float& deltaTime) override;
	void Draw() override;
	void OnDestroy() override;

	void OnCollision(GameObject* other) override;
	void Deactivate();
};

