#pragma once
class Button;
class Background;
class WinLoseScreen
{
	GameState _gameState = GameState::MainMenu;

	Button* _forwardButton = nullptr;
	Button* _backButton = nullptr;

	Background* _bg = nullptr;

	sf::Text _title;
	Transform _titleTransform;

public:
	static WinLoseScreen& Get();
private:
	WinLoseScreen();
public:
	virtual ~WinLoseScreen();
	WinLoseScreen(const WinLoseScreen& other) = delete;
	WinLoseScreen& operator=(const WinLoseScreen& other) = delete;

	void Start(bool hasWon);
	GameState Update(const float& deltaTime);
	void Draw();
	void OnDestroy();
};

