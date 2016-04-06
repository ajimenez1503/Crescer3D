#include "Window.h"

namespace Crescer3D
{
	// forward declaration of static members
	GLuint Window::m_Program;
	Ground Window::m_Ground;
	mat4 Window::m_ProjMat;

	Window::Window(char* title, int width, int height)
	: System(SystemType::Sys_Window)
	{
		m_Title = title;
		m_Width = width;
		m_Height = height;
	}

	Window::~Window()
	{}

	bool Window::Initialize()
	{
		glutInit(0, 0);
		glutInitDisplayMode(GLUT_DOUBLE | GLUT_DEPTH |  GLUT_RGB);
		glutInitContextVersion(3, 2);
		glutInitWindowSize (m_Width, m_Height);
		glutCreateWindow (m_Title);
		glutDisplayFunc(Draw);

		glClearColor(0.2,0.2,0.5,0);
		glEnable(GL_DEPTH_TEST);
		glDisable(GL_CULL_FACE);
		printError("OpenGL Init");

		m_ProjMat = frustum(-0.1, 0.1, -0.1, 0.1, 0.2, 50.0);

		// Load and compile shader
		m_Program = loadShaders("shader/shader.vert", "shader/shader.frag");
		glUseProgram(m_Program);
		printError("Shader Init");

		glUniformMatrix4fv(glGetUniformLocation(m_Program, "projMatrix"), 1, GL_TRUE, m_ProjMat.m);
		
		m_Ground.init();
		Game::GetPlayer()->init(0);
		Game::GetEnemy()->init(1);

		Game::GetEnemy()->setPosition(-3.0,1.0,0.0);
		sfMakeRasterFont(); // init font
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
		glutTimerFunc(20, &Timer, i);
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
		glUseProgram(m_Program);
		printError("Clearing Screen");

		// build matrix
		mat4 total = Input::GetLookAtMatrix();
		glUniformMatrix4fv(glGetUniformLocation(m_Program, "mdlMatrix"), 1, GL_TRUE, total.m);
		printError("Getting Camera Matrix");

		// draw stuff
		m_Ground.draw(total, m_Program);
		DisplayScore();
		Game::GetPlayer()->draw(total, m_Program);
		Game::GetEnemy()->draw(total, m_Program);
		printError("Drawing");

		// swapping buffers
		glutSwapBuffers();
		printError("Swapping Buffers");
	}

	void Window::DisplayScore()
	{
		// needs to be fixed: get score data from gameplay subsytem
		int score = 123456;
		
		char outString[28]; // enough to hold all numbers up to 64-bits and "Score: "
		const char* a = "Score: ";
		sprintf(outString,"%s%d",a,score);
		sfDrawString(20, 20, outString);
	}
}