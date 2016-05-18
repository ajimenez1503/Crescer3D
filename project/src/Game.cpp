#include "Game.h"

namespace Crescer3D
{
	// forward declaration of static members
	Player* Game::m_Player;
	std::list<Enemy*> Game::m_enemy_list;
	std::list<Food*> Game::m_food_list;

	Camera* Game::m_Camera;
	bool Game::gameNeedReset;
	GameStates Game::gameState;


	Game::Game()
		: System(SystemType::Sys_Game)
	{
		m_Player = new Player();
		m_Camera = new Camera();

		SetGameStateInit();

	}

	Game::~Game()
	{
		SafeDelete(m_Player);
		//SafeDelete(m_enemy_list);
		//SafeDelete(m_food_list);
		SafeDelete(m_Camera);
	}

	bool Game::Initialize()
	{



		HighScore::CalculateListScores();

			//The random number generator needs to be reseted every time a new game starts so the positions of all objects are different every time
		std::srand (time(NULL));

		//m_Player->setPosition(0.0,100.0,0.0);

		//Set the initial Position of the Player
		//Game::GetPlayer()->setPosition(0.0,Game::GetPlayer()->getRadius(),0.0);

		//Create an initial number of enemies
		m_enemy_list.clear();
		int number_of_enemies=10;
		for(int number_of_enemy=1; number_of_enemy<=number_of_enemies; number_of_enemy++)
		{
			Enemy* local_enemy=new Enemy();
			m_enemy_list.push_back( local_enemy);
		}



		//Create an initial number of food
		m_food_list.clear();
		int total_number_of_food=10;
		for(int number_of_food=1; number_of_food<=total_number_of_food; number_of_food++)
		{
			Food* local_food=new Food();
			m_food_list.push_back( local_food);
		}

		gameNeedReset=false;

		return true;
	}

