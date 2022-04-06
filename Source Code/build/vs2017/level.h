#pragma once
#include "game_object.h"
#include <vector>
#include <graphics/renderer_3d.h>
#include <assets/png_loader.h>
#include <graphics/image_data.h>
//Level Class
class Level
{
public:
	//Initialise
	void Init(PrimitiveBuilder* primitive_builder_, b2World* world, gef::Platform& platform);
	//Render
	void Render(gef::Renderer3D* renderer_3d_, gef::Platform& platform);
	//Build Level
	void LevelBuilder(PrimitiveBuilder* primitive_builder_, b2World* world,std::vector<int> map);
	//Clean Up 
	void CleanUp();

	//Level Boundaries
	float maxY = 11;
	float minY = -11;

	//Spawn Positions
	gef::Vector2 spawn_points[9] = { {8,8},{-8,8},{17,1},{-17,1},{8,-5},{-8,-5},{0,-11},{17,-11},{-17,-11} };
private:
	//Game Object Pointers
	std::vector<GameObject*> platforms;
};

