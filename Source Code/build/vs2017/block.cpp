#include "block.h"

void Block::Init(PrimitiveBuilder* primitive_builder_, b2World* world, gef::Vector2 position, gef::Vector4 size)
{
	set_type(BLOCK);
	//setup the mesh for the player

	set_mesh(primitive_builder_->CreateBoxMesh(size));

	object_size.x = size.x();
	object_size.y = size.y();

	//create a physics body for the player
	b2BodyDef object_body_def;

	object_body_def.type = b2_staticBody;
	object_body_def.position = b2Vec2(position.x, position.y);

	// create a connection between the rigid body and GameObject
	object_body_def.userData.pointer = reinterpret_cast<uintptr_t>(this);

	body = world->CreateBody(&object_body_def);

	// create the shape for the player
	b2PolygonShape object_shape;
	object_shape.SetAsBox(size.x(), size.y());

	// create the fixture
	b2FixtureDef object_fixture_def;
	object_fixture_def.shape = &object_shape;
	object_fixture_def.density = 1.0f;
	object_fixture_def.friction = 0.0f;


	// create the fixture on the rigid body
	body->CreateFixture(&object_fixture_def);

	BuildTransformationMatrix();
}