	bool Game::Update()
	{
		if(IsStatePlay()==true)
		{


			//////
			// Check for Collision between objects
			/////
			for(std::list<Enemy*>::iterator list_iter = m_enemy_list.begin(), end=m_enemy_list.end(); list_iter != end; list_iter++)
			{
				Enemy* e = NULL;
				if(*list_iter)
					e = *list_iter;
				if(e)
				{
					if(m_Player->collision(e))
					{
						float player_weight=m_Player->getWeight();
						float enemy_weight=(*list_iter)->getWeight();
						if(player_weight>=enemy_weight)
						{
							m_Player->eat((*list_iter)->getWeight());
							HighScore::IncrementScore((*list_iter)->getWeight());
							list_iter=m_enemy_list.erase(list_iter);
						}
						else
						{
							Sound::playGameOverMusic();
							GameOver();
							return true;
						}

						Sound::playEatEnemyMusic();
						//Logger::Log("Player collision with enemy!");
					}
				}
			}


			for(std::list<Food*>::iterator list_iter = m_food_list.begin(), end=m_food_list.end(); list_iter !=end; list_iter++)
			{
				if(m_Player->collisionAABB(*list_iter))
				{
					m_Player->eat((*list_iter)->getWeight());
					HighScore::IncrementScore((*list_iter)->getWeight());

					list_iter=m_food_list.erase(list_iter);
					Sound::playEatFoodMusic();
					//Logger::Log("Player collision with food!");
				}
			}

			for(std::list<Enemy*>::iterator outer_enemy_list_iter = m_enemy_list.begin(), end=m_enemy_list.end(); outer_enemy_list_iter  !=end; outer_enemy_list_iter ++)
			{
				for(std::list<Enemy*>::iterator inner_enemy_list_iter  = m_enemy_list.begin(), end=m_enemy_list.end(); inner_enemy_list_iter  !=end; inner_enemy_list_iter ++)
				{
					if((*outer_enemy_list_iter)!=(*inner_enemy_list_iter))
					{
						if((*outer_enemy_list_iter)->collision(*inner_enemy_list_iter))
						{
							Enemy* bigger_enemy;
							Enemy* smaller_enemy;


							if((*outer_enemy_list_iter)->getWeight()>=(*inner_enemy_list_iter)->getWeight())
							{
								bigger_enemy=(*outer_enemy_list_iter);
								smaller_enemy=(*inner_enemy_list_iter);

								bigger_enemy->eat(smaller_enemy->getWeight());
								bigger_enemy->setGoalState(undefined);
								inner_enemy_list_iter=m_enemy_list.erase(inner_enemy_list_iter);

							}else
							{
								bigger_enemy=(*inner_enemy_list_iter);
								smaller_enemy=(*outer_enemy_list_iter);

								bigger_enemy->eat(smaller_enemy->getWeight());
								bigger_enemy->setGoalState(undefined);
								outer_enemy_list_iter=m_enemy_list.erase(outer_enemy_list_iter);
							}

							//Logger::Log("Enemy collision with enemy!");

						}
					}
				}

				for(std::list<Food*>::iterator food_list_iter = m_food_list.begin(), end=m_food_list.end(); food_list_iter !=end; food_list_iter++)
				{
					if((*outer_enemy_list_iter)->collisionAABB(*food_list_iter))
					{
						(*outer_enemy_list_iter)->eat((*food_list_iter)->getWeight());
						(*outer_enemy_list_iter)->setGoalState(undefined);
						food_list_iter=m_food_list.erase(food_list_iter);

						//Logger::Log("Enemy collision with food!");
					}
				}
			}


			//Move Player

			GetCamera()->moveForwardPlayer();



			//////
			// Define what enemies are doing
			/////
			for(std::list<Enemy*>::iterator list_iter = m_enemy_list.begin(), end=m_enemy_list.end(); list_iter !=end; list_iter++)
			{
				//Iterate over all enemies

				if((*list_iter)->getWayWent()>40.0)
				{
					(*list_iter)->setGoalState(undefined);
					(*list_iter)->setWayWent(0.0);

				}

				if((*list_iter)->getGoalState()==undefined||(*list_iter)->getGoalState()==explore)
				{
					float positionx=(*list_iter)->getX();
					float positionz=(*list_iter)->getZ();

					float radius=(*list_iter)->getRadius();

					float radius_of_interest=5.0*radius;

					//Check for player in circle
					float player_positionx=m_Player->getX();
					float player_positionz=m_Player->getZ();

					float distance_to_player=sqrt(pow(player_positionx-positionx,2)+pow(player_positionz-positionz,2));


					if((distance_to_player<=radius_of_interest)&&(m_Player->getWeight()<(*list_iter)->getWeight()))
					{
						(*list_iter)->setGoalState(eat_player);
						//std::cout<< (*list_iter)->getID()<< ": eat_player"<<std::endl;
						continue;
					}

					//Check for food in circle
					Food* nearest_food=NULL;
					for(std::list<Food*>::iterator food_list_iter = m_food_list.begin(), end=m_food_list.end(); food_list_iter !=end; food_list_iter++)
					{

						float food_positionx=(*food_list_iter)->getX();
						float food_positionz=(*food_list_iter)->getZ();

						float distance_to_food=sqrt(pow(food_positionx-positionx,2)+pow(food_positionz-positionz,2));
						if(distance_to_food<=radius_of_interest)
						{
							if(nearest_food!=NULL)
							{
								if(distance_to_food>sqrt(pow((nearest_food)->getX()-positionx,2)+pow((nearest_food)->getZ()-positionz,2)))
								{

								}
								else
								{
									nearest_food=(*food_list_iter);
								}
							}
							else
							{
								nearest_food=(*food_list_iter);
							}
						}


					}
					if(nearest_food!=NULL)
					{
						(*list_iter)->setGoalState(eat_food);
						(*list_iter)->setTargetFood(nearest_food);
					}

					//Check for other Enemies in circle
					Enemy* nearest_enemy=NULL;
					for(std::list<Enemy*>::iterator other_enemy_list_iter = m_enemy_list.begin(), end=m_enemy_list.end(); other_enemy_list_iter !=end; other_enemy_list_iter++)
					{
						if((list_iter)!=(other_enemy_list_iter))
						{
							float positionx=(*list_iter)->getX();
							float positionz=(*list_iter)->getZ();
							float radius=(*list_iter)->getRadius();
							float weight=(*list_iter)->getWeight();

							float other_positionx=(*other_enemy_list_iter)->getX();
							float other_positionz=(*other_enemy_list_iter)->getZ();
							float other_radius=(*other_enemy_list_iter)->getRadius();
							float other_weight=(*other_enemy_list_iter)->getWeight();

							float distance_to_other=sqrt(pow(other_positionx-positionx,2)+pow(other_positionz-positionz,2));

							if(distance_to_other<=radius_of_interest)
							{
								if(nearest_enemy!=NULL)
								{
									if(distance_to_other<sqrt(pow(nearest_enemy->getX()-positionx,2)+pow(nearest_enemy->getZ()-positionz,2)));
									{
										nearest_enemy=(*other_enemy_list_iter);
									}
								}else
								{
									nearest_enemy=(*other_enemy_list_iter);
								}

							}
						}

					}
					if(nearest_enemy!=NULL)
					{
						(*list_iter)->setGoalState(eat_enemy);
						(*list_iter)->setTargetEnemy(nearest_enemy);
					}


					//If Goal state is still undefined, the enemy explores
					if((*list_iter)->getGoalState()==undefined)
					{
						(*list_iter)->setGoalState(explore);
						float movement_angle=rand() % 360;
						(*list_iter)->setMovementAngle(movement_angle);
					}

				}

				/////
				// Move Objects
				////


				//Handle the moving for the different enemy states
				if((*list_iter)->getGoalState()==eat_player)
				{
					float positionx=(*list_iter)->getX();
					float positionz=(*list_iter)->getZ();
					float target_positionx=m_Player->getX();
					float target_positionz=m_Player->getZ();

					float distance=sqrt(pow(target_positionx-positionx,2)+pow(target_positionz-positionz,2));
					float angle=atan2(target_positionz-positionz,target_positionx-positionx)* 180.0 / M_PI;


					//Move the enemy
					(*list_iter)->moveAngle(angle);
				}

				if((*list_iter)->getGoalState()==eat_food)
				{
					float positionx=(*list_iter)->getX();
					float positionz=(*list_iter)->getZ();
					float target_positionx=(*list_iter)->getTargetFood()->getX();
					float target_positionz=(*list_iter)->getTargetFood()->getZ();



					float distance=sqrt(pow(target_positionx-positionx,2)+pow(target_positionz-positionz,2));

					float angle=atan2(target_positionz-positionz,target_positionx-positionx)*180.0 / M_PI;


					(*list_iter)->moveAngle(angle);

				}



				if((*list_iter)->getGoalState()==eat_enemy)
				{
					float positionx=(*list_iter)->getX();
					float positionz=(*list_iter)->getZ();
					float target_positionx=(*list_iter)->getTargetEnemy()->getX();
					float target_positionz=(*list_iter)->getTargetEnemy()->getZ();



					float distance=sqrt(pow(target_positionx-positionx,2)+pow(target_positionz-positionz,2));

					float angle=atan2(target_positionz-positionz,target_positionx-positionx)*180.0 / M_PI;


					(*list_iter)->moveAngle(angle);
				}

				if((*list_iter)->getGoalState()==explore)
				{
					float movement_angle=(*list_iter)->getMovementAngle();
					(*list_iter)->moveAngle(movement_angle);

					float positionx=(*list_iter)->getX();
					float positionz=(*list_iter)->getZ();
					float radius=(*list_iter)->getRadius();


					vec3 worldMin = World::GetWorldMinimum();
					vec3 worldMax = World::GetWorldMaximum();

					bool valid_position=true;

					if(positionx>=worldMax.x-radius||positionx<=worldMin.x+radius)
					{
						valid_position=false;
					}
					if(positionz>=worldMax.y-radius||positionz<=worldMin.y+radius)
					{
						valid_position=false;
					}
					if(valid_position==false)
					{
						if(movement_angle>180.0)
						{
							movement_angle=movement_angle-180.0;
						}else
						{
							movement_angle=movement_angle+180.0;
						}
						(*list_iter)->moveAngle(movement_angle);
						(*list_iter)->setMovementAngle(movement_angle);
					}
				}
			}

			//////
			//Manage the Spawning of food and enemies
			/////
			int enemy_spawn_probability=rand()%100;
			if(m_enemy_list.size()<7)
			{
				if(enemy_spawn_probability<10)
				{
					spawnEnemy();
				}
			}else if(m_enemy_list.size()<15)
			{

				if(enemy_spawn_probability<3)
				{
					spawnEnemy();
				}
			}

			int food_spawn_probability=rand()%100;
			if(m_food_list.size()<20)
			{
				if(food_spawn_probability<5)
				{
					spawnFood();
				}
			}

		}

		return true;
	}




