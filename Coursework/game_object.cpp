#include "game_object.h"
#include <system/debug_log.h>

//
// UpdateFromSimulation
// 
// Update the transform of this object from a physics rigid body
//

void GameObject::Init(PrimitiveBuilder* primitive_builder_, b2World* world, gef::Vector2 position, gef::Vector4 size)
{
	set_type(BLOCK);
	//setup the mesh for the object

	set_mesh(primitive_builder_->CreateBoxMesh(size));

	object_size.x = size.x();
	object_size.y = size.y();

	//create a physics body for the object
	b2BodyDef object_body_def;

	object_body_def.type = b2_staticBody;
	object_body_def.position = b2Vec2(position.x, position.y);

	// create a connection between the rigid body and GameObject
	object_body_def.userData.pointer = reinterpret_cast<uintptr_t>(this);

	body = world->CreateBody(&object_body_def);

	// create the shape for the object
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

void GameObject::BuildTransformationMatrix()
{
	if (body)
	{
		// setup object rotation
		gef::Matrix44 object_rotation;
		object_rotation.RotationZ(body->GetAngle());

		// setup the object translation
		gef::Vector4 object_translation(body->GetPosition().x, body->GetPosition().y, 0.0f);

		// build object transformation matrix
		gef::Matrix44 object_transform = object_rotation;
		object_transform.RotationY(rotationY);
		object_transform.SetTranslation(object_translation);
		set_transform(object_transform);
	}
}

//Loop Around When Falling Off Stage
void GameObject::LoopAround(float maxY, float minY)
{
	//If go out on top
	if (body->GetPosition().y > maxY + object_size.y)
	{
		//Go To Botom
		float translation = minY - object_size.y;
		body->SetTransform({ body->GetPosition().x,translation }, 0);
	}

	//if fall from bottom
	if (body->GetPosition().y < minY - object_size.y)
	{
		//Go To TOP
		float translation = maxY + object_size.y;
		body->SetTransform({ body->GetPosition().x,translation }, 0);
	}

}




