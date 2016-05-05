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

namespace Crescer3D {

	class World {

	private:
		GLuint m_skyboxTexture;
		GLuint m_groundTexture;
		GLuint m_wallTexture;
		GLuint m_skyboxShader;
		GLuint m_groundShader;
		GLuint m_wallShader;
		Model *m_skyboxModel;
		Model *m_groundModel;
		Model *m_wallModel;

	public:
		World();
		void init(GLuint skyboxShader, GLuint groundShader, GLuint wallShader);
		void draw(mat4 total, vec3 cameraPos);
	};
}
#endif // _WORLD_H