	bool Game::ShutDown()
	{
		return true;
	}


	Player* Game::GetPlayer()
	{
		return m_Player;
	}

	Camera* Game::GetCamera()
	{
		return m_Camera;
	}


	std::list<Enemy*> Game::GetEnemyList()
	{
		return m_enemy_list;
	}

	void Game::SetEnemyList(std::list<Enemy*> in_enemy_list)
	{
		m_enemy_list=in_enemy_list;
	}

	std::list<Food*> Game::GetFoodList()
	{
		return m_food_list;
	}

	void Game::SetFoodList(std::list<Food*> in_food_list)
	{
		m_food_list=in_food_list;
	}

	void Game::GameOver()
	{
		SetGameStateGameOver();
	}

	void Game::SetGameStatePlay()
	{
		gameState = Game_Play;
	}

	void Game::SetGameStateInit()
	{
		//gameNeedReset=true;
		gameState = Game_Init;
	}
	void Game::SetGameStateGameOver()
	{
		//std::cout <<  "Game over" << std::endl;
		gameState = Game_GameOver;
		gameNeedReset=true;
		ResetGame();
	}

	bool Game::IsStateInit()
	{
		return gameState==Game_Init;
	}
	bool Game::IsStatePlay()
	{
		return gameState==Game_Play;
	}
	bool Game::IsStateGameOver()
	{
		return gameState==Game_GameOver;
	}

