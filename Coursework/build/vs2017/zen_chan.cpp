#include "zen_chan.h"
#include "graphics/mesh.h"

ZenChan::ZenChan()
{
	set_enemy_type(ZEN_CHAN);
	animation.SetAnimationSpeed(5);
}

//Update
void ZenChan::Update(float dt, float maxY,float minY)
{
	if (!captured)
	{
		//Zen Chan Movement Logic
		if (int(body->GetLinearVelocity().x) == 0)
		{
			velocity = -velocity;
		}

		//Look direction depending on velocity
		if (velocity < 0)
		{
			lookRight = false;
		}
		else
		{
			lookRight = true;

		}
		//Set Velocity
		body->SetLinearVelocity({ velocity * dt,body->GetLinearVelocity().y });

	}
	animation.RotateY(lookRight);
	UpdateGeneral(dt,maxY,minY);
}
