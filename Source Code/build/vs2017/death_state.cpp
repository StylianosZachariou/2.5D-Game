#include "death_state.h"
#include <system/platform.h>
#include "state_machine.h"
//Initialise
void DeathState::Init(gef::Platform* platform, PrimitiveBuilder* primitive_builder, gef::SpriteRenderer* sprite_renderer, gef::InputManager* input_manager, gef::Renderer3D* renderer_3d,gef::AudioManager* audio_manager, const gef::SonyController* controller, StateMachine* state_machine)
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

	//InitFont
	InitFont();

	//Load Sprite
	SetUpSprite();

	//Background
	SetUpBackground();
}

//Update
bool DeathState::Update(float dt)
{
	//Increment Display Scor until it matches players score
	if (display_score < score)
	{
		display_score+=50;

		if (!audio_manager_->sample_voice_playing(2))
		{
			//Play score sound effect
			audio_manager_->PlaySample(2, false);
		}
	}

	//Color Depends Display Score
	if (display_score < 2500)
	{
		color = 0xFF0000FF;
	}
	else
	{ 
		if (display_score < 5000)
		{
			color = 0xFF00FFFF;
		}
		else
		{
			color = 0xFF00FF00;
		}
	}

	//Go Back To Menu
	if (input_manager_->keyboard()->IsKeyPressed(gef::Keyboard::KC_ESCAPE) || (controller_->buttons_pressed() & gef_SONY_CTRL_CIRCLE))
	{
		state_machine_->changeGameState(MENU);
	}
	return true;
}

//Redre
void DeathState::Render()
{

	sprite_renderer_->Begin();
	//Sprites
	sprite_renderer_->DrawSprite(background);
	sprite_renderer_->DrawSprite(game_over);
	//Text
	font_->RenderText(sprite_renderer_, {float(platform_->width()/2),float(platform_->height()/1.5),0}, 1.5f, color, gef::TJ_CENTRE, "%i", display_score);
	font_->RenderText(sprite_renderer_, { 0,float(platform_->height()) - 22,0 }, 0.6f, 0xFFFFFFFF, gef::TJ_LEFT, "%s", "Press ESC or O To Go Back");

	sprite_renderer_->End();
}

//On Enter
void DeathState::OnEnter()
{
	//Play Death Music
	audio_manager_->LoadMusic("sfx/death_music.wav", *platform_);
	audio_manager_->PlayMusic();
}

//Score Setter
void DeathState::SetScore(int level_score)
{
	score = level_score;
}
//Set Up Sprite
void DeathState::SetUpSprite()
{
	//Set Up Background

	game_over.set_texture(CreateTextureFromPNG("textures/game_over.png", *platform_));
	game_over.set_height(328);
	game_over.set_width(819.2);
	game_over.set_position({ float(platform_->width()/2), float(platform_->height() / 3),0 });
}

//Set Up Background
void DeathState::SetUpBackground()
{
	background.set_colour(0xFF000000);
	background.set_height(platform_->height());
	background.set_width(platform_->width());
	background.set_position({ float(platform_->width() / 2),float(platform_->height() / 2),0 });
}
