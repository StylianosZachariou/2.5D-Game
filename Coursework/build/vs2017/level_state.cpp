#include "level_state.h"
#include "state_machine.h"

//Initialise
void LevelState::Init(gef::Platform* platform, PrimitiveBuilder* primitive_builder, gef::SpriteRenderer* sprite_renderer, gef::InputManager* input_manager, gef::Renderer3D* renderer_3d,gef::AudioManager* audio_manager, const gef::SonyController* controller, StateMachine* state_machine)
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

	//Initialise Font
	InitFont();

	// initialise the physics world
	b2Vec2 gravity(0.0f, -9.81f);
	world_ = new b2World(gravity);

	//Lights
	SetupLights();

	//Player
	SetUpPlayer();

	//Fruits
	SetUpFruits();

	//Background
	SetUpBackground();

	//Init Level
	level.Init(primitive_builder, world_, *platform_);

	//Init Camera
	camera_.Init({ 0.0f, -1.0f, 30 });

	//Enemy Manager
	enemy_manager.Init(level.spawn_points);
	SetUpEnemies();

	//HUD
	InitSprites();
}

//Clean Up Level State
void LevelState::CleanUp()
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

	delete world_;
	world_ = NULL;

	bubble_manager.CleanUp();
	level.CleanUp();
	enemy_manager.CleanUp();
	fruit_manager.CleanUp();
	CleanUpFont();
}

//Update
bool LevelState::Update(float dt)
{
	//Keyboard Input
	//Pause Game
	if (input_manager_->keyboard()->IsKeyPressed(gef::Keyboard::KC_P) || (controller_->buttons_pressed() & gef_SONY_CTRL_SELECT))
	{
		state_machine_->changeGameState(PAUSE);
	}

	//Walk Right
	if (input_manager_->keyboard()->IsKeyDown(gef::Keyboard::KC_RIGHT) || (controller_->left_stick_x_axis() >0))
	{
		player.walk(true, dt);
	}

	//Walk left
	if (input_manager_->keyboard()->IsKeyDown(gef::Keyboard::KC_LEFT) || (controller_->left_stick_x_axis() < 0))
	{
		player.walk(false, dt);
	}

	//Jumb
	if (input_manager_->keyboard()->IsKeyPressed(gef::Keyboard::KC_UP) || (controller_->buttons_pressed() & gef_SONY_CTRL_CROSS))
	{
		if (player.jumb())
		{
			audio_manager_->PlaySample(0, false);
		}
	}
	//Shoot
	if (input_manager_->keyboard()->IsKeyPressed(gef::Keyboard::KC_SPACE) || (controller_->buttons_pressed() & gef_SONY_CTRL_SQUARE))
	{
		if (player.fire())
		{
			//Create Bubble
			bubble_manager.CreateNewBubble(primitive_builder_, world_, player.body->GetPosition(), player.object_size.x, player.lookRight);
			audio_manager_->PlaySample(6, false);
		}
	}

	//If Player Is Dead
	if (player.GetHealth() <=0 )
	{
		state_machine_->score = player.GetScore();
		state_machine_->changeGameState(DEATH);
	}

	//If enemies are dead
	if (enemy_manager.isFinished)
	{
		//increament wave and create enemies
		wave++;
		enemy_manager.CreateEnemies(world_,wave);
	}
	//Update Everything

	UpdateSimulation(dt);
	camera_.Update(*platform_, renderer_3d_);
	UpdateHud();
	return true;
}

void LevelState::Render()
{
	//Render 3D Geometry
	renderer_3d_->Begin();

	//Background
	renderer_3d_->set_override_material(&background_material);
	renderer_3d_->DrawMesh(background_mesh);
	renderer_3d_->set_override_material(NULL);

	fruit_manager.Render(renderer_3d_);
	player.Render(renderer_3d_);
	enemy_manager.Render(renderer_3d_);
	bubble_manager.RenderBubbles(renderer_3d_);
	level.Render(renderer_3d_, *platform_);

	renderer_3d_->End();

	// start drawing sprites, but don't clear the frame buffer
	sprite_renderer_->Begin(false);
	RenderHud();
	sprite_renderer_->End();
}

