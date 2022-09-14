#include "Pch.h"
#include "Bullet.h"
#include "Game.h"
#include "AssetManager.h"
#include "Window.h"
#include "Tile.h"
#include "TileMap.h"
#include "Collision.h"
#include "Enemy.h"
#include "Player.h"

void Bullet::Start()
{
	_isActive = false;
	_dimensions = { 0.1f, 0.1f };
	_tag = "player-bullet";
	SetupSprite("bullet", sprite);
}

void Bullet::Update(const float& deltaTime)
{
	if (_isActive)
	{
		transform.position = {transform.position.x + (_forward.x * bulletSpeed * deltaTime), transform.position.y + (_forward.y * bulletSpeed * deltaTime)};
		for (Tile* tile : Game::Get().GetWorldRef()->GetMap())
			Collision::Check(*this, *tile);
		for (Enemy* enemy : Game::Get().GetWorldRef()->GetEnemies())
			Collision::Check(*this, *enemy);

		Collision::Check(*this, *Game::Get().GetPlayerRef());

		_life -= deltaTime;
		if (_life <= 0.f)
			Deactivate();
	}
}

void Bullet::Draw()
{
	if (_isActive)
	{
		Window::Draw(sprite, transform);
	}
}

void Bullet::OnDestroy()
{
}

void Bullet::OnCollision(GameObject* other)
{
	if (other->GetTag() == "tile")
		Deactivate();
	else if (_tag == "player-bullet" && other->GetTag() == "enemy")
		Deactivate();
	else if (_tag == "enemy-bullet" && other->GetTag() == "player")
		Deactivate();
}

void Bullet::Activate(Transform transform_, std::string owner)
{
	transform.position = transform_.position;
	_isActive = true;
	_forward = {cosf(transform_.rotation.GetRad()), sinf(transform_.rotation.GetRad())};
	owner.append("-bullet");
	_tag = owner;
	_life = _lifeSpan;
}

void Bullet::Deactivate()
{
	_isActive = false;
	_life = 0.f;
}
