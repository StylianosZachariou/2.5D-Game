#include "character.h"
//Initialise Character
void Character::Init(b2World* world, gef::Vector2 position, bool circle)
{
	//Initialise Animation
	animation.Init();
	set_mesh(animation.mesh());

	//get object size from mesh size
	object_size.x = mesh()->aabb().max_vtx().x() - mesh()->aabb().min_vtx().x();
	object_size.y = mesh()->aabb().max_vtx().y() - mesh()->aabb().min_vtx().y();

	//create a physics body for the character
	b2BodyDef character_body_def;
	character_body_def.type = b2_dynamicBody;
	character_body_def.position = b2Vec2(position.x, position.y);

	// create a connection between the rigid body and GameObject
	character_body_def.userData.pointer = reinterpret_cast<uintptr_t>(this);
	character_body_def.gravityScale = 2.81;

	body = world->CreateBody(&character_body_def);
	// create the fixture

	b2FixtureDef character_fixture_def;

	b2PolygonShape character_box;
	b2CircleShape character_circle;
	// create the shape for the character
	if (true)
	{
		character_circle.m_radius = object_size.x / 2;
		character_fixture_def.shape = &character_circle;
	}
	else
	{
		character_box.SetAsBox(object_size.x / 2, object_size.y / 2);
		character_fixture_def.shape = &character_box;
	}
	character_fixture_def.density = 1.0f;
	character_fixture_def.friction = 0.0f;


	// create the fixture on the rigid body
	body->CreateFixture(&character_fixture_def);
	body->SetFixedRotation(true);

	BuildTransformationMatrix();
}
