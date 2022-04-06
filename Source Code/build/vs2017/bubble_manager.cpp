#include "Bubble_manager.h"
#include <graphics/material.h>
//Create New Bubble
void BubbleManager::CreateNewBubble(PrimitiveBuilder* primitive_builder_, b2World* world, b2Vec2 position, float player_sizeX, bool direction)
{
	for (int i = 0; i < 7; i++)
	{
		//If There are less than 7 bubbles
		if (bubbles[i] == NULL)
		{
			//Create New Bubble
			bubbles[i] = new Bubble;
			bubbles[i]->Init(primitive_builder_, world, position, player_sizeX, direction, i);
			break;
		}
	}
}

//Render Bubbles
void BubbleManager::RenderBubbles(gef::Renderer3D* renderer_3d_)
{
	//Green half transparent material
	gef::Material bubble_material;
	bubble_material.set_colour(0x6F7FFF00);
	
	renderer_3d_->set_override_material(&bubble_material);
	
	for (int i = 0; i < 7; i++)
	{
		if (!(bubbles[i] == NULL))
		{
			//Rendre Bubbles
			renderer_3d_->DrawMesh(*bubbles[i]);
		}
	}
	//Reset override material
	renderer_3d_->set_override_material(NULL);
}

//Update
void BubbleManager::Update(float dt,float maxY,float minY)
{
	for (int i = 0; i < 7; i++)
	{
		if (!(bubbles[i] == NULL))
		{
			//Update Bubble
			bubbles[i]->Update(dt,maxY,minY);
		}
	}
}
//Reset
void BubbleManager::Reset(b2World* world)
{
	//Destroy All Bubbbles
	for (int i = 0; i <size; i++)
	{
		if (!(bubbles[i] == NULL))
		{
			world->DestroyBody(bubbles[i]->body);
			bubbles[i] ->set_mesh(NULL);
			delete bubbles[i];
			bubbles[i] = NULL;
		}
	}
}
//Pop Bubble
void BubbleManager::CollisionPop(Bubble bubble, b2World* world)
{
	//Destroy Bubble
	world->DestroyBody(bubbles[bubble.personal_id]->body);
	bubbles[bubble.personal_id]->set_mesh(NULL);
 	delete bubbles[bubble.personal_id];
	bubbles[bubble.personal_id] = NULL;
}
//Clean  Up Bubbles
void BubbleManager::CleanUp()
{
	for (int i = 0; i < 7; i++)
	{
		delete bubbles[i];
		bubbles[i] = NULL;
	}
}

