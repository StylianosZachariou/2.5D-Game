#include "monsta.h"

Monsta::Monsta()
{
	set_enemy_type(MONSTA);
	animation.SetAnimationSpeed(5);
}

//uPDATE
void Monsta::Update(float dt, float maxY, float minY)
{
	//If is not captured
	if (!captured)
	{
		//Monsta Movement Logic
		if (int(body->GetLinearVelocity().x) == 0)
		{
			velocity.x = -velocity.x;
		}

		if (int(body->GetLinearVelocity().y) == 0)
		{
			velocity.y = -velocity.y;
		}

		//Look depending on velicty
		if (velocity.x < 0)
		{
			lookRight = false;
		}
		else
		{
			lookRight = true;

		}
		//Set Velocity
		body->SetLinearVelocity({ velocity.x * dt, velocity.y * dt });

	}
	animation.RotateY(lookRight);
	UpdateGeneral(dt, maxY, minY);
}
