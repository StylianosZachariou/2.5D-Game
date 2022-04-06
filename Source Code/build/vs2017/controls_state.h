#pragma once
#include "state.h"
#include "graphics/sprite.h"

//Control State Class
class ControlsState: public State
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

private:
	//Controls Spirite
	gef::Sprite controls_;
};

