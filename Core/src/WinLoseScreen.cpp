#include "Pch.h"
#include "WinLoseScreen.h"
#include "Button.h"
#include "Window.h"
#include "GameObject.h"
#include "Background.h"
#include "AssetManager.h"

WinLoseScreen& WinLoseScreen::Get()
{
	static WinLoseScreen instance;
	return instance;
}

WinLoseScreen::WinLoseScreen()
{
}

WinLoseScreen::~WinLoseScreen()
{
}

void WinLoseScreen::Start(bool hasWon)
{
	_bg = new Background();
	_title.setFont(*AssetManager::GetFont("default"));

	if (hasWon)
	{
		_gameState = GameState::Win;

		_title.setString("You Escaped!");
		_forwardButton = new Button("Next Level", 5, 1);
		_backButton = new Button("Main Menu", 5, 1);
	}
	else
	{
		_gameState = GameState::Lose;

		_title.setString("You Died!");
		_forwardButton = new Button("Retry Level", 5, 1);
		_backButton = new Button("Main Menu", 5, 1);
	}
	_title.setCharacterSize(72);
	_title.setScale(Window::GetScale(), Window::GetScale());
	_title.setOrigin(_title.getLocalBounds().width * 0.5f, _title.getLocalBounds().height * 0.5f);
	_titleTransform.position = { Window::WidthInUnits() * 0.5f, 15 };


	_forwardButton->transform.position = { Window::WidthInUnits() * 0.5f + 5, 6 };
	_backButton->transform.position = { Window::WidthInUnits() * 0.5f - 5, 6 };

	_bg->Start();
	_forwardButton->Start();
	_backButton->Start();
}

GameState WinLoseScreen::Update(const float& deltaTime)
{
	_forwardButton->Update(deltaTime);
	_backButton->Update(deltaTime);

	if (_forwardButton->GetPressEvent())
		_gameState = GameState::Game;
	if (_backButton->GetPressEvent())
		_gameState = GameState::MainMenu;

	return _gameState;
}

void WinLoseScreen::Draw()
{
	_bg->Draw();
	Window::Draw(_title, _titleTransform);
	_forwardButton->Draw();
	_backButton->Draw();
}

void WinLoseScreen::OnDestroy()
{
	_bg->OnDestroy();
	_forwardButton->OnDestroy();
	_backButton->OnDestroy();

	delete _bg;
	delete _forwardButton;
	delete _backButton;

	_bg = nullptr;
	_forwardButton = nullptr;
	_backButton = nullptr;
}
