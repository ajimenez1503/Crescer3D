
#include "Window.h"

namespace Crescer3D
{
	// forward declaration of static members
	World Window::m_World;
	mat4 Window::m_ProjMat;
	mat4 Window::m_DepthMat;
	GLuint Window::m_DepthBuffer;
	GLuint Window::m_DepthTexture;
	GLuint Window::m_DepthShader;
	GLuint Window::m_sphereShader;

	bool Window::m_CollisionState;
	int Window::m_Width;
	int Window::m_Height;


	Window::Window(char* title, int width, int height)
	: System(SystemType::Sys_Window)
	{
		m_Title = title;
		Window::SetWidth(width);
		Window::SetHeight(height);
	}

	Window::~Window()
	{}

	bool Window::Initialize()
	{
		m_CollisionState=false;
		glutInit(0, 0);
		glutInitDisplayMode(GLUT_DOUBLE | GLUT_DEPTH |  GLUT_RGB);
		glutInitContextVersion(3, 2);
		glutInitWindowSize (Window::GetWidth(), Window::GetHeight());
		glutCreateWindow (m_Title);
		glutDisplayFunc(Draw);

		glClearColor(0.2,0.2,0.5,0);
		glEnable(GL_DEPTH_TEST);
		glDisable(GL_CULL_FACE);
		printError("OpenGL Init");


		// Load and compile shader
		GLuint skyboxShader = loadShaders("shader/Shader_Skybox.vert", "shader/Shader_Skybox.frag");
		GLuint sphereShader = loadShaders("shader/Shader_Objects.vert", "shader/Shader_Objects.frag");
		m_sphereShader=sphereShader;
		GLuint groundShader = loadShaders("shader/Shader_Ground.vert", "shader/Shader_Ground.frag");
		GLuint wallShader = loadShaders("shader/Shader_Wall.vert", "shader/Shader_Wall.frag");
		m_DepthShader = loadShaders("shader/Shader_Depth.vert", "shader/Shader_Depth.frag");
		m_World.init(skyboxShader, groundShader, wallShader, m_DepthShader);
		vec3 worldMin = m_World.GetWorldMinimum();
		vec3 worldMax = m_World.GetWorldMaximum();
		m_ProjMat = frustum(-0.1, 0.1, -0.1, 0.1, 0.2, 1000.0);
		// Depth Map Orthographic Projection
		// left, right, bottom, top, near, far
		m_DepthMat = ortho(worldMin.x, worldMax.x, worldMin.x, worldMax.y, worldMin.x, worldMax.z);
		glUseProgram(skyboxShader);
		glUniformMatrix4fv(glGetUniformLocation(skyboxShader, "projMatrix"), 1, GL_TRUE, m_ProjMat.m);
		glUseProgram(sphereShader);
		glUniformMatrix4fv(glGetUniformLocation(sphereShader, "projMatrix"), 1, GL_TRUE, m_ProjMat.m);
		glUseProgram(groundShader);
		glUniformMatrix4fv(glGetUniformLocation(groundShader, "normalProjMatrix"), 1, GL_TRUE, m_ProjMat.m);
		glUniformMatrix4fv(glGetUniformLocation(groundShader, "depthProjMatrix"), 1, GL_TRUE, m_DepthMat.m);
		glUseProgram(wallShader);
		glUniformMatrix4fv(glGetUniformLocation(wallShader, "projMatrix"), 1, GL_TRUE, m_ProjMat.m);
		glUseProgram(m_DepthShader);
		glUniformMatrix4fv(glGetUniformLocation(m_DepthShader, "projMatrix"), 1, GL_TRUE, m_DepthMat.m);
		printError("Shader Init");

		// Depth Buffer Init
 		glGenFramebuffers(1, &m_DepthBuffer);
 		glBindFramebuffer(GL_FRAMEBUFFER, m_DepthBuffer);
 		glActiveTexture(GL_TEXTURE6);
		glGenTextures(1, &m_DepthTexture);
		glBindTexture(GL_TEXTURE_2D, Window::GetDepthTexture());
		glTexImage2D(GL_TEXTURE_2D, 0, GL_DEPTH_COMPONENT, 1024, 1024, 0, GL_DEPTH_COMPONENT, GL_FLOAT, 0);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE); 
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);  
		glFramebufferTexture(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, Window::GetDepthTexture(), 0);
 		glBindFramebuffer(GL_FRAMEBUFFER, 0);
		printError("Creating Depthmap");
		
		std::cout<< "World init"<<std::endl;
		
		InitObjects();

		glutTimerFunc(20, &Timer, 0);
		printError("Rest Init");
		return true;
	}

	void Window::InitObjects()
	{
		Game::GetPlayer()->init(0, m_sphereShader);
		Game::GetPlayer()->setPosition(0.0,1.0,0.0);

		//Iterate through the enemy list and initialize them with the shaders and an increasing index
		std::list<Enemy*> local_enemy_list=Game::GetEnemyList();
		int enemy_index=1;
		for(std::list<Enemy*>::iterator list_iter = local_enemy_list.begin(), end=local_enemy_list.end(); list_iter !=end; list_iter++)
		{
			(*list_iter)->init(enemy_index,m_sphereShader);
			(*list_iter)->setRndPosition(World::GetWorldMaximum().x, World::GetWorldMinimum().x, World::GetWorldMaximum().y, World::GetWorldMinimum().y);			
			enemy_index++;
		}
		Game::SetEnemyList(local_enemy_list);

		//Iterate through the food list and initialize them with the shaders and an increasing index
		std::list<Food*> local_food_list=Game::GetFoodList();
		int food_index=enemy_index+1;
		for(std::list<Food*>::iterator list_iter = local_food_list.begin(), end=local_food_list.end(); list_iter !=end; list_iter++)
		{
			(*list_iter)->init(food_index,m_sphereShader);
			(*list_iter)->setRndPosition(World::GetWorldMaximum().x, World::GetWorldMinimum().x, World::GetWorldMaximum().y, World::GetWorldMinimum().y);			
			food_index++;
		}
		Game::SetFoodList(local_food_list);

		
	}


	bool Window::Update()
	{
		return true;
	}

	void Window::Timer(int i)
	{
		glutTimerFunc(2, &Timer, i);
		glutPostRedisplay();
	}

	void Window::Clear()
	{
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	}

	void Window::Draw()
	{
		// Update View Matrix
		Clear();
		Game::GetCamera() -> CameraUpdate();
		mat4 viewMatrix = Game::GetCamera() -> getLookAtMatrix();
		vec3 cameraPosition = Game::GetCamera() -> getCameraPos();
		vec3 lightPos = Light::GetLightDirection();
		vec3 minus = vec3(-lightPos.x, -lightPos.y, -lightPos.z);
 		mat4 depthViewMatrix = IdentityMatrix();

		if(Game::IsStateInit())
		{

			printError("Clearing Screen");
			bool game_must_reset=false;

			if(Game::GetPlayer()->isInit()==false)
			{
				game_must_reset=true;
				std::cout<<"Player"<<std::endl;
			}

			std::list<Enemy*> local_enemy_list=Game::GetEnemyList();
			for(std::list<Enemy*>::iterator list_iter = local_enemy_list.begin(), end=local_enemy_list.end(); list_iter !=end; list_iter++)
			{
				if((*list_iter)->isInit()==false)
				{
					game_must_reset=true;
					std::cout<<"Enemy"<<std::endl;
				}
			}
			
			std::list<Food*> local_food_list=Game::GetFoodList();
			for(std::list<Food*>::iterator list_iter = local_food_list.begin(), end=local_food_list.end(); list_iter !=end; list_iter++)
			{
				if((*list_iter)->isInit()==false)
				{
					game_must_reset=true;
					std::cout<<"Food"<<std::endl;
				}
			}
			
			if(game_must_reset==true)
			{
				Game::ResetGame();	
			}
			
			InitObjects();
			depthViewMatrix = IdentityMatrix();
			m_World.draw(depthViewMatrix, viewMatrix, cameraPosition);
			GUI::InitView();
		}
		else if(Game::IsStatePlay())
		{
 			glViewport(0, 0, 1024, 1024);
			glBindFramebuffer(GL_FRAMEBUFFER, m_DepthBuffer);
			glClear(GL_DEPTH_BUFFER_BIT);
			glUseProgram(m_DepthShader);
			glActiveTexture(GL_TEXTURE6);
			glBindTexture(GL_TEXTURE_2D, Window::GetDepthTexture());
			depthViewMatrix = lookAtv(minus, vec3(0,0,0), vec3(0,1,0));

			Game::GetPlayer()->draw(depthViewMatrix, cameraPosition, m_DepthShader);

			std::list<Enemy*> local_enemy_list=Game::GetEnemyList();
			for(std::list<Enemy*>::iterator list_iter = local_enemy_list.begin(), end=local_enemy_list.end(); list_iter !=end; list_iter++)
			{
				(*list_iter)->draw(depthViewMatrix, cameraPosition, m_DepthShader);
			}
			Game::SetEnemyList(local_enemy_list);


			std::list<Food*> local_food_list=Game::GetFoodList();
			for(std::list<Food*>::iterator list_iter = local_food_list.begin(), end=local_food_list.end(); list_iter !=end; list_iter++)
			{
				(*list_iter)->draw(depthViewMatrix, cameraPosition, m_DepthShader);
			}
			Game::SetFoodList(local_food_list);
			


			glBindFramebuffer(GL_FRAMEBUFFER, 0);
			glViewport(0, 0, Window::GetWidth(), Window::GetHeight());
			printError("Drawing Depthbuffer");

			// Draw World
			m_World.draw(depthViewMatrix, viewMatrix, cameraPosition);
			printError("Drawing World");

			// Draw Objects
			Game::GetPlayer()->draw(viewMatrix, cameraPosition, m_sphereShader);

			local_enemy_list=Game::GetEnemyList();
	
			for(std::list<Enemy*>::iterator list_iter = local_enemy_list.begin(), end=local_enemy_list.end(); list_iter !=end; list_iter++)
			{
				(*list_iter)->draw(viewMatrix, cameraPosition, m_sphereShader);
			}
			Game::SetEnemyList(local_enemy_list);

			
			local_food_list=Game::GetFoodList();
	
			for(std::list<Food*>::iterator list_iter = local_food_list.begin(), end=local_food_list.end(); list_iter !=end; list_iter++)
			{
				(*list_iter)->draw(viewMatrix, cameraPosition, m_sphereShader);
			}
			Game::SetFoodList(local_food_list);



			printError("Drawing");

			GUI::PlayView();
		}
		else if(Game::IsStateGameOver())
		{
			Clear();
			depthViewMatrix = IdentityMatrix();
			m_World.draw(depthViewMatrix, viewMatrix, cameraPosition);
			GUI::GameOverView();
		}
		// swapping buffers
		glutSwapBuffers();
		printError("Swapping Buffers");
	}
}

