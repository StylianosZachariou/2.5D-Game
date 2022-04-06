#pragma once
#include <graphics/renderer_3d.h>
#include <graphics/sprite_renderer.h>
#include "primitive_builder.h"
#include <input/input_manager.h>
#include <input/keyboard.h>
#include <graphics/font.h>
#include <graphics/scene.h>
#include <audio/audio_manager.h>
#include "load_texture.h"
#include <input/sony_controller_input_manager.h>
class StateMachine;

//Generic State Class
class State
{
public:
	//Initialise
	virtual void Init(gef::Platform* platform,
		PrimitiveBuilder* primitive_builder,
		gef::SpriteRenderer* sprite_renderer,
		gef::InputManager* input_manager,
		gef::Renderer3D* renderer_3d,
		gef::AudioManager* audio_manager,
		const gef::SonyController* controller,
		StateMachine* state_machine) {};
	//CleanUp
	virtual void CleanUp();
	//Update
	virtual bool Update(float dt) { return true; };
	//Render
	virtual void Render() {};
	//On Enter Exit
	virtual void OnEnter() {};
	virtual void onExit() {};
	

protected:
	//Load Assers
	gef::Mesh* LoadAsset(const char* asset_filename);
	gef::Scene* LoadSceneAssets(gef::Platform& platform, const char* filename);
	gef::Mesh* GetMeshFromSceneAssets(gef::Scene* scene);

	//Font
	void InitFont();
	void CleanUpFont();

	//Pointers
	const gef::SonyController* controller_;
	gef::Platform* platform_;
	PrimitiveBuilder* primitive_builder_;
	gef::SpriteRenderer* sprite_renderer_;
	gef::InputManager* input_manager_;
	gef::Renderer3D* renderer_3d_;
	gef::Font* font_;
	gef::AudioManager* audio_manager_;
	StateMachine* state_machine_;
};

