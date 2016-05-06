#include "World.h"

namespace Crescer3D {

	World::World()
	{}

	void World::init(GLuint skyboxShader, GLuint groundShader, GLuint wallShader) {
		
		m_skyboxShader = skyboxShader;
		m_groundShader = groundShader;
		m_wallShader = wallShader;

		glUseProgram(m_skyboxShader);
		glActiveTexture(GL_TEXTURE0);
		LoadTGATextureSimple("model/skybox/skybox.tga", &m_skyboxTexture);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
		glUseProgram(m_groundShader);
		glActiveTexture(GL_TEXTURE1);
		LoadTGATextureSimple("model/cube/grass3.tga", &m_groundTexture);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
		glUseProgram(m_wallShader);
		glActiveTexture(GL_TEXTURE2);
		LoadTGATextureSimple("model/cube/wall.tga", &m_wallTexture);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

		m_skyboxModel = LoadModelPlus("model/skybox/skybox.obj");
		m_groundModel = LoadModelPlus("model/cube/cubeplus.obj");
		m_wallModel = LoadModelPlus("model/cube/cubeplus.obj");
	}

	void World::draw(mat4 viewMatrix, vec3 cameraPos) {

		// Draw Skybox
		glDisable(GL_DEPTH_TEST);
		glDisable(GL_CULL_FACE);
		glDepthMask(0);
		glUseProgram(m_skyboxShader);
		mat4 SkyboxToView = viewMatrix;
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
		mdlViewMatrix = Mult(viewMatrix,S(100000,1,100000));
		glUniformMatrix4fv(glGetUniformLocation(m_groundShader, "mdlViewMatrix"), 1, GL_TRUE, mdlViewMatrix.m);
		glActiveTexture(GL_TEXTURE1);
		glBindTexture(GL_TEXTURE_2D, m_groundTexture);
		glUniform1i(glGetUniformLocation(m_groundShader, "tex"), 1);
		DrawModel(m_groundModel, m_groundShader, "inPosition", "inNormal", "inTexCoord");

		// Draw Walls
		glUseProgram(m_wallShader);
		glUniformMatrix4fv(glGetUniformLocation(m_wallShader, "mdlViewMatrix"), 1, GL_TRUE, viewMatrix.m);
		glActiveTexture(GL_TEXTURE2);
		glBindTexture(GL_TEXTURE_2D, m_wallTexture);
		glUniform1i(glGetUniformLocation(m_wallShader, "tex"), 2);
		//DrawModel(m_wallModel, m_wallShader, "inPosition", "inNormal", "inTexCoord");
	}
}