#include "enemy.h"
#include <graphics/mesh.h>
Enemy::Enemy()
{
	set_type(ENEMY);

}

//Collision With Bubble
void Enemy::CollisionBubble(Bubble* bubble)
{
	captured = true;
	connect_bubble = bubble;
}

//Update General
void Enemy::UpdateGeneral (float dt,float maxY, float minY)
{
	//If IS Captured by Bubble
	if (captured)
	{
		
		if (connect_bubble->personal_id >= 0)
		{
			//Move Enemy with Bubble
			body->SetEnabled(false);
			body->SetTransform({ connect_bubble->body->GetPosition().x, connect_bubble->body->GetPosition().y},0);
		}
	}
	else
	{
		//Else Update Animation, Position,Rotation
		set_mesh(animation.mesh());
		LoopAround(maxY, minY);
		animation.Update(dt);
		rotationY = animation.rotationY;
		
	}
	BuildTransformationMatrix();
}
