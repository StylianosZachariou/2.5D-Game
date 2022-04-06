#ifndef _GAME_OBJECT_H
#define _GAME_OBJECT_H

#include <box2d/Box2D.h>
#include <maths/vector2.h>
#include <graphics/mesh_instance.h>
#include "primitive_builder.h"
//Game Object Types 
enum OBJECT_TYPE
{
	PLAYER,
	ENEMY,
	BUBBLE,
	BLOCK,
	FRUIT
};

//Game Object Class
class GameObject : public gef::MeshInstance
{
public:
	//Initialise
	virtual void Init(PrimitiveBuilder* primitive_builder_, b2World* world, gef::Vector2 position, gef::Vector4 size);
	//Build Transform Matrix
	void BuildTransformationMatrix();
	//Loop Around Level
	void LoopAround(float maxY, float minY);
	//Object Type
	inline void set_type(OBJECT_TYPE type) { type_ = type; }
	inline OBJECT_TYPE type() { return type_; }
	//Body
	b2Body* body;
	//Object Size
	gef::Vector2 object_size;
	//Rotation Y 
	float rotationY = 0;
private:

	OBJECT_TYPE type_;
};

#endif // _GAME_OBJECT_H