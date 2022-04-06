#include "animated_mesh.h"

//Initialise
void AnimatedMesh::Init()
{
	//Set First Frame As Mesh
	set_mesh(animation_frames[0]->mesh());
}

//Update
void AnimatedMesh::Update(float dt)
{
	//If  last frame loop around frames
	if (int(current_frame) == (animation_frames.size()))
	{
		current_frame = 0;
	}
	else
	{
		//Continue with the next frame
		set_mesh(animation_frames[int(current_frame)]->mesh());
		current_frame += dt * speed;
	}
	
	//Rotate Mesh
	if (isLookingRight && rotationY > 0)
	{
		//Rotate Animation Right
		rotationY -= speed*3*dt;
	}
	else
	{ 
		//Rotate Animation Left
		if (!isLookingRight && rotationY < M_PI)
		{
			rotationY += dt*speed * 3;
		}
		else
		{
			//Straiten Rotation
			if (rotationY < 0)
			{
				rotationY = 0;
			}
			else
			{
				if (rotationY > M_PI)
				{
					rotationY = M_PI;
				}
			}
		}
	}

}

//Add Frame To Sequence
void AnimatedMesh::AddFrame(gef::Mesh* new_frame)
{
	gef::MeshInstance* new_Mesh = new gef::MeshInstance;
	new_Mesh->set_mesh(new_frame);
	animation_frames.push_back(new_Mesh);
}

//Change Animation Speed
void AnimatedMesh::SetAnimationSpeed(int new_speed)
{
	speed = new_speed;
}

//Rotate 
void AnimatedMesh::RotateY(bool right)
{
	//Rotate Animation
	if (isLookingRight && right)
	{

	}
	else
	{
		if (!isLookingRight && !right)
		{
		}
		else
		{
			isLookingRight = !isLookingRight;
		}
	}
}
