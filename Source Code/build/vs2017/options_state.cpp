#include "options_state.h"
#include <system/platform.h>
#include <graphics/image_data.h>
#include "state_machine.h"

//Initialise
void OptionsState::Init(gef::Platform* platform, PrimitiveBuilder* primitive_builder, gef::SpriteRenderer* sprite_renderer, gef::InputManager* input_manager, gef::Renderer3D* renderer_3d, gef::AudioManager* audio_manager, const gef::SonyController* controller, StateMachine* state_machine)
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

	//Textures
	SetUpTextures();
	//Sprites
	SetUpTexturedSprites();
	SetUpBackground();
	//Font
	InitFont();
}

//Clean Up
void OptionsState::CleanUp()
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

	for (int i = 0; i < 3; i++)
	{
		delete volume_tex[i];
		volume_tex[i] = NULL;
		delete sounds_tex[i];
		sounds_tex[i] = NULL;
	}

	for (int i = 0; i < 2; i++)
	{
		delete inc_tex[i];
		inc_tex[i] = NULL;
		delete dec_tex[i];
		dec_tex[i] = NULL;
	}
}

//Update
bool OptionsState::Update(float dt)
{
	//If Left stick is released
	if (controller_->left_stick_x_axis() == 0)
	{
		left_stick_released_x = true;
	}

	//If Left stick is released
	if (controller_->left_stick_y_axis() == 0)
	{
		left_stick_released_y = true;
	}

	//Volume or Sound Effect Choice
	if (input_manager_->keyboard()->IsKeyPressed(gef::Keyboard::KC_UP) || input_manager_->keyboard()->IsKeyPressed(gef::Keyboard::KC_DOWN) || (left_stick_released_y && left_stick_released_x&& !(controller_->left_stick_y_axis()==0)))
	{
		//Left Stick Is Hold
		left_stick_released_y = false;
		left_stick_released_x = false;
		//PLay sound effect
		audio_manager_->PlaySample(2, false);
		if (choice == 1)
		{
			volumeChange = !volumeChange;
		}
	}

	//Right CHOICE
	if (input_manager_->keyboard()->IsKeyPressed(gef::Keyboard::KC_RIGHT) || (left_stick_released_x && (controller_->left_stick_x_axis() > 0)))
	{
		//Left Stick Is Hold
		left_stick_released_x = false;
		//PLay sound effect
		audio_manager_->PlaySample(2, false);
		choice++;
		if (choice > 2)
		{
			choice = 0;
		}
	}

	//Left CHOICE
	if (input_manager_->keyboard()->IsKeyPressed(gef::Keyboard::KC_LEFT) || (left_stick_released_x && (controller_->left_stick_x_axis() < 0)))
	{
		//Left Stick Is Hold
		left_stick_released_x = false;

		//PLay sound effect
		audio_manager_->PlaySample(2, false);
		choice--;
		if (choice < 0)
		{
			choice = 2;
		}
	}

	//Lock Choice
	if (input_manager_->keyboard()->IsKeyPressed(gef::Keyboard::KC_SPACE) || (controller_->buttons_pressed() & gef_SONY_CTRL_CROSS))
	{
		audio_manager_->PlaySample(2, false);
		gef::VolumeInfo volumeInfo;
		if (choice == 0)
		{
			if (volumeChange)
			{
				//DECREMENT MUSIC VOLUME
				audio_manager_->GetMusicVolumeInfo(volumeInfo);
				volumeInfo.volume-= 20;
				if (volumeInfo.volume < 0)
				{
					volumeInfo.volume =0;
				}
				audio_manager_->SetMusicVolumeInfo(volumeInfo);
			}
			else
			{
				for (int i = 0; i < 7; i++)
				{
					//DECREMENT SOUNDS VOLUME
					audio_manager_->GetSampleVoiceVolumeInfo(i, volumeInfo);
					volumeInfo.volume -= 20;
					if (volumeInfo.volume < 0)
					{
						volumeInfo.volume = 0;
					}
					audio_manager_->SetSampleVoiceVolumeInfo(i, volumeInfo);
				}
			}
		}
		else
		{
			if (choice == 2)
			{
				if (volumeChange)
				{
					//INCREMENT  MUSIC VOLUME
					audio_manager_->GetMusicVolumeInfo(volumeInfo);
					volumeInfo.volume += 20;
					if (volumeInfo.volume > 100)
					{
						volumeInfo.volume = 100;
					}
					audio_manager_->SetMusicVolumeInfo(volumeInfo);

				}
				else
				{
					for (int i = 0; i < 7; i++)
					{
						//INCREMENT SOUND VOLUME
						audio_manager_->GetSampleVoiceVolumeInfo(i, volumeInfo);
						volumeInfo.volume += 20 ;
						if (volumeInfo.volume > 100)
						{
							volumeInfo.volume = 100;
						}
						audio_manager_->SetSampleVoiceVolumeInfo(i, volumeInfo);
					}
				}
			}
		}
		
	}
	//Go Back to Menu
	if (input_manager_->keyboard()->IsKeyPressed(gef::Keyboard::KC_ESCAPE) || (controller_->buttons_pressed() & gef_SONY_CTRL_CIRCLE))
	{
		state_machine_->changeGameState(MENU);
	}

	ChangeSprites();
	return true;
}

