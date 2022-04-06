#include "maita.h"

Maita::Maita()
{
	set_enemy_type(MAITA);
	animation.SetAnimationSpeed(5);
}

//Update
void Maita::Update(float dt, gef::Vector2 player_position, float maxY, float minY)
{
	//If Is not captured
	if (!captured)
	{
		//Move Towards Player, faster far awway
		gef::Vector2 direction;
		direction.x = (player_position.x - body->GetPosition().x);
		direction.y = (player_position.y - body->GetPosition().y);

		//Look depending on direction
		if (direction.x < 0)
		{
			lookRight = false;
		}
		else
		{
			lookRight = true;

		}

		//Set Velocity
		body->SetLinearVelocity({ direction.x * dt * velocity,direction.y * dt * velocity });

	}
	
	animation.RotateY(lookRight);
	UpdateGeneral(dt, maxY, minY);
}

