#include "World.h"

namespace Crescer3D {

	vec3 World::worldMinimum;
	vec3 World::worldMaximum;

	World::World()
	{}

	void World::init(GLuint skyboxShader, GLuint groundShader, GLuint wallShader, GLuint depthShader) {
		
		worldMinimum = vec3(-102, -102, -102);
		worldMaximum = vec3(102, 102, 102);

		m_skyboxShader = skyboxShader;
		m_groundShader = groundShader;
		m_wallShader = wallShader;
		m_depthShader = depthShader;

		glUseProgram(m_skyboxShader);
		glActiveTexture(GL_TEXTURE0);
		LoadTGATextureSimple("model/skybox/skybox.tga", &m_skyboxTexture);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
		glUseProgram(m_groundShader);
		glActiveTexture(GL_TEXTURE1);
		LoadTGATextureSimple("model/cube/grass3.tga", &m_groundTexture);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
		glUseProgram(m_wallShader);
		glActiveTexture(GL_TEXTURE2);
		LoadTGATextureSimple("model/cube/wall3.tga", &m_wallTexture);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

		m_skyboxModel = LoadModelPlus("model/skybox/skybox.obj");
		m_groundModel = LoadModelPlus("model/cube/cubeplus.obj");
		m_wallModel = LoadModelPlus("model/cube/cubeplus.obj");
	}

	void World::draw(mat4 depthViewMatrix, mat4 normalViewMatrix, vec3 cameraPos) {

		// Draw Skybox
		glDisable(GL_DEPTH_TEST);
		glDisable(GL_CULL_FACE);
		glDepthMask(0);
		glUseProgram(m_skyboxShader);
		mat4 SkyboxToView = normalViewMatrix;
		SkyboxToView.m[3] = 0.0f;
		SkyboxToView.m[7] = 0.0f;
		SkyboxToView.m[11] = 0.0f;
		SkyboxToView.m[15] = 1.0f;
		mat4 SkyboxToWorld = Mult(S(10.0, 10.0, 10.0), T(0.0, -0.1, 0.0));
		mat4 mdlViewMatrix = SkyboxToView * SkyboxToWorld;
		glUniformMatrix4fv(glGetUniformLocation(m_skyboxShader, "mdlViewMatrix"), 1, GL_TRUE, mdlViewMatrix.m);
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, m_skyboxTexture);
		glUniform1i(glGetUniformLocation(m_skyboxShader, "tex"), 0);
		DrawModel(m_skyboxModel, m_skyboxShader, "inPosition", NULL, "inTexCoord");
		glEnable(GL_DEPTH_TEST);
		glEnable(GL_CULL_FACE);
		glDepthMask(1);

		// Draw Ground
		glUseProgram(m_groundShader);
		mat4 groundWorldMatrix = Mult(T(0.0, 0.0, 0.0), S(100000,1,100000));
		glUniformMatrix4fv(glGetUniformLocation(m_groundShader, "worldMatrix"), 1, GL_TRUE, groundWorldMatrix.m);
		glUniformMatrix4fv(glGetUniformLocation(m_groundShader, "normalViewMatrix"), 1, GL_TRUE, normalViewMatrix.m);
		glUniformMatrix4fv(glGetUniformLocation(m_groundShader, "depthViewMatrix"), 1, GL_TRUE, depthViewMatrix.m);
		vec3 worldMin = World::GetWorldMinimum();
		vec3 worldMax = World::GetWorldMaximum();
		glUniform3fv(glGetUniformLocation(m_groundShader, "worldMin"), 1, &worldMin.x);
		glUniform3fv(glGetUniformLocation(m_groundShader, "worldMax"), 1, &worldMax.x);
		glActiveTexture(GL_TEXTURE1);
		glBindTexture(GL_TEXTURE_2D, m_groundTexture);
		glUniform1i(glGetUniformLocation(m_groundShader, "tex"), 1);
		glActiveTexture(GL_TEXTURE6);
		glBindTexture(GL_TEXTURE_2D, Window::GetDepthTexture());
		glUniform1i(glGetUniformLocation(m_groundShader, "depthTex"), 6);
		DrawModel(m_groundModel, m_groundShader, "inPosition", "inNormal", "inTexCoord");
		printError("Rendering Ground");

		// Draw Walls
		mat4 wallWorldMatrix, wallMatrix;

		glUseProgram(m_wallShader);
		glActiveTexture(GL_TEXTURE2);
		glBindTexture(GL_TEXTURE_2D, m_wallTexture);
		glUniform1i(glGetUniformLocation(m_wallShader, "tex"), 2);
		// Wall 1
		for(int i = -26; i <= 26; ++i)
		{
			wallWorldMatrix = Mult(T(i*4, 1.5, (GetWorldMaximum().z+2)), S(2.0, 2.0, 2.0));
			wallMatrix = normalViewMatrix * wallWorldMatrix;
			glUniform1f(glGetUniformLocation(m_wallShader, "scale"), 0.25);
			glUniformMatrix4fv(glGetUniformLocation(m_wallShader, "mdlViewMatrix"), 1, GL_TRUE, wallMatrix.m);
			DrawModel(m_wallModel, m_wallShader, "inPosition", NULL, "inTexCoord");
		}
		// Wall 2
		for(int i = -26; i <= 26; ++i)
		{
			wallWorldMatrix = Mult(T(i*4, 1.5, (GetWorldMinimum().z-2)), S(2.0, 2.0, 2.0));
			wallMatrix = normalViewMatrix * wallWorldMatrix;
			glUniform1f(glGetUniformLocation(m_wallShader, "scale"), 0.25);
			glUniformMatrix4fv(glGetUniformLocation(m_wallShader, "mdlViewMatrix"), 1, GL_TRUE, wallMatrix.m);
			DrawModel(m_wallModel, m_wallShader, "inPosition", NULL, "inTexCoord");
		}
		// Wall 3
		for(int i = -25; i <= 25; ++i)
		{
			wallWorldMatrix = Mult(T((GetWorldMaximum().x+2), 1.5, i*4), S(2.0, 2.0, 2.0));
			wallMatrix = normalViewMatrix * wallWorldMatrix;
			glUniform1f(glGetUniformLocation(m_wallShader, "scale"), 0.25);
			glUniformMatrix4fv(glGetUniformLocation(m_wallShader, "mdlViewMatrix"), 1, GL_TRUE, wallMatrix.m);
			DrawModel(m_wallModel, m_wallShader, "inPosition", NULL, "inTexCoord");
		}
		// Wall 4
		for(int i = -25; i <= 25; ++i)
		{
			wallWorldMatrix = Mult(T((GetWorldMinimum().x-2), 1.5, i*4), S(2.0, 2.0, 2.0));
			wallMatrix = normalViewMatrix * wallWorldMatrix;
			glUniform1f(glGetUniformLocation(m_wallShader, "scale"), 0.25);
			glUniformMatrix4fv(glGetUniformLocation(m_wallShader, "mdlViewMatrix"), 1, GL_TRUE, wallMatrix.m);
			DrawModel(m_wallModel, m_wallShader, "inPosition", NULL, "inTexCoord");

		}
		printError("Rendering Walls");
	}
}