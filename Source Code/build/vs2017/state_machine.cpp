#include "state_machine.h"
//Initialise
void StateMachine::Init(gef::Platform* platform, PrimitiveBuilder* primitive_builder, gef::SpriteRenderer* sprite_renderer, gef::InputManager* input_manager, gef::Renderer3D* renderer_3d, gef::AudioManager* audio_manager)
{
	//Controller Input
	gef::SonyControllerInputManager* controllerManager = input_manager->controller_input();
	const gef::SonyController* controller = controllerManager->GetController(0);

	//INITIALISE ALL STATES
	level_state.Init(platform, primitive_builder, sprite_renderer, input_manager, renderer_3d,audio_manager,controller,this);
	main_menu_state.Init(platform, primitive_builder, sprite_renderer, input_manager, renderer_3d, audio_manager, controller, this);
	controls_state.Init(platform, primitive_builder, sprite_renderer, input_manager, renderer_3d, audio_manager, controller, this);
	pause_state.Init(platform, primitive_builder, sprite_renderer, input_manager, renderer_3d, audio_manager, controller, this);
	death_state.Init(platform, primitive_builder, sprite_renderer, input_manager, renderer_3d, audio_manager, controller, this);
	options_state.Init(platform, primitive_builder, sprite_renderer, input_manager, renderer_3d, audio_manager, controller, this);
	changeGameState(MENU);
}
//Change state
void StateMachine::changeGameState(GAME_STATE next_stage)
{
	if (!(current_state == &level_state && (next_stage == PAUSE)))
	{
		current_state->onExit();
	}

	switch (next_stage)
	{
	case MENU:
		current_state = &main_menu_state;
		break;
	
	case LEVEL:
		current_state = &level_state;
		break;

	case CONTROLS:
		current_state = &controls_state;
		break;

	case PAUSE:
		current_state = &pause_state;
		break;

	case DEATH:
		death_state.SetScore(score);
		current_state = &death_state;
		break;

	case OPTIONS:
		current_state = &options_state;
		break;
	}
	current_state->OnEnter();
}
//Clean up All States
void StateMachine::CleanUp()
{
	main_menu_state.CleanUp();
	level_state.CleanUp();
	controls_state.CleanUp();
	pause_state.CleanUp();
	death_state.CleanUp();
	options_state.CleanUp();
}
