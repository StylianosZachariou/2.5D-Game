#pragma once
#include "game_object.h"

//Bubble Class
class Bubble : public GameObject
{
public:
	//Initialise
	void Init(PrimitiveBuilder* primitive_builder_, b2World* world, b2Vec2 position, float player_sizeX, bool direction,int id);
	//Update
	void Update(float dt, float maxY, float minY);
	
	bool isFull = false;
	bool isEnabled = true;

	//Velocity
	float velocity= 500;
	//Bubble ID
	int personal_id = -1;
};

