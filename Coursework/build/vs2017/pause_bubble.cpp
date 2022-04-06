#include "pause_bubble.h"
#include <box2d/box2d.h>
//Initialise
void PauseBubble::Init(PrimitiveBuilder* primitive_builder_, b2World* world, b2Vec2 position)
{
	set_type(BUBBLE);

	//setup the mesh for the bubble
	set_mesh(primitive_builder_->CreateSphereMesh(1.6, 20, 20));

	object_size.x = 1.6;
	object_size.y = 1.6;


	//create a physics body for the bubble
	b2BodyDef object_body_def;
	object_body_def.type = b2_dynamicBody;

	// create a connection between the rigid body and GameObject
	object_body_def.userData.pointer = reinterpret_cast<uintptr_t>(this);

	body = world->CreateBody(&object_body_def);

	// create the shape for the player
	b2CircleShape object_shape;
	object_shape.m_radius = 1.6;
	
	// create the fixture
	b2FixtureDef object_fixture_def;
	object_fixture_def.shape = &object_shape;
	object_fixture_def.density = 1.0f;
	object_fixture_def.friction = 0.0f;
	object_fixture_def.restitution= 1.0f;

	// create the fixture on the rigid bodys
	body->CreateFixture(&object_fixture_def);
	body->SetGravityScale(0);
	body->ApplyLinearImpulseToCenter({ 20,20 }, true);

	BuildTransformationMatrix();
}

//Update
void PauseBubble::Update(float dt)
{
	BuildTransformationMatrix();
}

