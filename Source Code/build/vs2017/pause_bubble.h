#pragma once
#include "game_object.h"
//Pause Bubble
class PauseBubble: public GameObject
{
public:
	//Initialise
	void Init(PrimitiveBuilder* primitive_builder_, b2World* world, b2Vec2 position);
	//Update
	void Update(float dt);
};

