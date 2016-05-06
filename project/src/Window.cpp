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
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_BORDER); 
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_BORDER);  
		glFramebufferTexture(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, Window::GetDepthTexture(), 0);
 		glBindFramebuffer(GL_FRAMEBUFFER, 0);
		printError("Creating Depthmap");
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
		// Update View Matrix
		Clear();
		Game::GetCamera() -> CameraUpdate();
		mat4 viewMatrix = Game::GetCamera() -> getLookAtMatrix();
		vec3 cameraPosition = Game::GetCamera() -> getCameraPos();

		if(Game::IsStateInit())
		{
			
			printError("Clearing Screen");
			Game::ResetGame();
			GUI::InitView();
		}
		else if(Game::IsStatePlay())
		{
			// Draw Depthmap from Objects
			vec3 lightDir = Light::GetLightDirection();
 			vec3 lightPosition = vec3(-lightDir.x, -lightDir.y, -lightDir.z);
 			mat4 depthViewMatrix = lookAtv(lightPosition, vec3(0,0,0), vec3(0,1,0));
 			glViewport(0, 0, 1024, 1024);
			glBindFramebuffer(GL_FRAMEBUFFER, m_DepthBuffer);
			glClear(GL_DEPTH_BUFFER_BIT);
			glUseProgram(m_DepthShader);
			glActiveTexture(GL_TEXTURE6);
			glBindTexture(GL_TEXTURE_2D, Window::GetDepthTexture());
			Game::GetPlayer()->draw(depthViewMatrix, cameraPosition, m_DepthShader);
			Game::GetEnemy()->draw(depthViewMatrix, cameraPosition, m_DepthShader);
			Game::GetFood()->draw(depthViewMatrix, cameraPosition, m_DepthShader);
			glBindFramebuffer(GL_FRAMEBUFFER, 0);
			glViewport(0, 0, Window::GetWidth(), Window::GetHeight());
			printError("Drawing Depthbuffer");

			// Draw World
			m_World.draw(depthViewMatrix, viewMatrix, cameraPosition);
			printError("Drawing World");

			// Objects
			Game::GetPlayer()->draw(viewMatrix, cameraPosition);
			Game::GetEnemy()->draw(viewMatrix, cameraPosition);
			Game::GetFood()->draw(viewMatrix, cameraPosition);
			printError("Drawing Objects");

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
			Clear();
			GUI::GameOverView();
		}
		// swapping buffers
		glutSwapBuffers();
		printError("Swapping Buffers");
	}
}
