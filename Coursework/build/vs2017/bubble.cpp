#include "bubble.h"
#include <graphics/mesh.h>
#include <graphics/mesh_instance.h>

//Initialise Bubble
void Bubble::Init(PrimitiveBuilder* primitive_builder_, b2World* world, b2Vec2 position, float player_sizeX,bool direction, int id)
{
	set_type(BUBBLE);

	//setup the mesh for the bubble
	
	set_mesh(primitive_builder_->CreateSphereMesh(1.2,10,10));
	
	object_size.x = 1.2;
	object_size.y = 1.2;
	

	//create a physics body for the bubble
	b2BodyDef object_body_def;

	//Set Position depending on direction
	object_body_def.type = b2_dynamicBody;
	if (direction)
	{
		object_body_def.position = { position.x + object_size.x + player_sizeX/2, position.y };
	}
	else
	{
		object_body_def.position = { position.x - object_size.x - player_sizeX/2, position.y };
		velocity = -velocity;
	}

	// create a connection between the rigid body and object
	object_body_def.userData.pointer = reinterpret_cast<uintptr_t>(this);

	body = world->CreateBody(&object_body_def);
	
	// create the shape for the bubble
	b2CircleShape object_shape;
	object_shape.m_radius = 1.2;

	// create the fixture
	b2FixtureDef object_fixture_def;
	object_fixture_def.shape = &object_shape;
	object_fixture_def.density = 1.0f;
	object_fixture_def.friction = 0.0f;
	
	// create the fixture on the rigid bodys
	body->CreateFixture(&object_fixture_def);
	body->SetGravityScale(0);
	
	//ID
	personal_id = id;

	BuildTransformationMatrix();
}

//Update Bubble
void Bubble::Update(float dt, float maxY, float minY)
{
	//Calculate move velocity
	float move_velocity = velocity * dt;
	//If Bubble just started
	if (std::abs(velocity) > 100)
	{

		if (velocity < 0)
		{
			velocity+=300*dt;
		}
		else
		{
			velocity-=300*dt;
		}
	}
	else
	{
		//Disable Bubble Cant capture any more
		isEnabled = false;

		//Dont Allow Bubble to leave level
		if (body->GetPosition().y > maxY-2)
		{
			body->SetGravityScale(1);
		}
		else
		{
			body->SetGravityScale(-1);
		}
	}	

	//Set Bubbles Velocity
	body->SetLinearVelocity({ move_velocity,body->GetLinearVelocity().y });
	//Loop Around Stage
	LoopAround(maxY, minY);
	BuildTransformationMatrix();
}
