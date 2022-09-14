#include "Pch.h"
#include "Player.h"
#include "Window.h"
#include "BulletPool.h"
#include "Collision.h"
#include "Game.h"
#include "TileMap.h"
#include "AssetManager.h"
#include "Background.h"

using namespace xe;

Player::Player()
{
	_tag = "player";
	SetupSprite("player", _sprite);
	SetupSprite("crosshair", _crosshair);
	SetupSprite("heart", _heart);
	SetupSprite("spritesheet", _key, 32, 32);
	_key.setTextureRect(sf::IntRect(32 * 4, 0, 32, 32));

	_health = _maxHealth;
	_keyCount = 0;

	for (int i = 0; i < _health; i++)
		_hearts.push_back(_heart);

	_jumpSound.setBuffer(*AssetManager::Get().GetSound("jump"));
	_shotSound.setBuffer(*AssetManager::Get().GetSound("shotPlayer"));
	_hitSound.setBuffer(*AssetManager::Get().GetSound("playerHit"));
	_keySound.setBuffer(*AssetManager::Get().GetSound("key"));

}

void Player::Start()
{
	transform.position = { 5, 5 };
	_destination = transform.position;
	_dimensions = { 0.5f, 0.5f };
}

void Player::Update(const float& deltaTime)
{
	_mouseTransform.position = (sf::Vector2f)sf::Mouse::getPosition(*Window::UnWrap());
	_mouseTransform.position.x = (_mouseTransform.position.x / Window::GetPixelsPerUnit() / Window::GetScale()) + Window::GetCameraPosition().x;
	_mouseTransform.position.y = ((Window::GetResolution().y - _mouseTransform.position.y) / Window::GetPixelsPerUnit() / Window::GetScale()) + Window::GetCameraPosition().y;

	float moveInput = InputSystem::KeyAxis1D(Key::D, Key::A, deltaTime);
	_destination.x = transform.position.x + moveInput * _moveSpeed * deltaTime;


	if (InputSystem::KeyEvent(Key::Space) == Pressed && _canJump)
	{
		_yVelocity = _jumpVelocity;
		_jumpSound.play();
	}
	else
		_yVelocity += _gravity * deltaTime;
	_destination.y = transform.position.y + _yVelocity * deltaTime;

	if (fabs(_yVelocity) > 1.f)
		_canJump = false;

	Shoot();
}

void Player::Draw()
{
	Window::Draw(_sprite, transform);
	Window::Draw(_crosshair, _mouseTransform);

	Transform hudTrans;
	hudTrans.scale = { 3, 3 };
	hudTrans.position = { Window::WidthInUnits() - 1, Window::HeightInUnits() - 1 };
	for (sf::Sprite heart : _hearts)
	{
		Window::DrawHUD(heart, hudTrans);
		hudTrans.position.x -= 1;
	}
	hudTrans.scale = { 1, 1 };

	hudTrans.position = { Window::WidthInUnits() - 1, Window::HeightInUnits() - 2 };
	for (sf::Sprite key : _keys)
	{
		Window::DrawHUD(key, hudTrans);
		hudTrans.position.x -= 1;
	}
}

void Player::OnDestroy()
{
	_hearts.clear();
	_keys.clear();
}

sf::Vector2f Player::GetDestination() const
{
	return _destination;
}

void Player::OnCollision(GameObject* other)
{
	if (other->GetTag() == "tile" &&
		(other->transform.position.y <= transform.position.y - (_dimensions.y * 0.5f) - (other->GetDimensions().y * 0.5f)))
	{
		_yVelocity = 0.f;
		_canJump = true;
	}
	else if (other->GetTag() == "tile" &&
		(other->transform.position.y >= transform.position.y + (_dimensions.y * 0.5f) + (other->GetDimensions().y * 0.5f)))
		_yVelocity = 0.f;
	else if (other->GetTag() == "enemy-bullet")
	{
		if (--_health <= 0)
		{
			Game::Get().SetGameState(GameState::Lose);
		}
		_hearts.pop_back();
		_hitSound.play();
	}
}

void Player::ConfirmDestination(sf::Vector2f dest)
{
	sf::Vector2i mapDim = { Game::Get().GetWorldRef()->GetWidth(), Game::Get().GetWorldRef()->GetHeight() };
	sf::Vector2f offset{};

	if (dest.x > ((Window::WidthInUnits() / 5) * 3) + Window::GetCameraPosition().x &&
		Window::GetCameraPosition().x < mapDim.x - Window::WidthInUnits())
		offset.x += dest.x - transform.position.x;
	else if (dest.x < ((Window::WidthInUnits() / 5) * 2) + Window::GetCameraPosition().x &&
		Window::GetCameraPosition().x > 0.f)
		offset.x += dest.x - transform.position.x;


	if (dest.y > (Window::HeightInUnits() / 2) + Window::GetCameraPosition().y &&
		Window::GetCameraPosition().y < mapDim.y - Window::HeightInUnits())
		offset.y += dest.y - transform.position.y;
	else if (dest.y < (Window::HeightInUnits() / 2) + Window::GetCameraPosition().y &&
		Window::GetCameraPosition().y > 0.f)
	{
		offset.y += dest.y - transform.position.y;
	}
	Window::AddCameraPosition(offset);
	Game::Get().GetWorldRef()->GetBackground()->AddOffset({ offset.x * 0.5f, offset.y * 0.5f });

	transform.position = dest;
}

void Player::Shoot()
{
	if (InputSystem::MouseEvent(Mouse::Left) == Pressed)
	{
		_shotSound.play();
		Transform bulletTrans;
		bulletTrans.position = transform.position;
		bulletTrans.rotation.SetRad(atan2f(_mouseTransform.position.y - transform.position.y, _mouseTransform.position.x - transform.position.x));
		BulletPool::Get().ActivateNext(bulletTrans, "player");
	}
}

void Player::AddKeyCount()
{
	_keySound.play();
	_keyCount++;
	_keys.push_back(_key);
	if (_hearts.size() < _maxHealth)
	{
		_hearts.push_back(_heart);
		_health++;
	}
}

int Player::GetKeyCount()
{
	return _keyCount;
}
