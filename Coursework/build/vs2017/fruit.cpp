#include "fruit.h"
#include <graphics/mesh.h>
Fruit::Fruit()
{
	set_type(FRUIT);
}
//Initialise
void Fruit::Init(PrimitiveBuilder* primitive_builder_, b2World* world, gef::Vector2 position)
{
	//Object Size Depending ON Mesh Size
	object_size.x = mesh()->aabb().max_vtx().x() - mesh()->aabb().min_vtx().x();
	object_size.y = mesh()->aabb().max_vtx().y() - mesh()->aabb().min_vtx().y();

	//create a physics body for the fruit
	b2BodyDef fruit_body_def;
	fruit_body_def.type = b2_dynamicBody;
	fruit_body_def.position = b2Vec2(position.x, position.y);

	// create a connection between the rigid body and object
	fruit_body_def.userData.pointer = reinterpret_cast<uintptr_t>(this);

	body = world->CreateBody(&fruit_body_def);

	// create the shape for the fruit
	b2PolygonShape fruit_shape;
	fruit_shape.SetAsBox(object_size.x / 2, object_size.y / 2);

	// create the fixture
	b2FixtureDef fruit_fixture_def;
	fruit_fixture_def.shape = &fruit_shape;
	fruit_fixture_def.density = 1.0f;

	// create the fixture on the rigid body
	body->CreateFixture(&fruit_fixture_def);
	body->SetFixedRotation(true);

	BuildTransformationMatrix();
}

//Update
void Fruit::Update(float dt, float maxY, float minY)
{
	//Spin Fruit
	rotationY+= dt*2;
	//If Fall Loop
	LoopAround(maxY,minY);
	BuildTransformationMatrix();
}


