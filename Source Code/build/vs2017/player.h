#pragma once
#include "game_object.h"
#define _USE_MATH_DEFINES
#include <cmath>
#include <graphics/renderer_3d.h>
#include "fruit.h"
#include "character.h"
//Player
class Player : public Character
{
public:

	Player();
	//Update
	void Update(float dt, float maxY, float minY);
	//Render
	void Render(gef::Renderer3D* renderer_3d);

	//Physics
	bool isJumbing = false;

	//Movement
	void walk(bool right, float dt);
	bool jumb();
	bool fire();
	
	//Health
	int GetHealth();
	void DecreaseHealth();
	void ResetHealth();

	//Score
	int GetScore();
	void ResetScore();
	void IncreaseScore(FRUIT_TYPE fruit_type);

	//Reset Player
	void ResetPlayer();

	//3D Models
	gef::MeshInstance dino_fire;
private:

	//Health
	int health = 3;

	//Score
	int score = 0;

	//Firing
	float cooldown = 1;

	//Damage
	float immunityCounter = 10;
	bool immune = false;
};

