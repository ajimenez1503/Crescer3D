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
		Game::GetEnemy()->init(1, sphereShader);
		Game::GetFood()->init(2, sphereShader);
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
			Game::ResetGame();
			GUI::InitView();
		}
		else if(Game::IsStatePlay())
		{
			// Draw World
			m_World.draw(viewMatrix, cameraPosition);

			// Draw Objects
			Game::GetPlayer()->draw(viewMatrix, cameraPosition);
			Game::GetEnemy()->draw(viewMatrix, cameraPosition);
			Game::GetFood()->draw(viewMatrix, cameraPosition);

			printError("Drawing");

			if(!m_CollisionState && (Game::GetPlayer()->collision(Game::GetEnemy())
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
