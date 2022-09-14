#pragma once
#include "GameObject.h"

class DoorKey : public GameObject
{
	sf::Sprite _sprite;

public:
	DoorKey();

	void Start() override;
	void Update(const float& deltaTime) override;
	void Draw() override;
	void OnDestroy() override;
};

