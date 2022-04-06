#include "controls_state.h"
#include <graphics/image_data.h>
#include <graphics/texture.h>
#include <system/platform.h>
#include "state_machine.h"

//Initialise
void ControlsState::Init(gef::Platform* platform, PrimitiveBuilder* primitive_builder, gef::SpriteRenderer* sprite_renderer, gef::InputManager* input_manager, gef::Renderer3D* renderer_3d,gef::AudioManager* audio_manager, const gef::SonyController* controller, StateMachine* state_machine)
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


	//Set Up Background
	controls_.set_texture(CreateTextureFromPNG("textures/controls.png", *platform_));
	controls_.set_height(platform_->height());
	controls_.set_width(platform_->width());
	controls_.set_position({ float(platform_->width() / 2),float(platform_->height() / 2),0 });

	InitFont();
}

//Update
bool ControlsState::Update(float dt)
{

	//Go Back to Menu
	if (input_manager_->keyboard()->IsKeyPressed(gef::Keyboard::KC_ESCAPE) || (controller_->buttons_pressed() & gef_SONY_CTRL_CIRCLE))
	{
		state_machine_->changeGameState(MENU);
	}
	return true;
}

//Render
void ControlsState::Render()
{
	sprite_renderer_->Begin();
	sprite_renderer_->DrawSprite(controls_);
	//Draw Text
	font_->RenderText(sprite_renderer_, { 0,float(platform_->height()) - 22,0 }, 0.6f, 0xFFFFFFFF, gef::TJ_LEFT, "%s", "Press ESC or O To Go Back");

	sprite_renderer_->End();
}
