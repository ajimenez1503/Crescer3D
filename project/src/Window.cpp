#include "Window.h"

namespace Crescer3D
{
	// forward declaration of static members
	GLuint Window::m_Program;
	Sphere Window::m_Player;
	Sphere Window::m_Enemy;
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
		printError("GL inits");

		m_ProjMat = frustum(-0.1, 0.1, -0.1, 0.1, 0.2, 50.0);

		// Load and compile shader
		m_Program = loadShaders("shader/shader.vert", "shader/shader.frag");
		glUseProgram(m_Program);
		printError("init shader");

		glUniformMatrix4fv(glGetUniformLocation(m_Program, "projMatrix"), 1, GL_TRUE, m_ProjMat.m);
		
		// Load Models
		m_Ground.init();
		m_Player.init(0);
		m_Enemy.init(1);
		m_Enemy.setPosition(-3.0,1.0,0.0);
		sfMakeRasterFont(); // init font

		glutTimerFunc(20, &Timer, 0);

		return true;
	}

	bool Window::Update()
	{
		displayScore();
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
		// angle of rotation for the camera direction
		const float angle = 0.0;
		// actual vector representing the camera's direction
		const float lx = 0.0f;
		const float lz = -1.0f;
		// XZ position of the camera
		const float x = 0.0f;
		const float z = 8.0f;
		const float y = 3.0f;
		const float deltaAngle = 0.0f;
		const int xOrigin = -1;

		// clear the screen
		Clear();

		printError("pre display");
		glUseProgram(m_Program);

		// Build matrix
		mat4 total = lookAt(x, y, z, x+lx, y,  z+lz,0.0f, 1.0f,  0.0f);
		glUniformMatrix4fv(glGetUniformLocation(m_Program, "mdlMatrix"), 1, GL_TRUE, total.m);

		//draw stuff
		m_Ground.draw(total, m_Program);
		m_Player.draw(total, m_Program);
		m_Enemy.draw(total, m_Program);
		
		printError("post display");
		glutSwapBuffers();

	}

	void Window::displayScore()
	{
		// needs to be fixed: get score data from gameplay subsytem
		int score = 99;
		char outString[28]; // enough to hold all numbers up to 64-bits and "Score: "
		const char* a = "Score: ";
		sprintf(outString,"%s%d",a,score);
		sfDrawString(20, 20, outString);
	}
}