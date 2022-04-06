#include "main_camera.h"
#include <graphics/renderer_3d.h>
//Initialise
void MainCamera::Init(gef::Vector4 eye_)
{
	//projection
	fov = gef::DegToRad(45.0f);
	
	// view
	camera_eye = eye_;
	camera_lookat = { 0.0f, 0.0f, 0.0f };
	camera_up = { 0.0f, 1.0f, 0.0f };
}

//Update Camera
void MainCamera::Update(gef::Platform& platform_, gef::Renderer3D* renderer_3d_)
{
	//View Matrix
	view_matrix.LookAt(camera_eye, camera_lookat, camera_up);
	//Aspect Ratio
	aspect_ratio = (float)platform_.width() / (float)platform_.height();
	//Porjection Matrix
	projection_matrix = platform_.PerspectiveProjectionFov(fov, aspect_ratio, 0.1f, 100.0f);
	
	renderer_3d_->set_projection_matrix(projection_matrix);
	renderer_3d_->set_view_matrix(view_matrix);
}