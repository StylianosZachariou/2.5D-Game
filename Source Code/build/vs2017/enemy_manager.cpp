#include "enemy_manager.h"
#include "monsta.h"
#include "maita.h"
#include <time.h>

//Initialise
void EnemyManager::Init(gef::Vector2 spawn_pos[])
{
	//Randomise
	srand(time(0));
	for (int i = 0; i < 9; i++)
	{
		spawn_positions[i] = spawn_pos[i];
	}
}

//Create enemies depending on the wave
void EnemyManager::CreateEnemies(b2World* world, int wave)
{
	//Clear all enemies
	enemies.clear();
	for (int i = 0; i < wave; i++)
	{
		//Random Position and Enemy
		int random_position = rand() % 9;
		int random_enemy = rand() % 3;

		//If Zen Chan Enemy
		if (random_enemy == 0)
		{
			//Initialise
			ZenChan* newZen = new ZenChan;
			newZen->animation = enemy_animations[0];
			newZen->Init(world, spawn_positions[random_position], false);
			if (i % 2 == 0)
			{
				newZen->velocity = -newZen->velocity;
			}
			enemies.push_back(newZen);
		}
		else
		{
			//If MOnsta Enemy
			if (random_enemy == 1)
			{
				//Intilaise
				Monsta* newMonsta = new Monsta;
				newMonsta->animation = enemy_animations[1];
				newMonsta->Init(world, spawn_positions[random_position], false);
				if (i % 2 == 0)
				{
					newMonsta->velocity.x = -newMonsta->velocity.x;
				}
				enemies.push_back(newMonsta);
			}
			else
			{
				//If Maita Enemy
				//Initialise
				Maita* newMaita = new Maita;
				newMaita->animation = enemy_animations[2];
				newMaita->Init(world, spawn_positions[random_position], false);
				enemies.push_back(newMaita);

			}
		}
		
	}
}

//Update
void EnemyManager::Update(float dt, gef::Vector2 player_pos, float maxY, float minY, b2World* world)
{
	//Check If Wave Is Finished
	isFinished = true;
	for (int i = 0; i < enemies.size(); i++)
	{
		if (!(enemies[i] == NULL))
		{
			isFinished = false;
			//If Not Update Enemies
			if (enemies[i]->enemy_type() == ZEN_CHAN)
			{
				//Update Zen Chan
				ZenChan* zenChan = reinterpret_cast<ZenChan*>(enemies[i]->body->GetUserData().pointer);
				zenChan->Update(dt, maxY,minY);
			}
			else
			{
				if (enemies[i]->enemy_type() == MONSTA)
				{
					//Update Monsta
					Monsta* monsta = reinterpret_cast<Monsta*>(enemies[i]->body->GetUserData().pointer);
					monsta->Update(dt, maxY, minY);
				}
				else
				{
					if(enemies[i]->enemy_type() == MAITA)
					{
						//Update Maita
						Maita* maita = reinterpret_cast<Maita*>(enemies[i]->body->GetUserData().pointer);
						maita->Update(dt,player_pos, maxY, minY);
					}
				}
			}
		}
	}
}

//Render
void EnemyManager::Render(gef::Renderer3D* renderer_3d_)
{
	//For All Enemies
	for (int i = 0; i < enemies.size(); i++)
	{
		if (!(enemies[i] == NULL))
		{	
			//Render Enemy
			renderer_3d_->DrawMesh(*enemies[i]);
		}
	}
}

//Destroy Enemy
void EnemyManager::DestroyEnemy(Enemy* enemy, b2World* world)
{
	//Destroy Body and Mesh
	world->DestroyBody(enemy->body);
	enemy->set_mesh(NULL);
	delete enemy;
	enemy = NULL;
	
}

//Find AND Destroy
void EnemyManager::FindAndDestroy(b2World* world,int bubble_id)
{
	//Find Bubble from id
	for (int i = 0; i < enemies.size(); i++)
	{
		if (!(enemies[i] == NULL))
		{
			if (enemies[i]->captured)
			{
				if (enemies[i]->connect_bubble->personal_id == bubble_id)
				{
					//Destroy it
					DestroyEnemy(enemies[i], world);
					enemies[i] = NULL;
				}
			}
		}
	}
}

//Clean Up
void EnemyManager::CleanUp()
{
	for (int i = 0; i < enemies.size(); i++)
	{
		delete enemies[i];
		enemies[i] = NULL;
	}
	enemies.clear();
}

//Reset
void EnemyManager::Reset(b2World* world)
{
	for (int i = enemies.size()-1; i >= 0; i--)
	{
		if (!(enemies[i] == NULL))
		{
			//Destroy all enemies
			world->DestroyBody(enemies[i]->body);
			enemies[i]->set_mesh(NULL);
			delete enemies[i];
			enemies[i] = NULL;
		}
		enemies.pop_back();
	}
}
