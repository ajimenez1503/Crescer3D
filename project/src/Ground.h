#ifndef _GROUND_H
#define _GROUND_H

#include "Platform.h"

#ifdef __LINUX__
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

class Ground {
	private:
		GLuint tex0;
		Model *cube;

	public:
		Ground();
		void init();
		void draw(mat4 total,GLuint program);
};

#endif // _GROUND_H
