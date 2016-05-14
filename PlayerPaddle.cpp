#include "stdafx.h"
#include "PlayerPaddle.h"
#include "Game.h"

PlayerPaddle::PlayerPaddle() : velocity(0), maxVelocity(600.0f){
	Load("images/paddle.png");
	assert(IsLoaded());

	GetSprite().setOrigin(GetSprite().getScale().x / 2, GetSprite().getScale().y / 2);

}

PlayerPaddle::~PlayerPaddle() {

}

void PlayerPaddle::Draw(sf::RenderWindow & rw) {
	VisibleGameObject::Draw(rw);
}

float PlayerPaddle::GetVelocity() const {
	return velocity;
}

void PlayerPaddle::Update(sf::Time elapsedTime) {
	sf::Keyboard keys;
	if (keys.isKeyPressed(sf::Keyboard::Left)) {
		velocity -= 30.0f;
	} else if (keys.isKeyPressed(sf::Keyboard::Right)) {
		velocity += 30.0f;
	} else {
		velocity = 0.0f;
	}

	if (velocity > maxVelocity) {
		velocity = maxVelocity;
	}
	if (velocity < -maxVelocity) {
		velocity = -maxVelocity;
	}

	sf::Vector2f pos = this->GetPosition();

	if ((pos.x+50 < GetSprite().getLocalBounds().width/ 2 && velocity<0) || (pos.x > Game::SCREEN_WIDTH - GetSprite().getLocalBounds().width / 2 && velocity >0)) {
		velocity = -velocity;
	}

	GetSprite().move(velocity*elapsedTime.asSeconds(), 0);
}
