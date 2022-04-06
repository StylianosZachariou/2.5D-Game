#pragma once
#include "bubble.h"
#define _USE_MATH_DEFINES
#include <cmath>
#include "character.h"
//Enemy Types
enum ENEMY_TYPE
{
	ZEN_CHAN,
	MONSTA,
	MAITA
};

//Enemy Class
class Enemy: public Character
{
public:
	Enemy();
	//Collision with Bubble
	void CollisionBubble(Bubble* bubble);
	//Update General Settings
	void UpdateGeneral(float dt, float maxY, float minY);

	//Captured 
	bool captured = false;
	Bubble* connect_bubble;
	
	//Enemy Type
	inline void set_enemy_type(ENEMY_TYPE type) { type_ = type; }
	inline ENEMY_TYPE enemy_type() { return type_; }
	
private:
	ENEMY_TYPE type_;
};

