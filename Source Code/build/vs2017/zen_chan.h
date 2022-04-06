#pragma once
#include "enemy.h"
//Zen Chan Enemy Class
class ZenChan: public Enemy
{
public:
	ZenChan();
	//Update
	void Update(float dt, float maxY,float minY);

	//Velocity
	float velocity = 300;
};

