#ifndef _CUBE_H
#define _CUBE_H

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
#include <math.h>
#include <stdlib.h>


//////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////

namespace Crescer3D
{

class Cube {
	private:
		float positionx,positiony,positionz;
		GLuint tex1;
		Model *model;
		int id;
		float velocity;
		float size;
	public:
		Cube();
		void init(int x);
		void draw(mat4 total,GLuint program);
		void moveForward ();
		void moveBack () ;
		void moveLeft ();
		void moveRight ();
		void moveUp ();
		void moveDown ();
		vec3 getMinBox();
		vec3 getMaxBox();
		float getX();
		float getY();
		float getZ();
		float getSize();
		void incrementSize();
		void decrementSize();
		void setPositionX(float x);
		void setPositionY(float y);
		void setPositionZ(float z);
		void setPosition(float x, float y,float z);
};

}
//////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////

#endif //  _CUBE_H
