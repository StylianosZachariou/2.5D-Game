#pragma once
#include "state.h"
#include "player.h"
#include "enemy_manager.h"
#include "bubble_manager.h"
#include "fruit_manager.h"
#include "main_camera.h"
#include "level.h"
#include <graphics/texture.h>
#include <graphics/sprite.h>
//Level State Class
class LevelState: public State
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
	//Clean Up State
	void CleanUp() override ;
	//Update
	bool Update(float dt) override;
	//Render
	void Render() override;
	//On Exit and Enter
	void onExit() override;
	void OnEnter() override;
	//Get Score
	int GetScore();
private:
	//Set Up Lights
	void SetupLights();
	//Update Physics Simulation
	void UpdateSimulation(float frame_time);

	// create the physics world
	b2World* world_;

	//Player
	Player player;
	void SetUpPlayer();

	//Enemies
	EnemyManager enemy_manager;
	void SetUpEnemies();

	//Bubbles
	BubbleManager bubble_manager;

	//Fruits
	FruitManager fruit_manager;
	void SetUpFruits();

	//Camera
	MainCamera camera_;

	//Level
	Level level;

	//Background
	void SetUpBackground();
	gef::Material background_material;
	gef::MeshInstance background_mesh;

	//Wave
	int wave = 1;

	//HUD]
	gef::Texture* heart_texture;
	gef::Texture* dead_heart_texture;
	std::vector<gef::Sprite> hearts;
	void InitSprites();
	void UpdateHud();
	void RenderHud();

};

