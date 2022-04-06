#pragma once
#include <maths/vector2.h>
#include <maths/math_utils.h>
#include <maths/matrix44.h>
#include <system/platform.h>
//Main Camera
class MainCamera
{
public:
	//Initialise
	void Init(gef::Vector4 eye_);
	//Update
	void Update(gef::Platform& platform_, gef::Renderer3D* renderer_3d_);

private:
	//Settings
	float fov;
	float aspect_ratio;
	//EYE LOOKAT UP
	gef::Vector4 camera_eye;
	gef::Vector4 camera_lookat;
	gef::Vector4 camera_up;
	//Matrices
	gef::Matrix44 view_matrix;
	gef::Matrix44 projection_matrix;
};

