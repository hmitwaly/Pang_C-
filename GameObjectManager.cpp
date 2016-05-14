#include "stdafx.h"
#include "GameObjectManager.h"
#include "Game.h"

GameObjectManager::GameObjectManager() {

}
//Deallocates memory for every game object in the game object manager
GameObjectManager:: ~GameObjectManager() {
	std::for_each(gameObjects.begin(), gameObjects.end(), GameObjectDeallocator());
}
//Adds a game object using a key value pair 
void GameObjectManager::Add(std::string name, VisibleGameObject* gameObject) {
	gameObjects.insert(std::pair<std::string, VisibleGameObject*>(name, gameObject));
}
// Removes the game object also using a key value pair by erasing its data
void GameObjectManager::Remove(std::string name) {
	std::map<std::string, VisibleGameObject*>::iterator results = gameObjects.find(name);
	if (results != gameObjects.end()) {
		delete results->second;
		gameObjects.erase(results);
	}
}

VisibleGameObject* GameObjectManager::Get(std::string name) const {
std::map<std::string, VisibleGameObject*>::const_iterator results = gameObjects.find(name);
	if (results == gameObjects.end()) {
		return NULL;
	}
	return results->second;
}

int GameObjectManager::GameObjectCount() const {
	return gameObjects.size();
}
//Adds and removes gameObjects constantly depending on the calls
void GameObjectManager::UpdateAll() {
	std::map<std::string, VisibleGameObject*>::const_iterator itr = gameObjects.begin();
	
	static sf::Clock clock;
	sf::Time timeDelta = clock.restart();

	while (itr != gameObjects.end()) {
		itr->second->Update(timeDelta);
		itr++;
	}
}
//Draws all the game objects to the screen
void GameObjectManager::DrawAll(sf::RenderWindow& renderWindow) {
	std::map<std::string, VisibleGameObject*>::const_iterator itr = gameObjects.begin();
	while (itr != gameObjects.end()) {
		itr->second->Draw(renderWindow);
		itr++;
	}
}