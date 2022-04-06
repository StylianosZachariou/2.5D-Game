#pragma once

#define _USE_MATH_DEFINES
#include <cmath>
#include <animation/animation.h>
#include <graphics/mesh_instance.h>
#include <graphics/mesh.h>

//Animated Mesh Class 3d Stop Motion Animation
class AnimatedMesh: public gef::MeshInstance
{
public:
	//Initialise
	void Init();
	//Update
	void Update(float dt);
	//Add Frame To Animation
	void AddFrame(gef::Mesh* new_frame);
	//Set Speed
	void SetAnimationSpeed(int speed);
	//Rotate Y of 3D Model
	void RotateY(bool right);
	//Direction
	bool isLookingRight = true;
	//Rotation
	float rotationY = 0;

private:
	//Speed
	int speed = 2;
	//Current Frame
	float current_frame = 0;
	//All Frames
	std::vector<gef::MeshInstance*> animation_frames;
};

