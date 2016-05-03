#include "Window.h"

namespace Crescer3D
{
	// forward declaration of static members
	GLuint Window::m_stdShader;
	GLuint Window::m_sphereShader;
	GLuint Window::m_groundShader;
	Ground Window::m_Ground;
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

		m_ProjMat = frustum(-0.1, 0.1, -0.1, 0.1, 0.2, 50.0);

		// Load and compile shader
		m_stdShader = loadShaders("shader/shader_std.vert", "shader/shader_std.frag");
		m_sphereShader = loadShaders("shader/Cell_Shader_Objects.vert", "shader/Cell_Shader_Objects.frag");
		m_groundShader = loadShaders("shader/Cell_Shader_Ground.vert", "shader/Cell_Shader_Ground.frag");

		glUseProgram(m_stdShader);
		glUniformMatrix4fv(glGetUniformLocation(m_stdShader, "projMatrix"), 1, GL_TRUE, m_ProjMat.m);
		glUseProgram(m_sphereShader);
		glUniformMatrix4fv(glGetUniformLocation(m_sphereShader, "projMatrix"), 1, GL_TRUE, m_ProjMat.m);
		glUniform1i(glGetUniformLocation(m_sphereShader, "inTest"), 666);
		glUseProgram(m_groundShader);
		glUniformMatrix4fv(glGetUniformLocation(m_groundShader, "projMatrix"), 1, GL_TRUE, m_ProjMat.m);
		printError("Shader Init");

		m_Ground.init();
		Game::GetPlayer()->init(0);
		Game::GetEnemy()->init(1);
		Game::GetFood()->init(2);
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
		glClearStencil(0);
	}

	void Window::Draw()
	{
		// clear the screen
		Clear();
		printError("Clearing Screen");
		// Update View Matrix

		Game::GetCamera() -> CameraUpdate();
		mat4 viewMatrix = Game::GetCamera() -> getLookAtMatrix();
		vec3 cameraDirection = Game::GetCamera() -> getCameraDir();

		glUseProgram(m_stdShader);
		glUniformMatrix4fv(glGetUniformLocation(m_stdShader, "mdlViewMatrix"), 1, GL_TRUE, viewMatrix.m);
		glUseProgram(m_sphereShader);
		glUniformMatrix4fv(glGetUniformLocation(m_sphereShader, "mdlViewMatrix"), 1, GL_TRUE, viewMatrix.m);
		glUniform3fv(glGetUniformLocation(m_sphereShader, "cameraPosition"), 1, &cameraPosition.x);
		glUseProgram(m_groundShader);
		glUniformMatrix4fv(glGetUniformLocation(m_groundShader, "mdlViewMatrix"), 1, GL_TRUE, viewMatrix.m);
		glUniform3fv(glGetUniformLocation(m_groundShader, "cameraPosition"), 1, &cameraPosition.x);
		printError("Updating View Matrix");

		if(Game::IsStateInit())
		{
			Game::ResetGame();
			GUI::InitView();
		}
		else if(Game::IsStatePlay())
		{
			GUI::PlayView();

			// Draw ground
			glUseProgram(m_groundShader);
			m_Ground.draw(viewMatrix, m_groundShader);

			// Draw Objects
			glUseProgram(m_sphereShader);
			Game::GetPlayer()->draw(viewMatrix, m_sphereShader);
			Game::GetEnemy()->draw(viewMatrix, m_sphereShader);
			Game::GetFood()->draw(viewMatrix,m_sphereShader);
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