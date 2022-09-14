#include "Pch.h"
#include "MainMenu.h"
#include "Button.h"
#include "Window.h"
#include "GameObject.h"
#include "Background.h"
#include "AssetManager.h"

MainMenu& MainMenu::Get()
{
	static MainMenu instance;
	return instance;
}

MainMenu::MainMenu()
{
}

MainMenu::~MainMenu()
{
}

void MainMenu::Start()
{
	_gameState = GameState::MainMenu;

	_bg = new Background();

	_title.setFont(*AssetManager::GetFont("default"));
	_title.setString("Happy Go Pew-Pew");
	_title.setCharacterSize(72);
	_title.setScale(Window::GetScale(), Window::GetScale());
	_title.setOrigin(_title.getLocalBounds().width * 0.5f, _title.getLocalBounds().height * 0.5f);
	_titleTransform.position = { Window::WidthInUnits() * 0.5f, 15 };

	_startButton = new Button("Start Game", 5, 1);
	_startButton->transform.position = { Window::WidthInUnits() * 0.5f, 7};

	_instrButton = new Button("Instructions", 6, 1);
	_instrButton->transform.position = { Window::WidthInUnits() * 0.5f, 5.5f };

	_quitButton = new Button("Quit to Desktop", 7, 1);
	_quitButton->transform.position = { Window::WidthInUnits() * 0.5f, 4 };

	_bg->Start();
	_startButton->Start();
	_instrButton->Start();
	_quitButton->Start();
}

GameState MainMenu::Update(const float& deltaTime)
{
	_startButton->Update(deltaTime);
	_instrButton->Update(deltaTime);
	_quitButton->Update(deltaTime);

	if (_startButton->GetPressEvent())
		_gameState = GameState::Game;
	if (_instrButton->GetPressEvent())
		_gameState = GameState::Instructions;
	if (_quitButton->GetPressEvent())
		Window::Close();

	return _gameState;
}

void MainMenu::Draw()
{
	_bg->Draw();
	Window::Draw(_title, _titleTransform);
	_startButton->Draw();
	_instrButton->Draw();
	_quitButton->Draw();
}

void MainMenu::OnDestroy()
{
	_bg->OnDestroy();
	_startButton->OnDestroy();
	_instrButton->OnDestroy();
	_quitButton->OnDestroy();

	delete _bg;
	delete _startButton;
	delete _instrButton;
	delete _quitButton;

	_bg = nullptr;
	_startButton = nullptr;
	_instrButton = nullptr;
	_quitButton = nullptr;
}
