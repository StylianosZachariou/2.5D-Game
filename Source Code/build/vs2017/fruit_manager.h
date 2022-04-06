#pragma once
#include "fruit.h"
#include <vector>
#include <graphics/renderer_3d.h>
//Fruit manager Class
class FruitManager
{
public:
	//Create New Fruit
	void CreateFruit(PrimitiveBuilder* primitive_builder_, b2World* world, gef::Vector2 position);
	//Update
	void Update(float dt, float maxY, float minY);
	//Render
	void Render(gef::Renderer3D* renderer_3d_);
	//Delete Specific Fruit
	void DeleteFruit(int id,b2World* world);
	//Clean Up Manager
	void CleanUp();
	//Reset Manager
	void Reset(b2World* world_);
	//Fruit Meshes
	gef::MeshInstance fruit_mesh;

private:
	//Fruits
	std::vector<Fruit*> fruits;
	int current_id = 0;
};

