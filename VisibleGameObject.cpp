#include "stdafx.h"
#include "VisibleGameObject.h"

VisibleGameObject:: VisibleGameObject() {
	isLoaded = false;
}

VisibleGameObject::~VisibleGameObject() {

}

float VisibleGameObject::GetHeight() const {
	return sprite.getScale().y;
}

float VisibleGameObject::GetWidth() const {
	return sprite.getScale().x;
}

sf::Rect<float> VisibleGameObject::GetBoundingRect() const {
	sf::Vector2f size = sprite.getScale();
	sf::Vector2f position = sprite.getPosition();

	return sf::Rect<float>(position.x - size.x / 2, position.y - size.y / 2, position.x + size.x / 2, position.y + size.y / 2);
}

void VisibleGameObject::Load(std::string filename) {
	if (image.loadFromFile(filename) == false) {
		fileName = "";
		isLoaded = false;
	}
	else {
		fileName = filename;
		sprite.setTexture(image);
		isLoaded = true;
	}
}

void VisibleGameObject::Draw(sf::RenderWindow & renderWindow) {
	if (isLoaded) {
		renderWindow.draw(sprite);
	}
}

void VisibleGameObject::Update(sf::Time elapsedTime) {

}

void VisibleGameObject::SetPosition(float x, float y) {
	if (isLoaded) {
		sprite.setPosition(x, y);
	}
}

sf:: Vector2f VisibleGameObject :: GetPosition() const {
if (isLoaded) {
	return sprite.getPosition();
}
return sf::Vector2f();
}

sf:: Sprite& VisibleGameObject:: GetSprite() {
	return sprite;
}

bool VisibleGameObject::IsLoaded() const {
	return isLoaded;
}