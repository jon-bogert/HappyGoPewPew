#pragma once

class Button;
class Background;
class MainMenu
{
	GameState _gameState = GameState::MainMenu;

	Button* _startButton = nullptr;
	Button* _quitButton = nullptr;
	Button* _instrButton = nullptr;

	Background* _bg = nullptr;

	sf::Text _title;
	Transform _titleTransform;

public:
	static MainMenu& Get();
private:
	MainMenu();
public:
	virtual ~MainMenu();
	MainMenu(const MainMenu& other) = delete;
	MainMenu& operator=(const MainMenu& other) = delete;

	void Start();
	GameState Update(const float& deltaTime);
	void Draw();
	void OnDestroy();
};