//Render
void OptionsState::Render()
{
	sprite_renderer_->Begin();

	//Draw Sprites
	sprite_renderer_->DrawSprite(background);
	sprite_renderer_->DrawSprite(volume);
	sprite_renderer_->DrawSprite(sounds);
	sprite_renderer_->DrawSprite(plus);
	sprite_renderer_->DrawSprite(minus);

	//Draw Text
	font_->RenderText(sprite_renderer_, { 0,float(platform_->height())-22,0 }, 0.6f, 0xFFFFFFFF, gef::TJ_LEFT, "%s", "Press ESC or O To Go Back");

	sprite_renderer_->End();
}

//Set Up Textured Sprites
void OptionsState::SetUpTexturedSprites()
{
	//Volume Sprite
	volume.set_texture(volume_tex[0]);
	volume.set_position({ float(platform_->width() / 2),float(platform_->height() / 2)-float(platform_->height()/7),0 });
	volume.set_height(160);
	volume.set_width(160);

	//Sounds Sprite
	sounds.set_texture(sounds_tex[2]);
	sounds.set_position({ float(platform_->width() / 2),float(platform_->height() / 2) + float(platform_->height() / 7) ,0 });
	sounds.set_height(120);
	sounds.set_width(120);

	//Plus Sprite
	plus.set_texture(inc_tex[1]);
	plus.set_position({ volume.position().x() + float(platform_->width() / 4),volume.position().y() ,0 });
	minus.set_height(80);
	plus.set_width(80);

	//Minus Sprite
	minus.set_texture(dec_tex[1]);
	minus.set_position({ volume.position().x() - float(platform_->width() / 4),volume.position().y() ,0 });	plus.set_height(80);
	minus.set_height(80);
	minus.set_width(80);
	
}

//Change Sprites depending on choice
void OptionsState::ChangeSprites()
{
	if (choice == 1)	//If CHOICE FOR VOLUME OR SOUND
	{
		plus.set_texture(inc_tex[1]);
		plus.set_width(80);
		plus.set_height(80);
		minus.set_texture(dec_tex[1]);
		minus.set_width(80);
		minus.set_height(80);

		if (volumeChange) //IF VOLUME
		{
			volume.set_texture(volume_tex[0]);
			volume.set_height(160);
			volume.set_width(160);
			sounds.set_texture(sounds_tex[2]);
			sounds.set_height(120);
			sounds.set_width(120);
			plus.set_position({ volume.position().x() + float(platform_->width() / 4),volume.position().y() ,0 });
			minus.set_position({ volume.position().x() - float(platform_->width() / 4),volume.position().y() ,0 });
		}
		else    //IF SOUND
		{
			volume.set_texture(volume_tex[2]);
			volume.set_height(120);
			volume.set_width(120);
			sounds.set_texture(sounds_tex[0]);
			sounds.set_height(160);
			sounds.set_width(160);
			plus.set_position({ sounds.position().x() + float(platform_->width() / 4),sounds.position().y() ,0 });
			minus.set_position({ sounds.position().x() - float(platform_->width() / 4),sounds.position().y() ,0 });
		}
	}
	else
	{
		if (volumeChange)
		{
			volume.set_texture(volume_tex[1]);
		}
		else
		{
			sounds.set_texture(sounds_tex[1]);
		}
		
		if (choice == 2)	//IF PLUS
		{
		
			plus.set_texture(inc_tex[0]);
			plus.set_width(120);
			plus.set_height(120);
			minus.set_texture(dec_tex[1]);
			minus.set_width(80);
			minus.set_height(80);
		}
		else        ///IF MINUS
		{
			minus.set_texture(dec_tex[0]);
			minus.set_width(120);
			minus.set_height(120); 
			plus.set_texture(inc_tex[1]);
			plus.set_width(80);
			plus.set_height(80);
		}
	}
}

//Set Up Background
void OptionsState::SetUpBackground()
{
	background.set_colour(0xFF000000);
	background.set_height(platform_->height());
	background.set_width(platform_->width());
	background.set_position({ float(platform_->width() / 2),float(platform_->height() / 2),0 });
}

//Set Up Textures
void OptionsState::SetUpTextures()
{
	//Initialise Textures

	//VOLUME TEXTURE
	//Green
	volume_tex[0] = CreateTextureFromPNG("textures/volume_green.png", *platform_);

	//Blue
	volume_tex[1] = CreateTextureFromPNG("textures/volume_blue.png", *platform_);


	//Red
	volume_tex[2] = CreateTextureFromPNG("textures/volume_red.png", *platform_);



	//SOUNDS TEXTURE
	//Green
	sounds_tex[0] = CreateTextureFromPNG("textures/sounds_green.png", *platform_);

	//Blue
	sounds_tex[1] = CreateTextureFromPNG("textures/sounds_blue.png", *platform_);


	//Red
	sounds_tex[2] = CreateTextureFromPNG("textures/sounds_red.png", *platform_);

	//+ TEXTURE
	//Green
	inc_tex[0] = CreateTextureFromPNG("textures/+_green.png", *platform_);

	//Red
	inc_tex[1] = CreateTextureFromPNG("textures/+_red.png", *platform_);

	//- TEXTURE
	//Green
	dec_tex[0] = CreateTextureFromPNG("textures/-_green.png", *platform_);

	//Red
	dec_tex[1] = CreateTextureFromPNG("textures/-_red.png", *platform_);
}
