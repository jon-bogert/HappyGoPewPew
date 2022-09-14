#pragma once
class Button;
class Background;
class InstructionsScreen
{
	GameState _gameState = GameState::MainMenu;

	Button* _quitButton = nullptr;

	Background* _bg = nullptr;

	sf::Sprite _instr;

public:
	static InstructionsScreen& Get();
private:
	InstructionsScreen();
public:
	virtual ~InstructionsScreen();
	InstructionsScreen(const InstructionsScreen& other) = delete;
	InstructionsScreen& operator=(const InstructionsScreen& other) = delete;

	void Start();
	GameState Update(const float& deltaTime);
	void Draw();
	void OnDestroy();
};
