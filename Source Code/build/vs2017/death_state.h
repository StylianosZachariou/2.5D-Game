#pragma once
#include "state.h"
#include <graphics/sprite.h>
//Death State Class
class DeathState: public State
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
	//Update
	bool Update(float dt) override;
	//Render
	void Render() override;
	//On Entering State
	void OnEnter() override;
	//Set State score
	void SetScore(int level_score);

private:
	//Set Ups
	void SetUpSprite();
	void SetUpBackground();
	//Score
	int score = 0;
	int display_score = 0;
	//Color of Score
	uint32_t color;
	//Sprites
	gef::Sprite game_over, background;
};

