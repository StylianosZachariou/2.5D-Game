#pragma once
#include "bubble.h"
#include <graphics/renderer_3d.h>

//Bubble Manager
class BubbleManager
{
public:
	//Create New Bubble
	void CreateNewBubble(PrimitiveBuilder* primitive_builder_, b2World* world, b2Vec2 position, float player_size, bool direction);
	//Render Bubbles
	void RenderBubbles(gef::Renderer3D* renderer_3d_);
	//Update Bubbles
	void Update(float dt, float maxY,float minY);
	//Pop Bubble
	void CollisionPop(Bubble bubble, b2World* world);
	//Clean Up
	void CleanUp();
	//Max bubbles
	int size = 7;
	//Reset Manager
	void Reset(b2World* world);

private:
	//Bubble Pointers
	Bubble* bubbles[7] = { NULL,NULL,NULL,NULL,NULL,NULL,NULL};
};

