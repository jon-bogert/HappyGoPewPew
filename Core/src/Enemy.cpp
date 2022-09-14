#include "Pch.h"
#include "Enemy.h"
#include "Window.h"
#include "BulletPool.h"
#include "Player.h"
#include "Game.h"
#include "AssetManager.h"

Enemy::Enemy()
{
}

void Enemy::Start()
{
	_tag = "enemy";
	SetupSprite("spritesheet", _sprite, 32, 32);
	_dimensions = { 0.5f, 0.5f };
	_sprite.setTextureRect(sf::IntRect(5 * 32, 0, 32, 32));
	_shotClock.restart();
	_shotTime = (rand() % (int)((_shotTimeMax - _shotTimeMin) * 4) * 0.25f + 0.5f);


	_shotSound.setBuffer(*AssetManager::Get().GetSound("shotEnemy"));
}

void Enemy::Update(const float& deltaTime)
{
	if (_isActive)
	{
		sf::Vector2f displacement = { Game::Get().GetPlayerRef()->transform.position.x - transform.position.x, Game::Get().GetPlayerRef()->transform.position.y - transform.position.y };
		if (_shotClock.getElapsedTime().asSeconds() >= _shotTime && sqrtf(powf(displacement.x, 2) + powf(displacement.y, 2)) < _range)
		{
			_shotClock.restart();
			_shotSound.play();
			_shotTime = (rand() % (int)((_shotTimeMax - _shotTimeMin) * 4) * 0.25f + 0.5f);
			Transform bulletTrans = transform;
			bulletTrans.rotation.SetRad(atan2f(displacement.y, displacement.x));
			BulletPool::Get().ActivateNext(bulletTrans, "enemy");
		}
	}
}

void Enemy::Draw()
{
	if (_isActive)
	{
		Window::Draw(_sprite, transform);
	}
}

void Enemy::OnDestroy()
{
}

void Enemy::OnCollision(GameObject* other)
{
	if (other->GetTag() == "player-bullet")
	{
		if (--_health <= 0)
		{
			Deactivate();
		}
	}
}

void Enemy::Deactivate()
{
	_isActive = false;
}
