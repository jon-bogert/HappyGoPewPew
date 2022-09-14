#pragma once

class Player;
class TileMap;
class Game
{
	Player* _player = nullptr;
	TileMap* _world = nullptr;

	//sf::Text _fpsCounter;
	GameState _gameState = GameState::Game;

public:
	static Game& Get();
private:
	Game();
public:
	virtual ~Game();
	Game(const Game& other) = delete;
	Game& operator=(const Game& other) = delete;

	void Start(int level);
	GameState Update(const float& deltaTime);
	void Draw();
	void OnDestroy();

	TileMap* GetWorldRef();
	Player* GetPlayerRef();

	GameState GetGameState() const;
	void SetGameState(const GameState& gameState);
};

