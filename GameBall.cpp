#include "stdafx.h"
#include "GameBall.h"
#include "Game.h"

//Initilizes the balls velocity, image, position, and angle
GameBall::GameBall() :
	velocity(230.0f), elapsedTimeSinceStart(0.0f)
{
	Load("images/ball.png");
	assert(IsLoaded());

	GetSprite().setOrigin(15, 15);

	srand(std::clock());
	angle = (float)(0 + (rand() % 360));
}

GameBall::~GameBall() {

}

void GameBall::Update(sf::Time elapsedTime) {
	elapsedTimeSinceStart += elapsedTime.asSeconds();

	//Delay game from starting until 3 seconds have passed
	if (elapsedTimeSinceStart < 3.0f)
		return;

	float moveAmount = velocity*elapsedTime.asSeconds();

	float moveByX = LinearVelocityX(angle)*moveAmount;
	float moveByY = LinearVelocityY(angle)*moveAmount;

	//collide with the left side of the screen
	if (GetPosition().x + moveByX <= 0 + GetWidth() / 2 || GetPosition().x + GetHeight() / 2 + moveByX >= Game::SCREEN_WIDTH) {
		//Ricochet
		angle = 360.0f - angle;
		if (angle > 260.0f && angle < 280.0f) angle += 20.0f;
		if (angle > 80.0f && angle < 100.0f) angle += 20.0f;
		moveByX = -moveByX;
	}

	PlayerPaddle* player1 = dynamic_cast<PlayerPaddle*>(Game::GetGameObjectManager().Get("Paddle1"));
	if (player1 != NULL) {
		sf::Rect<float> p1BB = player1->GetBoundingRect();
		if (p1BB.intersects(GetBoundingRect())) {

			angle = 360.0f - (angle - 180.0f);
			if (angle > 360.0f) angle -= 360.0f;

			moveByY = -moveByY;

			//make sure ball isnt inside paddle
			if ((GetBoundingRect().top + GetBoundingRect().height) > player1->GetBoundingRect().top) {
				SetPosition(GetPosition().x, player1->GetBoundingRect().top - GetHeight() / 2 - 1);
			}

			//now add english based on the players velocity
			float playerVelocity = player1->GetVelocity();

			if (playerVelocity < 0) {
				//moving left
				angle -= 20.0f;
				if (angle < 0) angle = 360.0f + angle;
			}
			else if (playerVelocity>0) {
				angle += 20.0f;
				if (angle > 360.0f) angle = angle - 360.0f;
			}

			velocity += 5.0f;

		}


		if (GetPosition().y - GetHeight() / 2 <= 0) {
			angle = 180 - angle;
			moveByY = -moveByY;
		}

		if (GetPosition().y + GetHeight() / 2 + moveByY >= Game::SCREEN_HEIGHT) {
			//move to middle of the screen for now and randomize angle
			GetSprite().setPosition(Game::SCREEN_WIDTH / 2, Game::SCREEN_HEIGHT / 2);
			angle = (float)(0 + (rand() % 360));
			velocity = 220.0f;
			elapsedTimeSinceStart = 0.0f;
		}
		GetSprite().move(moveByX, moveByY);
	}
}
//Handles the math behind the bouncing of the ball
float GameBall::LinearVelocityX(float angle) {
	angle -= 90;
	if (angle < 0) angle = 360 + angle;
	return (float)std::cos(angle * 3.1415926 / 180.0f);
}

float GameBall::LinearVelocityY(float angle) {
	angle -= 90;
	if (angle < 0) angle = 360 + angle;
	return (float)std::sin(angle * 3.1415926 / 180.0f);
}