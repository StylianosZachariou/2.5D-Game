#include "pause_state.h"
#include <system/platform.h>
#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include "state_machine.h"
//Initialise
void PauseState::Init(gef::Platform* platform, PrimitiveBuilder* primitive_builder, gef::SpriteRenderer* sprite_renderer, gef::InputManager* input_manager, gef::Renderer3D* renderer_3d,gef::AudioManager* audio_manager, const gef::SonyController* controller, StateMachine* state_machine)
{
	//Set Up Pointers
	platform_ = platform;
	primitive_builder_ = primitive_builder;
	sprite_renderer_ = sprite_renderer;
	input_manager_ = input_manager;
	renderer_3d_ = renderer_3d;
	audio_manager_ = audio_manager;
	controller_ = controller;
	state_machine_ = state_machine;

	// initialise the physics world
	b2Vec2 gravity(0.0f, 0.0f);
	world_ = new b2World(gravity);

	//randomness
	srand(time(0));

	//Camera
	camera.Init({0,0,15});

	//SetUp
	SetUpGameObjects();
	SetUpBackground();

	//Colors
	current_color = rand() % 7;

}

//Clean UP
void PauseState::CleanUp()
{
	delete platform_;
	platform_ = NULL;
	delete primitive_builder_;
	primitive_builder_ = NULL;
	delete sprite_renderer_;
	sprite_renderer_ = NULL;
	delete input_manager_;
	input_manager_ = NULL;
	delete renderer_3d_;
	renderer_3d_ = NULL;
	delete audio_manager_;
	audio_manager_ = NULL;
	delete state_machine_;
	state_machine_ = NULL;

	delete world_;
	world_ = NULL;
}

//Update
bool PauseState::Update(float dt)
{
	//Return to level
	if (input_manager_->keyboard()->IsKeyPressed(gef::Keyboard::KC_P) || (controller_->buttons_pressed() & gef_SONY_CTRL_SELECT))
	{
		state_machine_->changeGameState(LEVEL);
	}

	//Dino follows bubble
	dino.body->SetTransform({ bubble.body->GetPosition().x, bubble.body->GetPosition().y}, 0);
	dino.BuildTransformationMatrix();
	//Update Camera
	camera.Update(*platform_, renderer_3d_);
	//Update Physics Simulation
	UpdateSimulation(dt);
	return true;
}

//Render
void PauseState::Render()
{	
	//Create Bubble Material
	uint32_t bubble_colour= (120 << 24) | (colors[current_color] & 0x00FFFFFF);
	gef::Material material;

	renderer_3d_->Begin();
	//Background
	material.set_colour(0xFF000000);
	renderer_3d_->set_override_material(&material);
	renderer_3d_->DrawMesh(background_);
	renderer_3d_->set_override_material(NULL);
	//Dino
	renderer_3d_->DrawMesh(dino);
	//Bubble
	material.set_colour(bubble_colour);
	renderer_3d_->set_override_material(&material);
	renderer_3d_->DrawMesh(bubble);
	renderer_3d_->set_override_material(NULL);

	renderer_3d_->End();

}

//Set Up Game Objects
void PauseState::SetUpGameObjects()
{
	//Dino
	dino.animation.AddFrame(LoadAsset("dino_models/dino-fire.scn"));
	dino.Init(world_, { 0,0 }, true);
	dino.body->SetEnabled(false);
	//Bubble
	bubble.Init(primitive_builder_, world_, { 0,0 });

	//Create Boundaries around screen
	float x = 22.2;
	float y = 13.1;
	float sizex = x/2;
	float sizey = y/ 2;

	blocks[0].Init(primitive_builder_, world_, { 0,-sizey }, { sizex*2,0.5,0.5 });
	blocks[1].Init(primitive_builder_, world_, { 0,sizey }, { sizex*2,0.5,0.5 });
	blocks[2].Init(primitive_builder_, world_, { -sizex,0 }, { 0.5,sizey*2,0.5 });
	blocks[3].Init(primitive_builder_, world_, { sizex,0 }, { 0.5,sizey*2,0.5 });
}

///Update Physics Simulation
void PauseState::UpdateSimulation(float dt)
{
	// update physics world
	float timeStep = 1.0f / 60.0f;

	int32 velocityIterations = 6;
	int32 positionIterations = 2;
	world_->Step(timeStep, velocityIterations, positionIterations);

	bubble.Update(dt);

	// collision detection
	// get the head of the contact list
	b2Contact* contact = world_->GetContactList();
	// get contact count
	int contact_count = world_->GetContactCount();

	//If Contact
	for (int contact_num = 0; contact_num < contact_count; ++contact_num)
	{
		if (contact->IsTouching())
		{
			//Change Color Randomly
			int previous = current_color;
			while (previous == current_color)
			{
				current_color = rand() % 7;
			}
		}
	}
}

//Set Up background
void PauseState::SetUpBackground()
{
	background_.set_mesh(primitive_builder_->GetDefaultCubeMesh());
	gef::Matrix44 transform;
	transform.Scale({34,21,1 });
	transform.SetTranslation({0,0,-8});
	background_.set_transform(transform);
}
