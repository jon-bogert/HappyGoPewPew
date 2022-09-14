#pragma once
#include "GameObject.h"

class Player : public GameObject
{
	sf::Sprite _sprite;
	sf::Sprite _crosshair;
	float _moveSpeed = 10;

	sf::Vector2f _destination{};

	Transform _mouseTransform;

	float _gravity = -50.f;
	float _yVelocity = 0.f;
	float _jumpVelocity = 25.f;

	bool _canJump = false;

	int _maxHealth = 5;
	int _health;
	int _keyCount = 0;

	sf::Sprite _heart;
	std::vector<sf::Sprite> _hearts;
	sf::Sprite _key;
	std::vector<sf::Sprite> _keys;

	sf::Sound _jumpSound;
	sf::Sound _shotSound;
	sf::Sound _hitSound;
	sf::Sound _keySound;

public:
	Player();

	void Start() override;
	void Update(const float& deltaTime) override;
	void Draw() override;
	void OnDestroy() override;

	void OnCollision(GameObject* other) override;

	sf::Vector2f GetDestination() const;

	void ConfirmDestination(sf::Vector2f dest);

	void AddKeyCount();
	int GetKeyCount();

private:
	void Shoot();
};

