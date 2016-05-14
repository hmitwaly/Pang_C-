#include "stdafx.h"
#include "Game.h"
#include "MainMenu.h"
#include "SplashScreen.h"
#include "GameBall.h"
#include "SFMLSoundProvider.h"
#include "ServiceLocator.h"
	
	// Runs when the game is started from the pang file
	void Game::Start(void) {
		if (gameState != Uninitialized)
			return;
		//Creates the window for the game
		mainWindow.create(sf::VideoMode(1024, 768, 32), "Pang!");
		//Initializes the sound provider
		SFMLSoundProvider soundProvider;
		ServiceLocator::RegisterServiceLocator(&soundProvider);
		//Initializes player object and its position
		PlayerPaddle *player1 = new PlayerPaddle();
		player1->SetPosition(SCREEN_WIDTH/2, 700);
		//Initializes ball object and its position
		GameBall *ball = new GameBall();
		ball->SetPosition((SCREEN_WIDTH / 2), (SCREEN_HEIGHT / 2) - 15);
		//Adds objects to the object manager
		gameObjectManager.Add("Paddle1", player1);
		gameObjectManager.Add("Ball", ball);
		//Initializes the first state of the same
		gameState = Game::ShowingSplash;
		//Starts the game loop
		while (!IsExiting()) {
			GameLoop();
		}
		mainWindow.close();
	}
	const GameObjectManager& Game::GetGameObjectManager()
	{
		return Game::gameObjectManager;
	}
	bool Game::IsExiting() {
		if (gameState == Game::Exiting)
			return true;
		else
			return false;
	}

	//This method is constantly checking for game state changes and updating the screen and key events
	void Game::GameLoop() {
		sf::Event currentEvent;
		mainWindow.pollEvent(currentEvent);

			switch (gameState) {
			case Game::ShowingMenu:
				ShowMenu();
				break;
			case Game::ShowingSplash: 
				ShowSplashScreen();
				break;
			case Game::Playing:
					mainWindow.clear(sf::Color(0, 0, 0));
					
					gameObjectManager.UpdateAll();
					gameObjectManager.DrawAll(mainWindow);

					mainWindow.display();

					if (currentEvent.type == sf::Event::Closed) {
						gameState = Game::Exiting;
					}
					if (currentEvent.type == sf::Event::KeyPressed) {
						if (currentEvent.key.code == sf::Keyboard::Escape) {
							ShowMenu();
						}
					}
					break;
				}
		}
	// Uses the splash screen object and puts it on the screen
	void Game::ShowSplashScreen() {
		SplashScreen splashScreen;
		splashScreen.Show(mainWindow);
		gameState = Game::ShowingMenu;
	}
	//Uses the main menu object and puts it on the screen, also changes states when applicable
	void Game::ShowMenu() {
		MainMenu mainMenu;
		MainMenu::MenuResult result = mainMenu.Show(mainWindow);
		switch (result) {
		case MainMenu::Exit:
			gameState = Game::Exiting;
			break;
		case MainMenu::Play:
			gameState = Game::Playing;
			break;
		}
	}

	Game:: GameState Game::gameState = Uninitialized;
	sf::RenderWindow Game::mainWindow;
	GameObjectManager Game::gameObjectManager;