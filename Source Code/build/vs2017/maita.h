#pragma once
#include "enemy.h"
//Maita Enemy
class Maita: public Enemy
{
public:
	Maita();
	//Update
	void Update(float dt,gef::Vector2 player_poisition, float maxY, float minY);
private:
	//Velocity
	float velocity = 50;
};

