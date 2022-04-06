#include "main_menu_state.h"
#include <system/platform.h>
#include <graphics/image_data.h>
#include "state_machine.h"

//Initialise
void MainMenuState::Init(gef::Platform* platform, PrimitiveBuilder* primitive_builder, gef::SpriteRenderer* sprite_renderer, gef::InputManager* input_manager, gef::Renderer3D* renderer_3d,gef::AudioManager* audio_manager, const gef::SonyController* controller, StateMachine* state_machine)
{
	//Set Up pointers
	platform_ = platform;
	primitive_builder_ = primitive_builder;
	sprite_renderer_ = sprite_renderer;
	input_manager_ = input_manager;
	renderer_3d_ = renderer_3d;
	audio_manager_ = audio_manager;
	controller_ = controller;
	state_machine_ = state_machine;

	//Set Up Textures and Sprites
	SetUpBackground();
	SetUpTextures();
	SetUpTexturedSprites();

}

//Clean up
void MainMenuState::CleanUp()
{
	delete logo_tex;
	logo_tex = NULL;

	for (int i = 0; i < 2; i++)
	{
		delete play_tex[i];
		play_tex[i] = NULL;
		delete options_tex[i];
		options_tex[i] = NULL;
		delete controls_tex[i];
		controls_tex[i] = NULL;
	}
}

//Update
bool MainMenuState::Update(float dt)
{
	//If Left stick is released
	if (controller_->left_stick_x_axis() == 0)
	{
		left_stick_released = true;
	}

	//Move Choice Left
	if (input_manager_->keyboard()->IsKeyPressed(gef::Keyboard::KC_LEFT) || ( left_stick_released && (controller_->left_stick_x_axis() < 0)))
	{
		//Left stick is hold
		left_stick_released = false;
		//play sound effect
		audio_manager_->PlaySample(2,false);
		choice--;
		if (choice < 1)
		{
			choice = 3;
		}
	}
	//Move Choice Right
	if (input_manager_->keyboard()->IsKeyPressed(gef::Keyboard::KC_RIGHT) || (left_stick_released && controller_->left_stick_x_axis() > 0))
	{
		//Left stick is hold
		left_stick_released = false;
		//play sound effect
		audio_manager_->PlaySample(2, false);
		choice++;
		if (choice >3)
		{
			choice = 1;
		}
	}
	//Select Choice
	if (input_manager_->keyboard()->IsKeyPressed(gef::Keyboard::KC_SPACE) || (controller_->buttons_pressed() & gef_SONY_CTRL_CROSS))
	{
		//OPTIONS
		if (choice == 1)
		{
			state_machine_->changeGameState(OPTIONS);
		}
		else
		{
			//LEVEL
			if (choice == 2)
			{
				state_machine_->changeGameState(LEVEL);
			}
			else
			{
				//CONTROLS
				if (choice == 3)
				{
					state_machine_->changeGameState(CONTROLS);
				}
			}
		}
	}

	//Change Sprites
	ChangeSprites();
	return true;
}

//Render
void MainMenuState::Render()
{
	sprite_renderer_->Begin();
	
	sprite_renderer_->DrawSprite(background_);
	sprite_renderer_->DrawSprite(logo_);
	sprite_renderer_->DrawSprite(play_);
	sprite_renderer_->DrawSprite(options_);
	sprite_renderer_->DrawSprite(controls_);

	sprite_renderer_->End();

}

//On Enter
void MainMenuState::OnEnter()
{
	//Play Menu Music
	audio_manager_->LoadMusic("sfx/menu_music.wav", *platform_);
	audio_manager_->PlayMusic();
}

//Change Sprites depending on choice
void MainMenuState::ChangeSprites()
{
	if (choice == 1) //OPTIONS
	{
		play_.set_texture(play_tex[1]);
		options_.set_texture(options_tex[0]);
		controls_.set_texture(controls_tex[1]);
		options_.set_height(120);
		options_.set_width(120);
		play_.set_height(80);
		play_.set_width(80);
		controls_.set_height(80);
		controls_.set_width(80);

	}
	else
	{

		if (choice == 2) //PLAY
		{

			play_.set_texture(play_tex[0]);
			options_.set_texture(options_tex[1]);
			controls_.set_texture(controls_tex[1]);
			play_.set_height(120);
			play_.set_width(120);
			controls_.set_height(80);
			controls_.set_width(80);
			options_.set_height(80);
			options_.set_width(80);
		}
		else
		{

			if (choice == 3)//CONTROLS
			{
				play_.set_texture(play_tex[1]);
				options_.set_texture(options_tex[1]);
				controls_.set_texture(controls_tex[0]);
				controls_.set_height(120);
				controls_.set_width(120);
				play_.set_height(80);
				play_.set_width(80);
				options_.set_height(80);
				options_.set_width(80);
			}

		}
	}
}

//Set Up Background
void MainMenuState::SetUpBackground()
{
	background_.set_texture(CreateTextureFromPNG("textures/bubble_background.png", *platform_));
	background_.set_height(platform_->height());
	background_.set_width(platform_->width());
	background_.set_position({ float(platform_->width() / 2),float(platform_->height() / 2),0 });
}

//Set Up Textures
void MainMenuState::SetUpTextures()
{
	//Initialise Textures
	
	//LOGO TEXTURE
	logo_tex = CreateTextureFromPNG("textures/not_bubble_bobble_logo.png", *platform_);

	//PLAY TEXTURE
	//Green
	play_tex[0] = CreateTextureFromPNG("textures/green_play.png", *platform_);

	//Red
	play_tex[1] = CreateTextureFromPNG("textures/red_play.png", *platform_);


	//CONTROLS TEXTURE
	//Green
	controls_tex[0] = CreateTextureFromPNG("textures/green_controls.png", *platform_);

	//Red
	controls_tex[1] = CreateTextureFromPNG("textures/red_controls.png", *platform_);


	//OPTIONS TEXTURE
	//Green
	options_tex[0] =CreateTextureFromPNG("textures/green_options.png", *platform_);
	
	//Red
	options_tex[1] = CreateTextureFromPNG("textures/red_options.png", *platform_);

}

//Set Up Textured Sprites
void MainMenuState::SetUpTexturedSprites()
{
	//Logo Sprite
	logo_.set_texture(logo_tex);
	logo_.set_position({ float(platform_->width() / 2),float(platform_->height() / 3.5),0 });
	logo_.set_height(290);
	logo_.set_width(450);

	//Play Sprite
	play_.set_texture(play_tex[0]);
	play_.set_position({ float(platform_->width() / 2),float(platform_->height())-float(platform_->height() / 4) ,0 });
	play_.set_height(120);
	play_.set_width(120);

	//Options Sprite
	options_.set_texture(options_tex[1]);
	options_.set_position({ float(platform_->width()/4),float(platform_->height()) - float(platform_->height() / 4) ,0 });
	options_.set_height(80);
	options_.set_width(80);

	//Controls Sprite
	controls_.set_texture(controls_tex[1]);
	controls_.set_position({ float(platform_->width()) - float(platform_->width() / 4),float(platform_->height()) - float(platform_->height() / 4) ,0 });
	controls_.set_height(80);
	controls_.set_width(80);
}

