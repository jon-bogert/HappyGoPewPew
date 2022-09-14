#include "Pch.h"
#include "Window.h"
#include "Game.h"
#include "AssetManager.h"
#include "MainMenu.h"
#include "WinLoseScreen.h"
#include "InstructionsScreen.h"

int WinMain()
{
    srand(time(NULL));
    GameState currentState = GameState::MainMenu;
    GameState nextState = currentState;
    
    AssetManager::Get();

    Window& window = Window::Get();
    MainMenu& mMenu = MainMenu::Get();
    Game& game = Game::Get();
    WinLoseScreen& wlScreen = WinLoseScreen::Get();
    InstructionsScreen& instrScreen = InstructionsScreen::Get();
    sf::Clock deltaTime;

    int level = 0;
    int levelMax = 3;

    while (window.GetIsOpen())
    {
        //START
        switch (currentState)
        {
        case GameState::MainMenu:
            mMenu.Start();
            break;
        case GameState::Game:
            game.Start(level);
            break;
        case GameState::Win:
            level = (level + 1) % levelMax; // increase level counter
            wlScreen.Start(true);
            break;
        case GameState::Lose:
            wlScreen.Start(false);
            break;
        case GameState::Instructions:
            instrScreen.Start();
            break;
        }

        deltaTime.restart();
        while (window.GetIsOpen() && currentState == nextState)
        {
            window.CloseEventLoop();

            //UPDATE
            switch (currentState)
            {
            case GameState::MainMenu:
                nextState = mMenu.Update(deltaTime.restart().asSeconds());
                break;
            case GameState::Game:
                nextState = game.Update(deltaTime.restart().asSeconds());
                break;
            case GameState::Win:
            case GameState::Lose:
                nextState = wlScreen.Update(deltaTime.restart().asSeconds());
                break;
            case GameState::Instructions:
                nextState = instrScreen.Update(deltaTime.restart().asSeconds());
                break;
            }
            
            //DRAW
            window.Clear();
            switch (currentState)
            {
            case GameState::MainMenu:
                mMenu.Draw();
                break;
            case GameState::Game:
                game.Draw();
                break;
            case GameState::Win:
            case GameState::Lose:
                wlScreen.Draw();
                break;
            case GameState::Instructions:
                instrScreen.Draw();
                break;
            }
            window.Display();
        }

        //ON_DESTROY
        switch (currentState)
        {
        case GameState::MainMenu:
            mMenu.OnDestroy();
            break;
        case GameState::Game:
            game.OnDestroy();
            break;
        case GameState::Win:
        case GameState::Lose:
            wlScreen.OnDestroy();
            break;
        case GameState::Instructions:
            instrScreen.OnDestroy();
            break;
        }
        currentState = nextState;
    }

	return 0;
}