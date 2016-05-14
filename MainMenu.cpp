#include "stdafx.h"
#include "MainMenu.h"

using namespace std;

MainMenu::MenuResult MainMenu :: Show(sf:: RenderWindow& window) {
	
	//Load menu Image from file
	sf::Texture image;
	image.loadFromFile("images/Mainmenu.png");
	sf:: Sprite sprite(image);

	//Setup clickable regions

	//Playmenu item coordinates
	MenuItem playButton;
	playButton.rect.top = 145;
	playButton.rect.height = 380-145;
	playButton.rect.left = 0;
	playButton.rect.width = 1023;
	playButton.action = Play;

	//Exitmenu item coordinates
	MenuItem exitButton;
	exitButton.rect.top = 383;
	exitButton.rect.height = 560-383;
	exitButton.rect.left = 0;
	exitButton.rect.width = 1023;
	exitButton.action = Exit;

	menuItems.push_back(playButton);
	menuItems.push_back(exitButton);

	window.draw(sprite);
	window.display();

	return GetMenuResponse(window);
}
// Reads where the button is and checks if a click is registered within that range
MainMenu::MenuResult MainMenu:: HandleClick(int x, int y) {
	std::list<MenuItem>::iterator it;

	for (it = menuItems.begin(); it != menuItems.end(); it++) {
		sf::Rect<int> menuItemRect = (*it).rect;
		if (y<menuItemRect.top+menuItemRect.height &&
			y>menuItemRect.top   &&
			x>menuItemRect.left &&
			x<menuItemRect.left+menuItemRect.width) {
			return(*it).action;
		}
	}
	return Nothing;
}
// Uses handle click in order to send the action to the game class
MainMenu::MenuResult MainMenu::GetMenuResponse(sf::RenderWindow& window) {
	sf::Event menuEvent;

	while (true) {
		while (window.pollEvent(menuEvent)) {
			if (menuEvent.type == sf::Event::MouseButtonPressed) {
				return HandleClick(menuEvent.mouseButton.x,menuEvent.mouseButton.y);
			}
			if (menuEvent.type == sf::Event::Closed) {
				return Exit;
			}
		}
	}
}