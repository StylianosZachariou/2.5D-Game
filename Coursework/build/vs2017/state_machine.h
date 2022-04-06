#pragma once
#include "level_state.h"
#include "main_menu_state.h"
#include "controls_state.h"
#include "pause_state.h"
#include "death_state.h"
#include "options_state.h"
#include <input/sony_controller_input_manager.h>

//States
enum GAME_STATE { MENU, LEVEL, OPTIONS, CONTROLS, PAUSE, DEATH };

//State Machine Class
class StateMachine
{
public:
	//Initialise
	void Init(gef::Platform* platform,
		PrimitiveBuilder* primitive_builder,
		gef::SpriteRenderer* sprite_renderer,
		gef::InputManager* input_manager,
		gef::Renderer3D* renderer_3d,
		gef::AudioManager* audio_manager);
	//Change State
	void changeGameState(GAME_STATE next_stage);
	//Clean Up
	void CleanUp();
	//Score
	int score = -1;
	
	//Current State
	State* current_state = &main_menu_state;
private:
	
	//States
	MainMenuState main_menu_state;
	LevelState level_state;
	ControlsState controls_state;
	PauseState pause_state;
	DeathState death_state;
	OptionsState options_state;
};