	void Game::spawnEnemy()
	{
		//std::cout<<"Spawn Enemy"<<std::endl;
		Enemy* local_enemy=new Enemy();
		Window::InitEnemy(local_enemy);
		m_enemy_list.push_back(local_enemy);

	}

	void Game::spawnFood()
	{
		//std::cout<<"Spawn Food"<<std::endl;
		Food* local_food=new Food();
		Window::InitFood(local_food);
		m_food_list.push_back(local_food);
	}

	// set init all postion and reset all
	void Game::ResetGame()
	{
		if(gameNeedReset)
		{
			//std::cout <<  "Reset Game" << std::endl;
			HighScore::CalculateListScores();

			//The random number generator needs to be reseted every time a new game starts so the positions of all objects are different every time
			std::srand (time(NULL));


			m_Player = new Player();



			//Create an initial number of enemies
			m_enemy_list.clear();
			int number_of_enemies=10;
			for(int number_of_enemy=1; number_of_enemy<=number_of_enemies; number_of_enemy++)
			{
				Enemy* local_enemy=new Enemy();
				m_enemy_list.push_back( local_enemy);
			}



			//Create an initial number of food
			m_food_list.clear();
			int total_number_of_food=10;
			for(int number_of_food=1; number_of_food<=total_number_of_food; number_of_food++)
			{
				Food* local_food=new Food();
				m_food_list.push_back( local_food);
			}

			Window::InitAllObjects();

			gameNeedReset=false;
		}

	}

}
