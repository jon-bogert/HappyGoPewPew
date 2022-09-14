#pragma once
#include "GameObject.h"
class Bullet : public GameObject
{
	sf::Vector2f _forward{};
	float bulletSpeed = 50.f;

	sf::Sprite sprite;

	float _lifeSpan = 5.f;
	float _life = 0.f;

public:

	void Start() override;
	void Update(const float& deltaTime) override;
	void Draw() override;
	void OnDestroy() override;

	void OnCollision(GameObject* other) override;
	void Activate(Transform transform_, std::string owner);
	void Deactivate();
};

