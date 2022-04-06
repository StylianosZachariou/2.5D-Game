#include "scene_app.h"
#include <graphics/sprite_renderer.h>
#include <graphics/renderer_3d.h>
#include <input/input_manager.h>
#include <audio/audio_manager.h>

SceneApp::SceneApp(gef::Platform& platform) :
	Application(platform),
	sprite_renderer_(NULL),
	renderer_3d_(NULL),
	primitive_builder_(NULL),
	input_manager_(NULL),
	audio_manager_(NULL)
{
}

void SceneApp::Init()
{
	sprite_renderer_ = gef::SpriteRenderer::Create(platform_);

	// initialise input manager
	input_manager_ = gef::InputManager::Create(platform_);

	// create the renderer for draw 3D geometry
	renderer_3d_ = gef::Renderer3D::Create(platform_);

	// initialise primitive builder to make create some 3D geometry easier
	primitive_builder_ = new PrimitiveBuilder(platform_);
	
	// initialise audio manager
	audio_manager_ = gef::AudioManager::Create();
	
	//Load Sound
	audio_manager_->LoadSample("sfx/jumb_sound.wav", platform_);
	audio_manager_->LoadSample("sfx/score_sound.wav", platform_);
	audio_manager_->LoadSample("sfx/select_sound.wav", platform_);
	audio_manager_->LoadSample("sfx/damage_sound.wav", platform_);
	audio_manager_->LoadSample("sfx/cherry_sound.wav", platform_);
	audio_manager_->LoadSample("sfx/capture_sound.wav", platform_);
	audio_manager_->LoadSample("sfx/shoot_sound.wav", platform_);

	//Init GameStates
	state_machine_.Init(&platform_,primitive_builder_,sprite_renderer_,input_manager_,renderer_3d_,audio_manager_);

}

void SceneApp::CleanUp()
{
	delete input_manager_;
	input_manager_ = NULL;
	
	delete sprite_renderer_;
	sprite_renderer_ = NULL;

	delete primitive_builder_;
	primitive_builder_ = NULL;

	delete renderer_3d_;
	renderer_3d_ = NULL;

	delete audio_manager_;
	audio_manager_ = NULL;

	//Clean Up States
	state_machine_.CleanUp();
}

bool SceneApp::Update(float frame_time)
{
	//Handle Input
	input_manager_->Update();
	
	//Update Current Game State
	return (state_machine_.current_state->Update(frame_time));
	
}

void SceneApp::Render()
{
	//Render Current Game State
	state_machine_.current_state->Render();
}