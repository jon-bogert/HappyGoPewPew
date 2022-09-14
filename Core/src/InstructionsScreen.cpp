#include "Pch.h"
#include "InstructionsScreen.h"
#include "Button.h"
#include "Window.h"
#include "GameObject.h"
#include "Background.h"
#include "AssetManager.h"

InstructionsScreen& InstructionsScreen::Get()
{
	static InstructionsScreen instance;
	return instance;
}

InstructionsScreen::InstructionsScreen()
{
}

InstructionsScreen::~InstructionsScreen()
{
}

void InstructionsScreen::Start()
{
	_gameState = GameState::Instructions;

	_bg = new Background();
	_instr.setTexture(*AssetManager::GetTexture("instructions"));
	_instr.setScale(Window::GetResolution().x / _instr.getLocalBounds().width, Window::GetResolution().y / _instr.getLocalBounds().height);

	_quitButton = new Button("Back to Main Menu", 7, 1);
	_quitButton->transform.position = { Window::WidthInUnits() * 0.5f, 3 };

	_bg->Start();
	_quitButton->Start();
}

GameState InstructionsScreen::Update(const float& deltaTime)
{
	_quitButton->Update(deltaTime);

	if (_quitButton->GetPressEvent())
		_gameState = GameState::MainMenu;

	return _gameState;
}

void InstructionsScreen::Draw()
{
	_bg->Draw();
	_quitButton->Draw();
	Window::UnWrap()->draw(_instr);
}

void InstructionsScreen::OnDestroy()
{
	_bg->OnDestroy();
	_quitButton->OnDestroy();

	delete _bg;
	delete _quitButton;

	_bg = nullptr;
	_quitButton = nullptr;
}