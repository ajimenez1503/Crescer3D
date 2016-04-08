#ifndef _SPHERE_H
#define _SPHERE_H

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
#include <math.h>
#include <stdlib.h>


//////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////

class Sphere {
	private:
		float positionx,positiony,positionz;
		GLuint tex1;
		Model *model;
		int id;
		float velocity;
		float radius;//the radious can be incrmeent and decrement. By deafult it is 1. 
	public:
		Sphere();
		void init(int x);
		void draw(mat4 total,GLuint program);
		void moveForward ();
		void moveBack () ;
		void moveLeft ();
		void moveRight ();
		float getRadius();
		float getX();
		float getY();
		float getZ();
		void incrementRadius();
		void decrementRadius();
		void setPositionX(float x);
		void setPositionY(float y);
		void setPositionZ(float z);
		void setPosition(float x, float y,float z);
		bool collision(Sphere* other);
};
//////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////

#endif // _SPHERE_H