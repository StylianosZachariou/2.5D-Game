#pragma once
#include "enemy.h"
//Monsta Enemy Class
class Monsta: public Enemy
{
public:
	Monsta();
	//Update
	void Update(float dt,float maxY, float minY);

	//Velocity
	gef::Vector2 velocity = { 300,300 };
};

