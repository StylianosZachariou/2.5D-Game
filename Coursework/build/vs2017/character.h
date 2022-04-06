#pragma once
#include "game_object.h"
#include "animated_mesh.h"

//Character class, for player and enemies
class Character: public GameObject
{
public:
	//Initialise
	void Init(b2World* world, gef::Vector2 position, bool circle);
	//Direction
	bool lookRight = true;
	//Animation
	AnimatedMesh animation;
};

