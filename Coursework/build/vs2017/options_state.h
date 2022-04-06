#pragma once
#include "state.h"
#include <graphics/sprite.h>
//Options State Class
class OptionsState: public State
{
public:
	//Initalise
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
	void SetUpTextures();
	void SetUpTexturedSprites();
	void SetUpBackground();
	//Change Sprites
	void ChangeSprites();
	//Choices
	bool volumeChange = true;
	int choice = 1;

	//Textures
	gef::Texture* volume_tex[3];
	gef::Texture* sounds_tex[3];
	gef::Texture* inc_tex[2];
	gef::Texture * dec_tex[2];

	//Sprites
	gef::Sprite volume;
	gef::Sprite sounds;
	gef::Sprite plus;
	gef::Sprite minus;
	gef::Sprite background;

	//Controller Input
	bool left_stick_released_x = false;
	bool left_stick_released_y = false;
};

