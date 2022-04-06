#pragma once
#include "state.h"
#include <graphics/sprite.h>
#include <graphics/texture.h>
#include "enemy_manager.h"
//Main Menu State
class MainMenuState: public State
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
	//On Enter
	void OnEnter() override;

private:
	//Menu Choice
	int choice = 2;
	//Change Sprites
	void ChangeSprites();
	//Set Up
	void SetUpBackground();
	void SetUpTextures();
	void SetUpTexturedSprites();
	//Textures
	gef::Texture* logo_tex;
	gef::Texture* play_tex[2];
	gef::Texture* options_tex[2];
	gef::Texture* controls_tex[2];
	//Sprites
	gef::Sprite play_;
	gef::Sprite options_;
	gef::Sprite controls_;
	gef::Sprite logo_;
	gef::Sprite background_;

	//Controller Input
	bool left_stick_released = false;
};

