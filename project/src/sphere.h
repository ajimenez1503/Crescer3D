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
		bool collision(Sphere other);
};
//////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////
