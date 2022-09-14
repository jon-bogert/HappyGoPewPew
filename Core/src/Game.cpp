#include "Pch.h"
#include "Game.h"
#include "Player.h"
#include "BulletPool.h"
#include "TileMap.h"
#include "Collision.h"

#include "AssetManager.h"
#include "Window.h"

Game& Game::Get()
{
	static Game instance;
	return instance;
}

Game::Game()
{
}

Game::~Game()
{
}

void Game::Start(int level)
{
	_gameState = GameState::Game;
	//_fpsCounter.setFont(*AssetManager::GetFont("default"));
	//_fpsCounter.setCharacterSize(20);

	BulletPool::Get().Start();

	_world = new TileMap();
	_player = new Player();
	
	std::string levelPath = "assets/maps/level";
	levelPath.append(std::to_string(level) + ".map");
	_world->Load(levelPath);

	_world->Start();
	_player->Start();
	Window::SetCursorVis(false);
}

GameState Game::Update(const float& deltaTime)
{
	BulletPool::Get().Update(deltaTime);
	_world->Update(deltaTime);
	_player->Update(deltaTime);

	Collision::PlayerWorld(*_player, *_world);

	if (_player->transform.position.x > _world->GetWidth())
		_gameState = GameState::Win;

	if (xe::InputSystem::KeyEvent(xe::Key::Escape) == xe::Pressed)
		_gameState = GameState::MainMenu;

	return _gameState;
}

void Game::Draw()
{
	_world->Draw();
	BulletPool::Get().Draw();
	_player->Draw();

	//Window::UnWrap()->draw(_fpsCounter);
}

void Game::OnDestroy()
{
	Window::SetCameraPosition({ 0.f, 0.f });

	BulletPool::Get().OnDestroy();
	_world->OnDestroy();
	_player->OnDestroy();

	delete _world;
	_world = nullptr;
	delete _player;
	_player = nullptr;

	Window::SetCursorVis(true);
}

TileMap* Game::GetWorldRef()
{
	return _world;
}

Player* Game::GetPlayerRef()
{
	return _player;
}

GameState Game::GetGameState() const
{
	return _gameState;
}

void Game::SetGameState(const GameState& gameState)
{
	_gameState = gameState;
}