//On Exit
void LevelState::onExit()
{
	//Reset managers
 	bubble_manager.Reset(world_);
	enemy_manager.Reset(world_);
	fruit_manager.Reset(world_);
	//Reset Player
	player.ResetPlayer();
	///Reset Waves
	wave = 1;
	enemy_manager.CreateEnemies(world_, wave);

}
//On Enter
void LevelState::OnEnter()
{
	//Play Level Music
	audio_manager_->LoadMusic("sfx/level_music.wav", *platform_);
	audio_manager_->PlayMusic();
}
//Get Player Score
int LevelState::GetScore()
{
	return player.GetScore();
}
//Set Up Lights
void LevelState::SetupLights()
{
	// grab the data for the default shader used for rendering 3D geometry
	gef::Default3DShaderData& default_shader_data = renderer_3d_->default_shader_data();

	// set the ambient light
	default_shader_data.set_ambient_light_colour(gef::Colour(0.25f, 0.25f, 0.25f, 1.0f));

	// add a point light that is almost white, but with a blue tinge
	// the position of the light is set far away so it acts light a directional light
	gef::PointLight default_point_light;

	default_point_light.set_colour(gef::Colour(1.0f, 1.0f, 1.0f, 1.0f));
	default_point_light.set_position(gef::Vector4(0.0f, 0.0f, 45.0f));
	default_shader_data.AddPointLight(default_point_light);
}

//Update Simulation
void LevelState::UpdateSimulation(float frame_time)
{
	// update physics world
	float timeStep = 1.0f / 60.0f;

	int32 velocityIterations = 6;
	int32 positionIterations = 2;
	world_->Step(timeStep, velocityIterations, positionIterations);


	// update objects
	player.Update(frame_time, level.maxY, level.minY);
	enemy_manager.Update(frame_time, { player.body->GetPosition().x, player.body->GetPosition().y }, level.maxY, level.minY,world_);
	bubble_manager.Update(frame_time, level.maxY, level.minY);
	fruit_manager.Update(frame_time, level.maxY, level.minY);

	// collision detection
	// get the head of the contact list
	b2Contact* contact = world_->GetContactList();
	// get contact count
	int contact_count = world_->GetContactCount();

	for (int contact_num = 0; contact_num < contact_count; ++contact_num)
	{
		if (contact->IsTouching())
		{
			// get the colliding bodies
			b2Body* bodyA = contact->GetFixtureA()->GetBody();
			b2Body* bodyB = contact->GetFixtureB()->GetBody();

			// DO COLLISION RESPONSE HERE

			GameObject* gameObjectA = NULL;
			GameObject* gameObjectB = NULL;

			gameObjectA = reinterpret_cast<GameObject*>(bodyA->GetUserData().pointer);
			gameObjectB = reinterpret_cast<GameObject*>(bodyB->GetUserData().pointer);

			if (gameObjectA && gameObjectB)
			{
				//ENEMY & BUBBLE COLLISION
				if (gameObjectA->type() == ENEMY && gameObjectB->type() == BUBBLE)
				{
					Enemy* enemyObj = reinterpret_cast<Enemy*>(bodyA->GetUserData().pointer);
					Bubble* bubbleObj = reinterpret_cast<Bubble*>(bodyB->GetUserData().pointer);

					if (!(bubbleObj->isFull) && !(enemyObj->captured) && (bubbleObj->isEnabled))
					{
						//CONNECT BUBBLE AND ENEMY
						bubbleObj->isFull = true;
						enemyObj->CollisionBubble(bubbleObj);
						audio_manager_->PlaySample(5,false);
					}
				}
				else
				{
					if (gameObjectA->type() == BUBBLE && gameObjectB->type() == ENEMY)
					{
						Enemy* enemyObj = reinterpret_cast<Enemy*>(bodyB->GetUserData().pointer);
						Bubble* bubbleObj = reinterpret_cast<Bubble*>(bodyA->GetUserData().pointer);

						if (!(bubbleObj->isFull) && !(enemyObj->captured) && (bubbleObj->isEnabled))
						{
							//CONNECT BUBBLE AND ENEMY
							bubbleObj->isFull = true;
							enemyObj->CollisionBubble(bubbleObj);
							audio_manager_->PlaySample(5, false);
						}
					}
				}

				//PLAYER & ENEMY
				if (gameObjectA->type() == PLAYER && gameObjectB->type() == ENEMY)
				{
					Player* playerObj = reinterpret_cast<Player*>(bodyA->GetUserData().pointer);
					//Decrement Health
					playerObj->DecreaseHealth();

					//If Is Not playeing already
					if (!audio_manager_->sample_voice_playing(3))
					{
						//play sound effect
						audio_manager_->PlaySample(3, false);
					}
					break;
				}

				//PLAYER & FRUIT COLLISION
				if (gameObjectA->type() == FRUIT && gameObjectB->type() == PLAYER)
				{
					Player* playerObj = reinterpret_cast<Player*>(bodyB->GetUserData().pointer);
					Fruit* fruitObj = reinterpret_cast<Fruit*>(bodyA->GetUserData().pointer);

					//increase score and delete fruit
					playerObj->IncreaseScore(fruitObj->fruit_type());
					fruit_manager.DeleteFruit(fruitObj->personal_id, world_);
					//play sound effect
					audio_manager_->PlaySample(4, false);
					break;
				}

				//PLAYER & BUBBLE COLLISION
				if (gameObjectA->type() == PLAYER && gameObjectB->type() == BUBBLE)
				{
					Bubble* bubbleObj = reinterpret_cast<Bubble*>(bodyB->GetUserData().pointer);

					//Check If Bubble is EMpty and Enable
					if (!bubbleObj->isEnabled)
					{
						
						if (bubbleObj->isFull)
						{
							//Destroy Enemy
							enemy_manager.FindAndDestroy(world_, bubbleObj->personal_id);
							fruit_manager.CreateFruit(primitive_builder_, world_, { bubbleObj->body->GetPosition().x, bubbleObj->body->GetPosition().y });
						}
						//Pop Bubble
						bubble_manager.CollisionPop(*bubbleObj, world_);
					}
					break;
				}

			}
		}
		// Get next contact point
		contact = contact->GetNext();
	}

}

