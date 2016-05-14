#pragma once
#include "stdafx.h"
#include "VisibleGameObject.h"

class PlayerPaddle : public VisibleGameObject {
public:
	PlayerPaddle();
	~PlayerPaddle();

	void Update(sf::Time elapsedTime);
	void Draw(sf::RenderWindow& rw);

	float GetVelocity() const;

private:
	float velocity;
	float maxVelocity;
};

