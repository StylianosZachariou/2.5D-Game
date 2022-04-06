#pragma once
#include "state.h"
#include <box2d/box2d.h>
#include "main_camera.h"
#include "pause_bubble.h"
#include "player.h"
#include <graphics/sprite.h>
//Pause State Class
class PauseState: public State
{
public:
	//Initialise
	void Init(gef::Platform* platform,
		PrimitiveBuilder* primitive_builder,
		gef::SpriteRenderer* sprite_renderer,
		gef::InputManager* input_manager,
		gef::Renderer3D* renderer_3d,
		gef::AudioManager* audio_manager,
		const gef::SonyController* controller,
		StateMachine* state_machine) override;
	//Clean Up
	void CleanUp() override;
	//Update
	bool Update(float dt) override;
	//Render
	void Render() override;


private:
	//Set Up
	void SetUpGameObjects();
	void SetUpBackground();
	//Update Physics Simulation
	void UpdateSimulation(float dt);

	// create the physics world
	b2World* world_;

	//Camera
	MainCamera camera;

	//Bubble
	PauseBubble bubble;

	//Barriers
	GameObject blocks[4];

	//Dino
	Player dino;
	
	//Colours
	uint32_t colors[7] = {0xFFFF0000,0XFFFFA500,0XFFFFFF00,0XFF008000,0XFF0000FF,0XFF4B0082,0XFFEE82EE};
	int current_color = -1;

	//Background
	gef::MeshInstance background_;

};

