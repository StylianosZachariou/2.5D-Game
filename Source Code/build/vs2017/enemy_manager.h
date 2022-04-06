#pragma once
#include "zen_chan.h"
#include <vector>
#include <graphics/renderer_3d.h>
#include <stdio.h>
#include <stdlib.h>

//Enemy Manager class
class EnemyManager
{
public:
	//Initialise
	void Init(gef::Vector2 spawn_pos[]);
	//Create Enemies
	void CreateEnemies(b2World* world, int wave);
	//Update
	void Update(float dt,gef::Vector2 player_pos,float maxY, float minY, b2World* world);
	//Render
	void Render(gef::Renderer3D* renderer_3d_);
	//Destroy Specific Enemy
	void DestroyEnemy(Enemy* enemy, b2World* world);
	//Find and Destroy specific bubble
	void FindAndDestroy(b2World* world,int bubble_id);
	//Clean Up Manager
	void CleanUp();
	//Reset Manager
	void Reset(b2World* world);
	//Animation of all enemies
	AnimatedMesh enemy_animations[3];
	//Is Wave Finished
	bool isFinished = false;

private:
	//Enemy pointers
	std::vector<Enemy*> enemies;
	//Possible spawning positions
	gef::Vector2 spawn_positions[9];
};
