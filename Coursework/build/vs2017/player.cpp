#include "Player.h"
#include <graphics/mesh.h>
#include <maths/matrix44.h>
#include <fstream>
#include <graphics/material.h>

Player::Player()
{
	set_type(PLAYER);
	animation.SetAnimationSpeed(5);
}

//Walk
void Player::walk(bool right, float dt)
{
	float walk_speed = 400 * dt;
	if (right) //Go Right
	{
		lookRight = true;
		// Walk And Walk Animation
		body->SetLinearVelocity({ walk_speed,body->GetLinearVelocity().y });
	}
	else //Go Left
	{
		lookRight = false;
		//Walk And Walk Animation
		body->SetLinearVelocity({ -walk_speed,body->GetLinearVelocity().y });	
	}
	animation.RotateY(lookRight);
	set_mesh(animation.mesh());
}

//Jumb
bool Player::jumb()
{
	if (!isJumbing)//If is not jumbing
	{
		body->SetLinearVelocity({ 0,20});	
		isJumbing = true;
		return true;
	}
	return false;
}

//Fire
bool Player::fire()
{
	if (cooldown >= 1)//If cooldown is over
	{
		cooldown = 0;
		set_mesh(dino_fire.mesh());
		return true;
	}
	return false;
}

//Get Health
int Player::GetHealth()
{
	return health;
}

//Decrease Health
void Player::DecreaseHealth()
{
	if (!immune)//If Is Not Immune
	{
		health--;
		immunityCounter = 0;
	}
}

//Reset Health
void Player::ResetHealth()
{
	health = 3;
}

//Get Score
int Player::GetScore()
{
	return score;
}

//Reset Score
void Player::ResetScore()
{
	score = 0;
}

//Increase Score
void Player::IncreaseScore(FRUIT_TYPE fruit_type)
{
	if (fruit_type == CHERRY)
	{
		score += 100;
	}
}

//Reset Player
void Player::ResetPlayer()
{
	body->SetTransform({ 0,0 }, 0);
	ResetHealth();
	ResetScore();
	immunityCounter = 10;
}

//Update
void Player::Update(float dt, float maxY, float minY)
{
	//If dino is touching the groung. it can jumb
	if (int(body->GetLinearVelocity().y) == 0)
	{
		isJumbing = false;
	}
	else
	{
		isJumbing = true;
	}

	//Shooting Cooldown
	if (cooldown < 1)
	{
		cooldown += 2 * dt;
		set_mesh(dino_fire.mesh());
	}
	else
	{
		if (mesh() == dino_fire.mesh())
		{
			set_mesh(animation.mesh());

		}
	}

	//Immunity Cooldown
	if (immunityCounter < 10)
	{
		immune = true;
		immunityCounter += dt * 5;
	}
	else
	{
		immune = false;
	}

	//Stop Player From Slipping
	body->SetLinearVelocity({ 0,body->GetLinearVelocity().y });

	//Update Animation
	animation.Update(dt);
	rotationY = animation.rotationY;

	BuildTransformationMatrix();
	LoopAround(maxY, minY);
}

//Render
void Player::Render(gef::Renderer3D* renderer_3d)
{
	if (immune) //IF player is immune
	{
		if (!(int(immunityCounter) % 2 == 0))//flash red color
		{
			gef::Material material;
			material.set_colour(0xAF0000FF);
			renderer_3d->set_override_material(&material);
		}
	}
	renderer_3d->DrawMesh(*this);
	renderer_3d->set_override_material(NULL);
}