//Set Up Player
void LevelState::SetUpPlayer()
{
	//Animation
	player.animation.AddFrame(LoadAsset("dino_models/dino-walk0.scn"));
	player.animation.AddFrame(LoadAsset("dino_models/dino-walk1.scn"));
	player.animation.AddFrame(LoadAsset("dino_models/dino-walk2.scn"));
	player.dino_fire.set_mesh(LoadAsset("dino_models/dino-fire.scn"));
	//Initialise
	player.Init(world_, { 0,0 }, true);
}

//Set Up Enemies
void LevelState::SetUpEnemies()
{
	//Animations
	enemy_manager.enemy_animations[0].AddFrame(LoadAsset("enemy_models/zenChan.scn"));
	enemy_manager.enemy_animations[0].AddFrame(LoadAsset("enemy_models/zenChan2.scn"));
	enemy_manager.enemy_animations[1].AddFrame(LoadAsset("enemy_models/monsta.scn"));
	enemy_manager.enemy_animations[1].AddFrame(LoadAsset("enemy_models/monsta2.scn"));
	enemy_manager.enemy_animations[2].AddFrame(LoadAsset("enemy_models/maita.scn"));
	enemy_manager.enemy_animations[2].AddFrame(LoadAsset("enemy_models/maita2.scn"));
	//Create Enemies
	enemy_manager.CreateEnemies(world_, wave);
}
//Set Up Fruits
void LevelState::SetUpFruits()
{
	fruit_manager.fruit_mesh.set_mesh(LoadAsset("fruit_models/cherry.scn"));
}
//Set Up Background
void LevelState::SetUpBackground()
{
	//Set Up background
	background_material.set_texture(CreateTextureFromPNG("textures/background_texture.png", *platform_));
	//Matrix
	gef::Matrix44 translation;
	translation.SetIdentity();
	translation.SetTranslation({ 0,0,-3 });
	background_mesh.set_transform(translation);
	background_mesh.set_mesh(primitive_builder_->CreateBoxMesh({ 22,22,0.5 }));
}

//Initialise Sprites
void LevelState::InitSprites()
{
	//Initialise Textures
	heart_texture =CreateTextureFromPNG("textures/dino_heart.png", *platform_);
	dead_heart_texture = CreateTextureFromPNG("textures/dino_heart_dead.png", *platform_);

	//Initialise Sprites
	for (int i = 0; i < player.GetHealth(); i++)
	{
		gef::Sprite* heart = new gef::Sprite;
		heart->set_texture(heart_texture);
		heart->set_height(40);
		heart->set_width(40);
		heart->set_position({ heart->width() * i + heart->width() / 2,platform_->height() - (heart->height() / 2),0 });
		hearts.push_back(*heart);
	}
}

//Update HUD
void LevelState::UpdateHud()
{
	//Update Hearts from players health
	for (int i = 0; i < hearts.size(); i++)
	{
		if (i >= player.GetHealth())
		{
			hearts[i].set_texture(dead_heart_texture);
		}
		else
		{
			hearts[i].set_texture(heart_texture);
		}
	}
}

//Render HUD
void LevelState::RenderHud()
{
	//Hearts
	for (int i = 0; i < hearts.size(); i++)
	{
		sprite_renderer_->DrawSprite(hearts[i]);
	}

	//Score
	if (font_)
	{
		// display frame rate
		font_->RenderText(sprite_renderer_, gef::Vector4(0.0f, 0.0f, 0.f), 0.7f, 0xffffffff, gef::TJ_LEFT, "SCORE: %i", player.GetScore());
	}
}
