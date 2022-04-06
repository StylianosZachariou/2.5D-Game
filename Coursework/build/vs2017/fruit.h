#pragma once
#include "game_object.h"

//Fruit Types
enum FRUIT_TYPE
{
	CHERRY
};

//Fruit Class
class Fruit: public GameObject
{
public:
	Fruit();
	//Initialise
	void Init(PrimitiveBuilder* primitive_builder_, b2World* world, gef::Vector2 position);
	//Update
	void Update(float dt,float maxY, float minY);
	//Fruit ID
	int personal_id = -1;

	//Fruit Type
	inline void set_fruit_type(FRUIT_TYPE type) { type_ = type; }
	inline FRUIT_TYPE fruit_type() { return type_; }

private:
	FRUIT_TYPE type_;
};

