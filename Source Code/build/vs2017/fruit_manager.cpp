#include "fruit_manager.h"
//Create Fruit
void FruitManager::CreateFruit(PrimitiveBuilder* primitive_builder_, b2World* world, gef::Vector2 position)
{
	//Create new Fruit
	Fruit* newFruit = new Fruit;
	//Set Mesh
	newFruit->set_mesh(fruit_mesh.mesh());
	//Set ID
	newFruit->personal_id = current_id;
	current_id++;
	//Init
	newFruit->Init(primitive_builder_, world, position);
	newFruit->set_fruit_type(CHERRY);
	fruits.push_back(newFruit);
}
//Update
void FruitManager::Update(float dt, float maxY, float minY)
{
	for (int i = 0; i < fruits.size(); i++)
	{
		if (!(fruits[i] == NULL))
		{//Update Fruits
			fruits[i]->Update(dt,maxY,minY);
		}
	}
	
	if (!fruits.empty() && fruits.back() == NULL)
	{
		fruits.pop_back();
	}
}
//Render Fruit
void FruitManager::Render(gef::Renderer3D* renderer_3d_)
{
	//For all fruit
	for (int i = 0; i < fruits.size(); i++)
	{
		if (!(fruits[i] == NULL))
		{
			//Render Fruit
			renderer_3d_->DrawMesh(*fruits[i]);
		}
	}
}

//Delete Fruit
void FruitManager::DeleteFruit(int id, b2World* world)
{
	//Search for fruit
	for (int i = 0; i < fruits.size(); i++)
	{
		if (!(fruits[i] == NULL))
		{
			if (fruits[i]->personal_id == id)
			{
				//Delete fruit
				//Body
				world->DestroyBody(fruits[i]->body);
				//Mesh
				fruits[i]->set_mesh(NULL);
				delete fruits[i];
				fruits[i] = NULL;
			}
		}
	}
}
//Clean Up
void FruitManager::CleanUp()
{
	for (int i = 0; i < fruits.size(); i++)
	{
		delete fruits[i];
		fruits[i] = NULL;
	}
	fruits.clear();
}
//Reset
void FruitManager::Reset(b2World* world)
{
	//Delete all Fruit
	for (int i = fruits.size() - 1; i >= 0; i--)
	{
		if (!(fruits[i] == NULL))
		{
			world->DestroyBody(fruits[i]->body);
			fruits[i]->set_mesh(NULL);
			delete fruits[i];
			fruits[i] = NULL;
		}
		fruits.pop_back();
	}
}
