#include "Window.h"

namespace Crescer3D
{
	// forward declaration of static members
	World Window::m_World;
	mat4 Window::m_ProjMat;
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

		m_ProjMat = frustum(-0.1, 0.1, -0.1, 0.1, 0.2, 1000.0);

		// Load and compile shader
		GLuint skyboxShader = loadShaders("shader/Shader_Skybox.vert", "shader/Shader_Skybox.frag");
		GLuint sphereShader = loadShaders("shader/Shader_Objects.vert", "shader/Shader_Objects.frag");
		GLuint groundShader = loadShaders("shader/Shader_Ground.vert", "shader/Shader_Ground.frag");
		GLuint wallShader = loadShaders("shader/Shader_Ground.vert", "shader/Shader_Ground.frag");

		glUseProgram(skyboxShader);
		glUniformMatrix4fv(glGetUniformLocation(skyboxShader, "projMatrix"), 1, GL_TRUE, m_ProjMat.m);
		glUseProgram(sphereShader);
		glUniformMatrix4fv(glGetUniformLocation(sphereShader, "projMatrix"), 1, GL_TRUE, m_ProjMat.m);
		glUseProgram(groundShader);
		glUniformMatrix4fv(glGetUniformLocation(groundShader, "projMatrix"), 1, GL_TRUE, m_ProjMat.m);
		glUseProgram(wallShader);
		glUniformMatrix4fv(glGetUniformLocation(wallShader, "projMatrix"), 1, GL_TRUE, m_ProjMat.m);
		printError("Shader Init");

		m_World.init(skyboxShader, groundShader, wallShader);


		Game::GetPlayer()->init(0, sphereShader);

		//Iterate through the enemy list and initialize them with the shaders and an increasing index
		//Game::GetEnemy()->init(1, sphereShader);

		std::list<Enemy*> local_enemy_list=Game::GetEnemyList();
		
		std::cout << "Window Initialize" << std::endl;
		std::cout << local_enemy_list.size() << std::endl;
	
		int enemy_index=1;
		for(std::list<Enemy*>::iterator list_iter = local_enemy_list.begin(), end=local_enemy_list.end(); list_iter !=end; list_iter++)
		{
			(*list_iter)->init(enemy_index,sphereShader);
			//std::cout << (*list_iter)->getX()<< std::endl;
			std::cout << (*list_iter)->getID()<< std::endl;
			enemy_index++;
		}
		Game::SetEnemyList(local_enemy_list);
	

		//Game::GetFood()->init(2, sphereShader);

		glutTimerFunc(20, &Timer, 0);
		printError("Rest Init");
		return true;
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
		// clear the screen
		Clear();
		printError("Clearing Screen");
		// Update View Matrix

		Game::GetCamera() -> CameraUpdate();
		mat4 viewMatrix = Game::GetCamera() -> getLookAtMatrix();
		vec3 cameraPosition = Game::GetCamera() -> getCameraPos();

		if(Game::IsStateInit())
		{
			//Game::ResetGame();

			GUI::InitView();
		}
		else if(Game::IsStatePlay())
		{
			// Draw World
			m_World.draw(viewMatrix, cameraPosition);

			// Draw Objects
			Game::GetPlayer()->draw(viewMatrix, cameraPosition);
			
			//Game::GetEnemy()->draw(viewMatrix, cameraPosition);
			std::list<Enemy*> local_enemy_list=Game::GetEnemyList();
			//(*local_enemy_list.begin())->draw(viewMatrix, cameraPosition);

			//std::cout << local_enemy_list.size() << std::endl;				
			for(std::list<Enemy*>::iterator list_iter = local_enemy_list.begin(), end=local_enemy_list.end(); list_iter !=end; list_iter++)
			{
				(*list_iter)->draw(viewMatrix, cameraPosition);
				//std::cout << (*list_iter)->getID()<< std::endl;
				//std::cout << (*list_iter)->getX()<< std::endl;
			}
			Game::SetEnemyList(local_enemy_list);
			//Game::GetFood()->draw(viewMatrix, cameraPosition);

			printError("Drawing");

/*			if(!m_CollisionState && (Game::GetPlayer()->collision(Game::GetEnemy())
			|| Game::GetPlayer()->collisionAABB(Game::GetFood())))
			{
				Logger::Log("Collision!");
				HighScore::IncrementScore();
				m_CollisionState=true;
			}

			if(m_CollisionState && (!Game::GetPlayer()->collision(Game::GetEnemy())
			&& !Game::GetPlayer()->collisionAABB(Game::GetFood())))
			{
				Logger::Log("No Collision!");
				m_CollisionState=false;
			}
*/
			GUI::PlayView();
		}
		else if(Game::IsStateGameOver())
		{
			GUI::GameOverView();
		}
		// swapping buffers
		glutSwapBuffers();
		printError("Swapping Buffers");
	}
}
