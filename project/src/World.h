#ifndef _WORLD_H
#define _WORLD_H

#if defined (__LINUX__) || (__CENTOS__)
	extern "C"
	{
		#define GL_GLEXT_PROTOTYPES
		#include "../../common/Linux/MicroGlut.h"
	}
#endif
#ifdef __OSX__
	extern "C"
	{
		#include <OpenGL/gl3.h>
		#include "../../common/mac/MicroGlut.h"
	}
#endif

#include "../../common/GL_utilities.h"
#include "../../common/loadobj.h"
#include "../../common/VectorUtils3.h"
#include "../../common/LoadTGA.h"
#include "Logger.h"
#include "Window.h"

namespace Crescer3D {

	class World {

	private:
		static vec3 worldMinimum;
		static vec3 worldMaximum;
		GLuint m_skyboxTexture;
		GLuint m_groundTexture;
		GLuint m_wallTexture;
		GLuint m_skyboxShader;
		GLuint m_groundShader;
		GLuint m_wallShader;
		GLuint m_depthShader;
		Model *m_skyboxModel;
		Model *m_groundModel;
		Model *m_wallModel;

	public:
		World();
		void init(GLuint skyboxShader, GLuint groundShader, GLuint wallShader, GLuint depthShader);
		void draw(mat4 depthViewMatrix, mat4 viewMatrix, vec3 cameraPos);
		inline static vec3 GetWorldMinimum() { return worldMinimum; };
		inline static vec3 GetWorldMaximum() { return worldMaximum; };
	};
}
#endif // _WORLD_H