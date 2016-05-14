#pragma once
#include "VisibleGameObject.h"

class GameBall :
	public VisibleGameObject {
public:
	GameBall();
	virtual ~GameBall();
	void Update(sf::Time elapsedTime);
	
private: float velocity;
		 float angle;
		 float elapsedTimeSinceStart;

		 float LinearVelocityX(float angle);
		 float LinearVelocityY(float angle);
};